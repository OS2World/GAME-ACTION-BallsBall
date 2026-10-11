/**************************************************************************
 *  File name  :  keymap.c
 *
 *  Description:  Keyboard mapping and joystick support of BallsBall and
 *                the "Key Mapping..." dialog (notebook: Keyboard, Joystick).
 *
 *                Keys: the runner's four directions and start/pause can be
 *                given any key.  Enter always starts / pauses, any other
 *                character key still stops the runner (as before).
 *                Joystick: through the GAME$ driver; every action can be a
 *                button or a stick direction.  The mappings are saved in
 *                bb.ini (section "Keys", key "Map").
 *************************************************************************/
#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_WINSTDBOOK
#define INCL_WINENTRYFIELDS
#define INCL_WININPUT

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "dlg.h"
#include "game.h"
#include "xtrn.h"
#include "keymap.h"
#include "joyos2.h"

extern BOOL bBackgrndRun;

/* ------------------------------------------------------------------ data */

typedef struct { int vk, chr; } KMKEY;            /* virtual key or character */

static KMKEY km_keys[KM_KEYACTS] = {
    { VK_LEFT,  0 }, { VK_RIGHT, 0 }, { VK_UP, 0 }, { VK_DOWN, 0 }, { VK_SPACE, 0 }
};

/* joystick: 0=none, 1-4=button, 5-8=axis left/right/up/down */
#define JOY_AXIS_L  5
#define JOY_AXIS_R  6
#define JOY_AXIS_U  7
#define JOY_AXIS_D  8
static int km_joy_sel = 0;                        /* 0=off, 1=stick A, 2=stick B */
static int km_joy[KM_ACTIONS] = { JOY_AXIS_L, JOY_AXIS_R, JOY_AXIS_U, JOY_AXIS_D, 1, 2 };

static HFILE             hGame = 0;               /* GAME$ driver            */
static GAME_2DPOS_STRUCT joyCalA = { 0, 0 };      /* centre of stick A       */
static GAME_2DPOS_STRUCT joyCalB = { 0, 0 };      /* centre of stick B       */
static BOOL              bJoyAvail[2];            /* stick A / B reported    */
static BOOL              bModal = FALSE;          /* dialog open: no polling */
static int               prevDown[KM_ACTIONS];    /* accepted state (edge detection) */
static int               rawLast[KM_ACTIONS];     /* last raw sample (debounce)      */
static BOOL              bPrimed = FALSE;         /* first reading taken as baseline */

static const USHORT usButBit[4] = { JOY_BUT1_BIT, JOY_BUT2_BIT, JOY_BUT3_BIT, JOY_BUT4_BIT };

/* the key names the user sees (English, like the key caps) */
static const struct { SHORT code; const char *name; } vkNames[] = {
    { 0x01, "Button1" }, { 0x02, "Button2" }, { 0x03, "Button3" },
    { 0x04, "Break" },   { 0x05, "Backspace" }, { 0x06, "Tab" },
    { 0x07, "Backtab" }, { 0x08, "Return" },  { 0x09, "Shift" },
    { 0x0A, "Ctrl" },    { 0x0B, "Alt" },     { 0x0C, "Altgraf" },
    { 0x0D, "Pause" },   { 0x0E, "Caps Lock" }, { 0x0F, "Esc" },
    { 0x10, "Space" },   { 0x11, "Page Up" }, { 0x12, "Page Down" },
    { 0x13, "End" },     { 0x14, "Home" },    { 0x15, "Left" },
    { 0x16, "Up" },      { 0x17, "Right" },   { 0x18, "Down" },
    { 0x19, "PrintScrn" }, { 0x1A, "Insert" }, { 0x1B, "Delete" },
    { 0x1C, "ScrlLock" }, { 0x1D, "Num Lock" }, { 0x1E, "Enter" },
    { 0x1F, "SysRq" },   { 0x20, "F1" },      { 0x21, "F2" },
    { 0x22, "F3" },      { 0x23, "F4" },      { 0x24, "F5" },
    { 0x25, "F6" },      { 0x26, "F7" },      { 0x27, "F8" },
    { 0x28, "F9" },      { 0x29, "F10" },     { 0x30, "F11" },
    { 0x31, "F12" }
};
#define NVKNAMES (sizeof(vkNames) / sizeof(vkNames[0]))

static const INT idsAct[KM_ACTIONS] = {
    IDS_KM_A_LEFT, IDS_KM_A_RIGHT, IDS_KM_A_UP, IDS_KM_A_DOWN, IDS_KM_A_START, IDS_KM_A_STOP
};

static PSZ KmText(ULONG id)
{
    static CHAR buf[8][MESSAGELEN];
    static int  n;

    n = (n + 1) & 7;
    return LangText(id, MESSAGELEN, (PSZ)buf[n]);
}

static void KmKeyName(const KMKEY *k, char *out)
{
    unsigned i;

    if (k->vk)
        for (i = 0; i < NVKNAMES; i++)
            if (vkNames[i].code == k->vk) {
                strcpy(out, vkNames[i].name);
                return;
            }
    if (k->chr > 32 && k->chr < 127) {
        out[0] = (char)toupper(k->chr);
        out[1] = 0;
        return;
    }
    strcpy(out, (char *)KmText(IDS_KM_NONE));
}

static const char *JoyLabel(int n)
{
    static char b[MESSAGELEN];

    if (n == 0) return (char *)KmText(IDS_KM_NONE);
    if (n >= 1 && n <= 4) { sprintf(b, (char *)KmText(IDS_KM_BTN), n); return b; }
    if (n == JOY_AXIS_L) return (char *)KmText(IDS_KM_AXL);
    if (n == JOY_AXIS_R) return (char *)KmText(IDS_KM_AXR);
    if (n == JOY_AXIS_U) return (char *)KmText(IDS_KM_AXU);
    if (n == JOY_AXIS_D) return (char *)KmText(IDS_KM_AXD);
    return "?";
}

/* ------------------------------------------------------------ the keyboard */

/* Which action does this WM_CHAR belong to?  -1 = none */
INT KmKeyAction(MPARAM mp1, MPARAM mp2)
{
    USHORT fs   = SHORT1FROMMP(mp1);
    USHORT chr  = SHORT1FROMMP(mp2);
    USHORT vkey = SHORT2FROMMP(mp2);
    int    a;

    for (a = 0; a < KM_KEYACTS; a++) {
        if (km_keys[a].vk) {
            if ((fs & KC_VIRTUALKEY) && vkey == km_keys[a].vk)
                return a;
        } else if (km_keys[a].chr) {
            if ((fs & KC_CHAR) && !(fs & KC_VIRTUALKEY) &&
                tolower(chr) == tolower(km_keys[a].chr))
                return a;
        }
    }
    return -1;
}

/* ------------------------------------------------------------- the joystick */

VOID KmInit(VOID)
{
    APIRET            rc;
    ULONG             action, dataLen;
    GAME_PARM_STRUCT  parms;
    GAME_CALIB_STRUCT calib;

    rc = DosOpen(GAMEPDDNAME, &hGame, &action, 0, FILE_READONLY, FILE_OPEN,
                 OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL);
    if (rc != NO_ERROR)
        hGame = 0;
    else {
        dataLen = sizeof(parms);
        rc = DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_PARMS,
                         NULL, 0, NULL, &parms, dataLen, &dataLen);
        if (rc != NO_ERROR) { DosClose(hGame); hGame = 0; }
    }
    if (hGame != 0) {
        bJoyAvail[0] = (parms.useA & GAME_USE_BOTH_NEWMASK) != 0;
        bJoyAvail[1] = (parms.useB & GAME_USE_BOTH_NEWMASK) != 0;
        dataLen = sizeof(calib);
        if (DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_CALIB,
                        NULL, 0, NULL, &calib, dataLen, &dataLen) == NO_ERROR) {
            joyCalA.x = calib.Ax.centre;  joyCalA.y = calib.Ay.centre;
            joyCalB.x = calib.Bx.centre;  joyCalB.y = calib.By.centre;
        }
    }
    /* a saved joystick choice only holds if the driver reports that stick */
    if (km_joy_sel == 1 && !bJoyAvail[0]) km_joy_sel = 0;
    if (km_joy_sel == 2 && !bJoyAvail[1]) km_joy_sel = 0;
    if (!hGame) km_joy_sel = 0;
    /* poll the stick 20 times a second */
    WinStartTimer(hab, hwndMain, IDT_JOY, 50);
}

VOID KmDone(VOID)
{
    WinStopTimer(hab, hwndMain, IDT_JOY);
    if (hGame) {
        DosClose(hGame);
        hGame = 0;
    }
}

/* Poll the stick.  An action happens when a button is newly pressed or a
 * direction is newly pushed.  What is held when polling starts (at launch, after
 * a dialog, when the window is activated) is only taken as the starting state,
 * and a change must be seen twice in a row (debounce), so a stick that does not
 * rest exactly in the centre or a button that chatters cannot start / pause the
 * game by itself. */
VOID KmJoyPoll(VOID)
{
    GAME_STATUS_STRUCT s;
    ULONG              len = sizeof(s);
    GAME_2DPOS_STRUCT *jd, *cal;
    SHORT              tolX, tolY, dX, dY;
    BOOL               axL, axR, axU, axD;
    int                a, c, down;

    if (!km_joy_sel || !hGame || bModal ||
        (WinQueryActiveWindow(HWND_DESKTOP) != hwndMainFrame && !bBackgrndRun)) {
        bPrimed = FALSE;
        return;
    }
    if (DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS,
                    NULL, 0, NULL, &s, len, &len) != NO_ERROR)
        return;
    jd   = (km_joy_sel == 1) ? &s.curdata.A : &s.curdata.B;
    cal  = (km_joy_sel == 1) ? &joyCalA : &joyCalB;
    tolX = (SHORT)(abs((int)cal->x) / 10 + 1);
    tolY = (SHORT)(abs((int)cal->y) / 10 + 1);
    if (tolX < 16) tolX = 16;               /* generous dead zone */
    if (tolY < 16) tolY = 16;
    dX   = (SHORT)(jd->x - cal->x);
    dY   = (SHORT)(jd->y - cal->y);
    axL = dX < -tolX;  axR = dX > tolX;
    axU = dY < -tolY;  axD = dY > tolY;
    for (a = 0; a < KM_ACTIONS; a++) {
        c = km_joy[a];
        down = 0;
        if (c >= 1 && c <= 4)
            down = (s.curdata.butMask & usButBit[c - 1]) == 0;
        else if (c == JOY_AXIS_L) down = axL;
        else if (c == JOY_AXIS_R) down = axR;
        else if (c == JOY_AXIS_U) down = axU;
        else if (c == JOY_AXIS_D) down = axD;
        if (!bPrimed) {                     /* first reading: baseline only */
            prevDown[a] = rawLast[a] = down;
            continue;
        }
        if (down == rawLast[a] && down != prevDown[a]) {
            prevDown[a] = down;             /* stable for two polls */
            if (down)
                RunnerAction(a);
        }
        rawLast[a] = down;
    }
    bPrimed = TRUE;
}

/* -------------------------------------------------------------- settings */

typedef struct {
    int ver;
    int vk[KM_KEYACTS], chr[KM_KEYACTS];
    int joy_sel, joy[KM_ACTIONS];
} KMCFG;

VOID KmSave(HINI hini)
{
    KMCFG c;
    int   i;

    c.ver = 1;
    for (i = 0; i < KM_KEYACTS; i++) { c.vk[i] = km_keys[i].vk; c.chr[i] = km_keys[i].chr; }
    for (i = 0; i < KM_ACTIONS; i++) c.joy[i] = km_joy[i];
    c.joy_sel = km_joy_sel;
    PrfWriteProfileData(hini, "Keys", "Map", &c, sizeof(c));
}

VOID KmLoad(HINI hini)
{
    KMCFG c;
    ULONG cb = sizeof(c);
    int   i, ok = 1;

    if (!PrfQueryProfileData(hini, "Keys", "Map", &c, &cb) || cb != sizeof(c) || c.ver != 1)
        return;
    for (i = 0; i < KM_KEYACTS; i++)
        if (c.vk[i] < 0 || c.vk[i] > 255 || c.chr[i] < 0 || c.chr[i] > 255 ||
            (c.vk[i] == 0 && c.chr[i] == 0))
            ok = 0;
    for (i = 0; i < KM_ACTIONS; i++)
        if (c.joy[i] < 0 || c.joy[i] > 8)
            ok = 0;
    if (c.joy_sel < 0 || c.joy_sel > 2)
        ok = 0;
    if (!ok)
        return;
    for (i = 0; i < KM_KEYACTS; i++) { km_keys[i].vk = c.vk[i]; km_keys[i].chr = c.chr[i]; }
    for (i = 0; i < KM_ACTIONS; i++) km_joy[i] = c.joy[i];
    km_joy_sel = c.joy_sel;
}

/* ============================================================== dialogs */

#define WM_KM_INPUT   (WM_USER + 1)

typedef struct _KMIN {
    USHORT fs;                      /* KC_* flags of the key               */
    UCHAR  vkey;                    /* virtual key                         */
    USHORT chr;                     /* character                           */
    USHORT type;                    /* 0 = key down, 1 = mouse button down */
} KMIN;

static PFNWP pfnEntryOrig;

/* Keys pressed in a mapping box go to the owning page */
static MRESULT EXPENTRY KmEntryProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    HWND   hwndOwner = WinQueryWindow(hwnd, QW_OWNER);
    USHORT id        = WinQueryWindowUShort(hwnd, QWS_ID);
    KMIN   ki;

    switch (msg) {
    case WM_CHAR: {
        USHORT fs = CHARMSG(&msg)->fs;
        USHORT vk = CHARMSG(&msg)->vkey;
        /* Tab/Esc/F1 and Alt combinations keep their dialog meaning */
        if (fs & KC_ALT)
            break;
        if ((fs & KC_VIRTUALKEY) &&
            (vk == VK_TAB || vk == VK_BACKTAB || vk == VK_ESC || vk == VK_F1))
            break;
        if (!(fs & KC_KEYUP)) {
            ki.fs = fs;  ki.vkey = (UCHAR)vk;  ki.chr = CHARMSG(&msg)->chr;  ki.type = 0;
            WinSendMsg(hwndOwner, WM_KM_INPUT, MPFROMSHORT(id), MPFROMP(&ki));
        }
        return (MRESULT)TRUE;
    }
    }
    return pfnEntryOrig(hwnd, msg, mp1, mp2);
}

static VOID KmSubclass(HWND hwndPage, USHORT id)
{
    HWND  hwndE = WinWindowFromID(hwndPage, id);
    PFNWP p;

    if (hwndE == NULLHANDLE)
        return;
    p = WinSubclassWindow(hwndE, KmEntryProc);
    if (p != NULL && pfnEntryOrig == NULL)
        pfnEntryOrig = p;
}

/* Enable or disable every child of hwnd except the one with excludeId */
static VOID EnableChildren(HWND hwnd, USHORT excludeId, BOOL en)
{
    HENUM  he = WinBeginEnumWindows(hwnd);
    HWND   hc;
    while ((hc = WinGetNextWindow(he)) != NULLHANDLE) {
        if (WinQueryWindowUShort(hc, QWS_ID) != excludeId)
            WinEnableWindow(hc, en);
    }
    WinEndEnumWindows(he);
}

/* ------------------------------------------------------------ keyboard tab */

static KMKEY kmKeyTmp[KM_KEYACTS];

static MRESULT EXPENTRY KmKeyboardProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    int  i;
    char name[24];

    switch (msg) {
    case WM_INITDLG:
        WinSetDlgItemText(hwnd, IDC_KM_KH1, KmText(IDS_KM_KBD_H1));
        WinSetDlgItemText(hwnd, IDC_KM_KH2, KmText(IDS_KM_KBD_H2));
        for (i = 0; i < KM_KEYACTS; i++) {
            WinSetDlgItemText(hwnd, IDC_KM_KL1 + i, KmText(idsAct[i]));
            kmKeyTmp[i] = km_keys[i];
            KmKeyName(&kmKeyTmp[i], name);
            WinSetDlgItemText(hwnd, IDC_KM_KBD1 + i, (PSZ)name);
            KmSubclass(hwnd, (USHORT)(IDC_KM_KBD1 + i));
        }
        return (MRESULT)FALSE;

    case WM_KM_INPUT: {
        KMIN *ki = (KMIN *)PVOIDFROMMP(mp2);
        INT   n  = (INT)SHORT1FROMMP(mp1) - IDC_KM_KBD1;

        if (n < 0 || n >= KM_KEYACTS)
            return (MRESULT)FALSE;
        if (ki->vkey == VK_SHIFT || ki->vkey == VK_CTRL || ki->vkey == VK_ALT)
            return (MRESULT)TRUE;           /* modifier only */
        if ((ki->fs & KC_VIRTUALKEY) && ki->vkey >= 1 && ki->vkey <= 0x31) {
            kmKeyTmp[n].vk = ki->vkey;  kmKeyTmp[n].chr = 0;
        } else if ((ki->fs & KC_CHAR) && ki->chr > 32 && ki->chr < 127) {
            kmKeyTmp[n].vk = 0;  kmKeyTmp[n].chr = ki->chr;
        } else
            return (MRESULT)TRUE;           /* unsupported key */
        KmKeyName(&kmKeyTmp[n], name);
        WinSetDlgItemText(hwnd, SHORT1FROMMP(mp1), (PSZ)name);
        return (MRESULT)TRUE;
    }

    case WM_COMMAND:
        if (SHORT1FROMMP(mp1) == DID_OK)
            for (i = 0; i < KM_KEYACTS; i++)
                km_keys[i] = kmKeyTmp[i];
        return 0;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

/* ------------------------------------------------------------ joystick tab */

/* Calibrate and stick choices follow what the driver reports */
static VOID KmCalEnable(HWND hwnd)
{
    WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_CAL),  hGame && bJoyAvail[0]);
    WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_CALB), hGame && bJoyAvail[1]);
    if (!hGame)
        WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JOY_EN), FALSE);
    if (!bJoyAvail[0])
        WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JOY_A), FALSE);
    if (!bJoyAvail[1])
        WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JOY_B), FALSE);
}

/* Centre the stick, then read its position as the neutral point */
static VOID CalibrateStick(HWND hwnd, BOOL isA)
{
    CHAR szMsg[MESSAGELEN + 8]; CHAR szTitle[MESSAGELEN + 8];

    if (!hGame)
        return;
    sprintf(szMsg,   (char *)KmText(IDS_KM_CAL_MSG),   isA ? 'A' : 'B');
    sprintf(szTitle, (char *)KmText(IDS_KM_CAL_TITLE), isA ? 'A' : 'B');
    if (WinMessageBox(HWND_DESKTOP, hwnd, szMsg, szTitle, 0,
                      MB_OKCANCEL | MB_INFORMATION) == MBID_OK) {
        GAME_STATUS_STRUCT joyCal;
        ULONG calLen = sizeof(joyCal);
        if (DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS,
                        NULL, 0, NULL, &joyCal, calLen, &calLen) == NO_ERROR) {
            if (isA) {
                joyCalA.x = joyCal.curdata.A.x;
                joyCalA.y = joyCal.curdata.A.y;
            } else {
                joyCalB.x = joyCal.curdata.B.x;
                joyCalB.y = joyCal.curdata.B.y;
            }
        }
    }
}

static MRESULT EXPENTRY KmJoystickProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static int    iTmpJoy;
    static int    iTmpAct[KM_ACTIONS];
    static int    iSelAct;
    static USHORT usPrevButs;
    static BOOL   bPAxL, bPAxR, bPAxU, bPAxD;
    int  i;

    switch (msg) {
    case WM_INITDLG:
        iTmpJoy = km_joy_sel;
        for (i = 0; i < KM_ACTIONS; i++)
            iTmpAct[i] = km_joy[i];
        iSelAct    = -1;
        usPrevButs = 0xFFFF;
        bPAxL = bPAxR = bPAxU = bPAxD = FALSE;
        /* prime the axis state so a stick held off-centre does not assign */
        if (hGame) {
            GAME_STATUS_STRUCT s0;
            ULONG len0 = sizeof(s0);
            if (DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS,
                            NULL, 0, NULL, &s0, len0, &len0) == NO_ERROR) {
                GAME_2DPOS_STRUCT *jd0  = (iTmpJoy != 2) ? &s0.curdata.A : &s0.curdata.B;
                GAME_2DPOS_STRUCT *cal0 = (iTmpJoy != 2) ? &joyCalA : &joyCalB;
                SHORT tx = (SHORT)(abs((int)cal0->x) / 10 + 1);
                SHORT ty = (SHORT)(abs((int)cal0->y) / 10 + 1);
                SHORT dx = (SHORT)(jd0->x - cal0->x);
                SHORT dy = (SHORT)(jd0->y - cal0->y);
                bPAxL = dx < -tx;  bPAxR = dx >  tx;
                bPAxU = dy < -ty;  bPAxD = dy >  ty;
            }
        }
        WinSetDlgItemText(hwnd, IDC_KM_JOY_EN, KmText(IDS_KM_JOY_EN));
        WinSetDlgItemText(hwnd, IDC_KM_JOY_A,  KmText(IDS_KM_JOY_A));
        WinSetDlgItemText(hwnd, IDC_KM_JOY_B,  KmText(IDS_KM_JOY_B));
        WinSetDlgItemText(hwnd, IDC_KM_CAL,    KmText(IDS_KM_CAL_A));
        WinSetDlgItemText(hwnd, IDC_KM_CALB,   KmText(IDS_KM_CAL_B));
        WinSetDlgItemText(hwnd, IDC_KM_JH1,    KmText(IDS_KM_JOY_H1));
        WinSetDlgItemText(hwnd, IDC_KM_JH2,    KmText(IDS_KM_JOY_H2));
        WinSendDlgItemMsg(hwnd, IDC_KM_JOY_EN, BM_SETCHECK,
                          MPFROMSHORT(iTmpJoy != 0), MPVOID);
        WinSendDlgItemMsg(hwnd, (iTmpJoy == 2) ? IDC_KM_JOY_B : IDC_KM_JOY_A,
                          BM_SETCHECK, MPFROMSHORT(1), MPVOID);
        for (i = 0; i < KM_ACTIONS; i++) {
            WinSetDlgItemText(hwnd, IDC_KM_JL1 + i, KmText(idsAct[i]));
            WinSetDlgItemText(hwnd, IDC_KM_JBTN1 + i, (PSZ)JoyLabel(iTmpAct[i]));
            KmSubclass(hwnd, (USHORT)(IDC_KM_JBTN1 + i));
        }
        EnableChildren(hwnd, IDC_KM_JOY_EN, iTmpJoy != 0);
        KmCalEnable(hwnd);
        WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, 1, 50);
        return (MRESULT)FALSE;

    case WM_TIMER:
        /* a new button press or deflection goes to the focused box */
        if (hGame && iTmpJoy != 0) {
            GAME_STATUS_STRUCT s;
            ULONG len = sizeof(s);
            if (DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS,
                            NULL, 0, NULL, &s, len, &len) == NO_ERROR) {
                GAME_2DPOS_STRUCT *jd  = (iTmpJoy == 1) ? &s.curdata.A : &s.curdata.B;
                GAME_2DPOS_STRUCT *cal = (iTmpJoy == 1) ? &joyCalA : &joyCalB;
                SHORT tolX = (SHORT)(abs((int)cal->x) / 10 + 1);
                SHORT tolY = (SHORT)(abs((int)cal->y) / 10 + 1);
                SHORT dX = (SHORT)(jd->x - cal->x);
                SHORT dY = (SHORT)(jd->y - cal->y);
                USHORT curButs = s.curdata.butMask;
                USHORT pressed = usPrevButs & ~curButs;
                BOOL axL = dX < -tolX, axR = dX > tolX;
                BOOL axU = dY < -tolY, axD = dY >  tolY;
                INT  newAct = 0;
                if (pressed) {
                    for (i = 0; i < 4; i++)
                        if (pressed & usButBit[i]) { newAct = i + 1; break; }
                }
                if (!newAct) {
                    if (axL && !bPAxL) newAct = JOY_AXIS_L;
                    else if (axR && !bPAxR) newAct = JOY_AXIS_R;
                    else if (axU && !bPAxU) newAct = JOY_AXIS_U;
                    else if (axD && !bPAxD) newAct = JOY_AXIS_D;
                }
                if (newAct && iSelAct >= 0) {
                    iTmpAct[iSelAct] = newAct;
                    WinSetDlgItemText(hwnd, IDC_KM_JBTN1 + iSelAct, (PSZ)JoyLabel(newAct));
                }
                usPrevButs = curButs;
                bPAxL = axL; bPAxR = axR; bPAxU = axU; bPAxD = axD;
            }
        }
        return 0;

    case WM_KM_INPUT: {
        KMIN *ki = (KMIN *)PVOIDFROMMP(mp2);
        INT   r  = (INT)SHORT1FROMMP(mp1) - IDC_KM_JBTN1;
        if (r >= 0 && r < KM_ACTIONS && (ki->fs & KC_VIRTUALKEY) &&
            (ki->vkey == VK_BACKSPACE || ki->vkey == VK_DELETE)) {
            iTmpAct[r] = 0;
            WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBTN1 + r), (PSZ)JoyLabel(0));
        }
        return (MRESULT)TRUE;
    }

    case WM_CONTROL:
        if (SHORT1FROMMP(mp1) >= IDC_KM_JBTN1 && SHORT1FROMMP(mp1) < IDC_KM_JBTN1 + KM_ACTIONS) {
            if (SHORT2FROMMP(mp1) == EN_SETFOCUS)
                iSelAct = SHORT1FROMMP(mp1) - IDC_KM_JBTN1;
            else if (SHORT2FROMMP(mp1) == EN_KILLFOCUS)
                iSelAct = -1;
            return 0;
        }
        if (SHORT2FROMMP(mp1) == BN_CLICKED) {
            switch (SHORT1FROMMP(mp1)) {
            case IDC_KM_JOY_EN: {
                BOOL en = (BOOL)(SHORT)(ULONG)WinSendDlgItemMsg(hwnd,
                              IDC_KM_JOY_EN, BM_QUERYCHECK, MPVOID, MPVOID);
                if (!en) {
                    iTmpJoy = 0;
                } else {
                    BOOL isB = (BOOL)(SHORT)(ULONG)WinSendDlgItemMsg(hwnd,
                                   IDC_KM_JOY_B, BM_QUERYCHECK, MPVOID, MPVOID);
                    iTmpJoy = isB ? 2 : 1;
                }
                EnableChildren(hwnd, IDC_KM_JOY_EN, en);
                KmCalEnable(hwnd);
                break;
            }
            case IDC_KM_JOY_A: if (iTmpJoy != 0) iTmpJoy = 1; break;
            case IDC_KM_JOY_B: if (iTmpJoy != 0) iTmpJoy = 2; break;
            }
        }
        return 0;

    case WM_COMMAND:
        switch (SHORT1FROMMP(mp1)) {
        case DID_OK:
            km_joy_sel = iTmpJoy;
            for (i = 0; i < KM_ACTIONS; i++)
                km_joy[i] = iTmpAct[i];
            break;
        case IDC_KM_CAL:
            CalibrateStick(hwnd, TRUE);
            break;
        case IDC_KM_CALB:
            CalibrateStick(hwnd, FALSE);
            break;
        }
        return 0;

    case WM_DESTROY:
        WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, 1);
        return 0;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

/* ------------------------------------------------------------- main dialog */

static HWND  hwndNB, hwndKbd, hwndJoy;
static ULONG ulKbdPage, ulJoyPage;

static VOID KmSizeNotebook(HWND hwnd)
{
    SWP swpBtn, swpDlg;

    WinQueryWindowPos(hwnd, &swpDlg);
    WinQueryWindowPos(WinWindowFromID(hwnd, DID_OK), &swpBtn);
    WinSetWindowPos(hwndNB, HWND_TOP,
        4, swpBtn.y + swpBtn.cy + 4,
        swpDlg.cx - 8,
        swpDlg.cy - (swpBtn.y + swpBtn.cy + 4) - 4 -
            WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR),
        SWP_MOVE | SWP_SIZE);
}

static MRESULT EXPENTRY KeyMappingDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch (msg) {
    case WM_INITDLG: {
        SWP swpFr;

        /* a dialog window is the frame itself: the title bar belongs to hwnd */
        WinSetWindowText(hwnd, KmText(IDS_KM_TITLE));
        WinSetDlgItemText(hwnd, DID_OK,     KmText(IDS_KM_OK));
        WinSetDlgItemText(hwnd, DID_CANCEL, KmText(IDS_KM_CANCEL));
        WinQueryWindowPos(hwnd, &swpFr);
        WinSetWindowPos(hwnd, HWND_TOP,
            (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN) - swpFr.cx) / 2,
            (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) - swpFr.cy) / 2,
            0, 0, SWP_MOVE | SWP_ACTIVATE);

        hwndNB = WinCreateWindow(hwnd, WC_NOTEBOOK, "",
                     BKS_TABBEDDIALOG | BKS_BACKPAGESBR | WS_VISIBLE | WS_TABSTOP,
                     0, 0, 1, 1, hwnd, HWND_TOP, IDC_KM_NOTEBOOK, NULL, NULL);
        if (hwndNB == NULLHANDLE) {
            WinDismissDlg(hwnd, FALSE);
            return (MRESULT)FALSE;
        }
        KmSizeNotebook(hwnd);
        /* the strip of the page area the page window does not cover has the
           dialog colour (it was white) */
        WinSendMsg(hwndNB, BKM_SETNOTEBOOKCOLORS,
                   MPFROMLONG(WinQuerySysColor(HWND_DESKTOP, SYSCLR_DIALOGBACKGROUND, 0)),
                   MPFROMSHORT(BKA_BACKGROUNDPAGECOLOR));

        ulKbdPage = (ULONG)WinSendMsg(hwndNB, BKM_INSERTPAGE, NULL,
                    MPFROM2SHORT(BKA_AUTOPAGESIZE | BKA_MAJOR, BKA_LAST));
        WinSendMsg(hwndNB, BKM_SETTABTEXT, MPFROMLONG(ulKbdPage), MPFROMP(KmText(IDS_KM_TAB_KBD)));
        ulJoyPage = (ULONG)WinSendMsg(hwndNB, BKM_INSERTPAGE, NULL,
                    MPFROM2SHORT(BKA_AUTOPAGESIZE | BKA_MAJOR, BKA_LAST));
        WinSendMsg(hwndNB, BKM_SETTABTEXT, MPFROMLONG(ulJoyPage), MPFROMP(KmText(IDS_KM_TAB_JOY)));

        hwndKbd = WinLoadDlg(hwndNB, hwndNB, KmKeyboardProc, NULLHANDLE, DLG_KM_KEYBOARD, NULL);
        WinSendMsg(hwndNB, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulKbdPage), MPFROMHWND(hwndKbd));
        hwndJoy = WinLoadDlg(hwndNB, hwndNB, KmJoystickProc, NULLHANDLE, DLG_KM_JOYSTICK, NULL);
        WinSendMsg(hwndNB, BKM_SETPAGEWINDOWHWND, MPFROMLONG(ulJoyPage), MPFROMHWND(hwndJoy));

        WinSendMsg(hwndNB, BKM_TURNTOPAGE, MPFROMLONG(ulKbdPage), MPVOID);
        return (MRESULT)FALSE;
    }

    case WM_SIZE:
        if (hwndNB)
            KmSizeNotebook(hwnd);
        break;

    case WM_COMMAND:
        switch (SHORT1FROMMP(mp1)) {
        case DID_OK:
            WinSendMsg(hwndKbd, WM_COMMAND, MPFROMSHORT(DID_OK), MPVOID);
            WinSendMsg(hwndJoy, WM_COMMAND, MPFROMSHORT(DID_OK), MPVOID);
            WinDismissDlg(hwnd, TRUE);
            break;
        case DID_CANCEL:
            WinDismissDlg(hwnd, FALSE);
            break;
        }
        return 0;
    }
    return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

VOID KmDialog(HWND hwndOwner)
{

    hwndNB = NULLHANDLE;                    /* no stale handle for WM_SIZE */
    bModal = TRUE;
    WinDlgBox(HWND_DESKTOP, hwndOwner, KeyMappingDlgProc, NULLHANDLE, DLG_KEYMAPPING, NULL);
    bModal = FALSE;
    bPrimed = FALSE;                        /* what is held now is the new baseline */
}
