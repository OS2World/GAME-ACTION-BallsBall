/**************************************************************************
 *  File name  :  main.c
 *
 *  Description:  ᮧ����� ����, �㭪樨 ���� � ��ࠡ��稪
 *                ᮡ�⨩ �� �롮� ��樨 � ����
 *
 *                This source file contains the following functions:
 *
 *                main()
 *                MainWndProc(hwnd, msg, mp1, mp2)
 *                MessageBox(hwndOwner, idMsg, szTitle, fsStyle, fBeep)
 *                MainCommand(mp1, mp2)
 *      MainChar(hwnd, mp1, mp2)
 *                MainTimer(ulTIMER)
 *
 *  Concepts   :  Presentation Manager
 *
 *  API's      :  WinInitialize
 *                DosBeep
 *                WinCreateMsgQueue
 *                WinTerminate
 *                WinCreateStdWindow
 *                WinOpenWindowDC
 *                WinGetMsg
 *                WinDispatchMsg
 *                WinPostMsg
 *                WinLoadMessage
 *                WinAlarm
 *                WinMessageBox
 *
 *    Files    :  OS2.H, MAIN.H, HELP.H, XTRN.H, GAME.H, DLG.H
 *
 *************************************************************************/

/* Include files, macros, defined constants, and externs */

#define  INCL_DOSPROCESS
#define  INCL_WIN
#define  INCL_WINHELP

#include <os2.h>
#include <stdlib.h>
#include "game.h"
#include "main.h"
#include "help.h"
#include "dlg.h"
#include "xtrn.h"


static const char bldlevel[] = "@#BALLSBALL:1.3#@ BallsBall for OS/2 Presentation Manager";
#pragma ref(bldlevel)

/* Global variables */
HWND hwndMainFrame = NULLHANDLE;    /* handle to the main frame window */
HWND hwndMain;                      /* handle to the main client window */
HWND hwndMenu;                      /* 奭�� �������� ���� */
HWND hwndPopupMenu;      /* 奭�� ������饣� ���� */
HDC  hdcMain;                       /* handle to the DC of the client */
HAB  hab;                           /* anchor block for the process */
HMQ  hmq;                           /* handle to the process' message queue */
CHAR szAppName[MAXNAMEL];           /* buffer for application name string */
CHAR szUntitled[MESSAGELEN];        /* buffer for "Untitled" string */
BOOL fHelpEnabled;                  /* flag to determine if help is enabled */
BOOL bStart;
BOOL bBackgrndRun = FALSE;
static HWND hwndTitleBar  = NULLHANDLE;
static HWND hwndSysMenu   = NULLHANDLE;
static HWND hwndMinMax    = NULLHANDLE;
static HWND hwndMenuBar   = NULLHANDLE;

/* Entry point declarations */

/**************************************************************************
 *  Name       : main()
 *
 *  Description: Initializes the PM environment, calls the
 *               initialization routine, creates the main
 *               window,  and polls the message queue
 *
 *  Concepts:    - obtains anchor block handle and creates message
 *                    queue
 *               - calls the initialization routine
 *               - creates the main frame window which creates the
 *                    main client window
 *               - polls the message queue via Get/Dispatch Msg loop
 *               - upon exiting the loop, exits
 *
 *  API's      :  WinInitialize
 *                DosBeep
 *                WinCreateMsgQueue
 *                WinTerminate
 *                WinCreateStdWindow
 *                WinOpenWindowDC
 *                WinGetMsg
 *                WinDispatchMsg
 *
 *  Return     :  0 - if successful execution completed
 *                1 - if error
 *************************************************************************/
int main(VOID)
{  QMSG qmsg;          /* message structure */
   ULONG flCtlData;    /* frame control data */
   BOOL bInit;//�᫨ ���樠������ ��諠 ���਩��
   CHAR szLangT[40];

   hab = WinInitialize(0);
   if(NULLHANDLE == hab) {
      DosBeep(BEEP_WARN_FREQ, BEEP_WARN_DUR);
      return(RETURN_ERROR);}
   hmq = WinCreateMsgQueue(hab, 0);
   if(NULLHANDLE == hmq) {
      DosBeep(BEEP_WARN_FREQ, BEEP_WARN_DUR); WinTerminate(hab);
      return(RETURN_ERROR);}

   if(!Init()) {
      MessageBox(HWND_DESKTOP, IDMSG_INITFAILED,(PSZ)NULL,
                   MB_OK | MB_ERROR, TRUE);
      return(RETURN_ERROR);}

   /* create the main window */
   flCtlData = FCF_TITLEBAR  | FCF_SYSMENU    | FCF_MINBUTTON |
               FCF_TASKLIST   | FCF_BORDER    | FCF_ICON      |
               FCF_ACCELTABLE | FCF_MENU      | FCF_SHELLPOSITION;


   hwndMainFrame = WinCreateStdWindow(HWND_DESKTOP, WS_VISIBLE,
                      &flCtlData, (PSZ)szAppName, (PSZ)NULL,
                      WS_VISIBLE, (HMODULE)NULL, IDR_MAIN,
                      (PHWND)&hwndMain);
   if(NULLHANDLE == hwndMainFrame){
       MessageBox(HWND_DESKTOP, IDMSG_MAINWINCREATEFAILED,
          (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
       return(RETURN_ERROR);}
   hdcMain = WinOpenWindowDC(hwndMain);
   hwndTitleBar = WinWindowFromID(hwndMainFrame, FID_TITLEBAR);
   hwndSysMenu  = WinWindowFromID(hwndMainFrame, FID_SYSMENU);
   hwndMinMax   = WinWindowFromID(hwndMainFrame, FID_MINMAX);
   hwndMenuBar  = WinWindowFromID(hwndMainFrame, FID_MENU);
   /* ���樠������ ����஥� � ���� */
   bInit = InitPrf();
   ApplyLanguage();
   InitFont( hdcMain); bStart = 1;
   /* ��������� ࠧ��஢ �������� ���� */
   WinSetWindowPos(
      hwndMainFrame,//�� �㤥� �ந��
      HWND_TOP,//�������� ���
      MainX,MainY,//���न���� ����
      BmpSize*Col+2,BmpSize*Row+40+LineHeight,//ࠧ����
      SWP_SIZE | SWP_MOVE );
   /* �� ���� ���樠������ ����஥� � ���� */
   InitNewGame(0);//����� ���
   InitHelp();
   if(!bInit)//�᫨ ���樠������ ��諠 ���਩��
      MessageBox(hwndMain, IDMSG_CANNOTLOADSETTINGS,
         LangText(IDS_TITLE_WARNING, 40, szLangT), MB_OK | MB_ERROR, TRUE);
   /* Get/Dispatch Message loop */
   while(WinGetMsg(hab, (PQMSG)&qmsg, (HWND)NULL, (ULONG)NULL, (ULONG)NULL))
       WinDispatchMsg(hab, (PQMSG)&qmsg);
   /* destroy the help instance */
   DestroyHelpInstance(); ExitProc();
   return(RETURN_SUCCESS);
}   /* End of main   */
/**************************************************************************
 *  Name       : MainWndProc(hwnd, msg, mp1, mp2)
 *
 *  Description:  Processes the messages sent to the main client
 *                window.  This routine processes the basic
 *                messages all client windows should process
 *                and passes all others onto WinDefWindowProc where
 *                the developer can process any others.
 *
 *  Concepts:     Called for each message placed in the main
 *                window's message queue
 *
 *                A switch statement branches to the routines to be
 *                performed for each message processed. Any messages
 *                not specifically process are passed to the user's
 *                message processing procedure WinDefWindowProc().
 *
 *  API's      :  WinPostMsg
 *
 *  Parameters :  hwnd = window handle
 *                msg  = message i.d.
 *                mp1  = first message parameter
 *                mp2  = second message parameter
 *
 *  Return     :  value is determined by each message
 *************************************************************************/
MRESULT EXPENTRY MainWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   switch(msg){
   case WM_CREATE:
      UpdateTitleText(((PCREATESTRUCT)PVOIDFROMMP(mp2))->hwndParent, 0);
      hwndPopupMenu = WinLoadMenu(hwnd,NULLHANDLE,POPUP_MENU);
      return (MRESULT)FALSE;
      break;

   case WM_ACTIVATE:
      if (!bBackgrndRun) {
         bGame = 0;
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      break;

   case WM_BUTTON1DOWN://��誠
      {//���न���� ��誨 �⭮�⥫쭮 ���न��� ���㭪�
      long  lx,ly;
      //��-�����,������ ���� ��⨢��
      if(WinQueryActiveWindow(HWND_DESKTOP)!=hwndMainFrame) {
        WinSetActiveWindow(HWND_DESKTOP,hwndMainFrame);
        break;}
      //��-�����,㧭��� ���न���� ������
      lx = SHORT1FROMMP(mp1)-Runner.xLeft*BmpSize-BmpSize/2-1;
      ly = SHORT2FROMMP(mp1)-Runner.yBottom*BmpSize-BmpSize/2+2;
      //�-�����,���⠢�塞 ��� ������� ���
      if(lx == ly) ++lx;
      if(lx > abs(ly) )
         WinPostMsg(hwnd, WM_CHAR, MPVOID,
            (MPARAM)MAKELONG(0,VK_RIGHT)); else
      if(-lx > abs(ly) )
         WinPostMsg(hwnd, WM_CHAR, MPVOID,
            (MPARAM)MAKELONG(0,VK_LEFT)); else
      if(ly > abs(lx) )
         WinPostMsg(hwnd, WM_CHAR, MPVOID,
            (MPARAM)MAKELONG(0,VK_UP));
      else
         WinPostMsg(hwnd, WM_CHAR, MPVOID,
            (MPARAM)MAKELONG(0,VK_DOWN));}break;

   case WM_BUTTON2DOWN://������饥 ����
      //��-�����,������ ���� ��⨢��
      if(WinQueryActiveWindow(HWND_DESKTOP)!=hwndMainFrame) {
        WinSetActiveWindow(HWND_DESKTOP,hwndMainFrame);
        break;}
      //��-�����,��㥬 ������饥 ����
      MenuRedraw(bSound-7);//�⠢�� ���
      WinPopupMenu(hwnd,hwnd,hwndPopupMenu,
          SHORT1FROMMP(mp1),SHORT2FROMMP(mp1), IDM_DIRECTION_START,
          PU_POSITIONONITEM | PU_KEYBOARD     |
          PU_HCONSTRAIN     | PU_VCONSTRAIN   |
          PU_MOUSEBUTTON1   | PU_MOUSEBUTTON2 ); break;

   case WM_PAINT:
       MainPaint(hwnd); break;

   case WM_COMMAND:
       MainCommand(hwnd, mp1, mp2);break;

   case WM_TIMER:
      MainTimer(hwnd,SHORT1FROMMP(mp1));break;

   case WM_CHAR://����⨥ ������
       if(!(SHORT1FROMMP(mp1) & KC_KEYUP) &&
          !(SHORT1FROMMP(mp1) & KC_PREVDOWN))
          MainChar(hwnd,mp1,mp2);break;

   case WM_INITMENU:
       InitMenu(mp1, mp2);break;

   case HM_QUERY_KEYS_HELP:
       return (MRESULT)PANEL_HELPKEYS;/* return id of key help panel */break;

   case WM_DESTROY:
      if(bGame){//�᫨ ���� ��� - ��⠭��������
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      ClosePrf();break;

   default: return WinDefWindowProc(hwnd, msg, mp1, mp2); break; }
   return (MRESULT)NULL;
}   /* End of MainWndProc   */
/**************************************************************************
 *  Name       : MessageBox(hwndOwner, nIdMsg, fsStyle, fBeep)
 *
 *  Description:  Displays the message box with the message
 *                given in idMsg retrieved from the message table
 *                and using the style flags in fsStyle.
 *
 *  Concepts:     Called whenever a message box is to be displayed
 *
 *                - Message string is loaded from the process'
 *                    message table
 *                - Alarm beep is sounded if desired
 *                - Message box with the message is displayed
 *                - WinMessageBox return value is returned
 *
 *  API's      :  WinLoadMessage
 *                WinAlarm
 *                WinMessageBox
 *
 *  Parameters :  hwndOwner = window handle of the owner
 *                nIdMsg   = message i.d.
 *      szTitle  = ���������
 *                fsStyle  = style flags for the message box
 *                fBeep   = should an alarm be sounded?
 *
 *  Return     :  return value from WinMessageBox
 *************************************************************************/
ULONG MessageBox(HWND hwndOwner, ULONG idMsg, PSZ szTitle, ULONG fsStyle, BOOL fBeep)
{  CHAR szText[MESSAGELEN];

   if (!WinLoadMessage(hab, (HMODULE)NULL, iLangBase+idMsg,
                 MESSAGELEN, (PSZ)szText)){
      WinAlarm(HWND_DESKTOP, WA_ERROR);return MBID_ERROR;}
   if(fBeep) WinAlarm(HWND_DESKTOP, WA_ERROR);
   return(WinMessageBox(HWND_DESKTOP, hwndOwner, szText,
                        szTitle, MSGBOXID, fsStyle));
}   /* End of MessageBox   */
/**************************************************************************
 *  Name       : MainCommand(mp1, mp2)
 *
 *  Description: Calls the appropriate procedures that deal with
 *               the selected menu item.
 *
 *  Concepts:    Routine is called whenever a WM_COMMAND message
 *               is posted to the main window.
 *
 *               A switch statement branches on the id of the
 *               menu item that posted the message and the
 *               appropriate action for that item is taken.  Any
 *               menu ids that are not part of the standard menu
 *               set are passed onto the user defined WM_COMMAND
 *               processing procedure.
 *
 *  API's      : [none]
 *
 *  Parameters : mp1 = first message parameter
 *               mp2 = second message parameter
 *************************************************************************/
VOID MainCommand(HWND hwnd, MPARAM mp1, MPARAM mp2)
{  USHORT usReturn;

   switch(SHORT1FROMMP(mp1))
   {
   case IDM_FILENEW:
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      if(bStart && iScore != iBScore){
         usReturn = MessageBox(hwnd, IDMSG_SAVE," ",
                       MB_YESNOCANCEL | MB_INFORMATION, 0);
         switch(usReturn) {
            case MBID_YES:
               FileSave(mp2);
            case MBID_NO:
               usLevel = 0; InitNewGame(0);iBScore = 0;
               UpdateTitleText(hwndMainFrame,1);
               WinInvalidateRect(hwnd,NULL,FALSE); break;
            case MBID_CANCEL:
               if(bGame){//�᫨ 諠 ���,����᪠�� ���⭮
                  WinStartTimer(hab,hwnd,IDT_MOVE,100);
                  WinStartTimer(hab,hwnd,IDT_GAME,1000);}break;
            default:break;}}
      else{usLevel = 0; InitNewGame(0);iBScore = 0;
           UpdateTitleText(hwndMainFrame,1);
           WinInvalidateRect(hwnd,NULL,FALSE);} break;

   case IDM_FILEOPEN:
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      if(bStart && iScore != iBScore){
         usReturn = MessageBox(hwnd, IDMSG_SAVE," ",
                       MB_YESNOCANCEL | MB_INFORMATION, 0);
         switch(usReturn) {
            case MBID_YES:
               FileSave(mp2);
            case MBID_NO:
               FileOpen(mp2); break;
            case MBID_CANCEL:
               if(bGame){//�᫨ 諠 ���,����᪠�� ���⭮
                  WinStartTimer(hab,hwnd,IDT_MOVE,100);
                  WinStartTimer(hab,hwnd,IDT_GAME,1000);}break;
            default:break;}}
      else FileOpen(mp2); break;

   case IDM_FILESAVE:
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      FileSave(mp2);
      if(bGame){//�᫨ ���� ���
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_FILESAVEAS:
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      FileSaveAs(mp2);
      if(bGame){//�᫨ ���� ���
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_HIGHSCORES:
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      HScoresPrf(0);
      if(bGame){//�᫨ ���� ���
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_FILEEXIT:
         if(bGame){//�᫨ ���� ���
            WinStopTimer(hab,hwnd,IDT_MOVE);//��⠭��������
            WinStopTimer(hab,hwnd,IDT_GAME);}
         if(bStart && iScore != iBScore){
            usReturn = MessageBox(hwnd, IDMSG_SAVE," ",
                         MB_YESNOCANCEL | MB_INFORMATION, 0);
            switch(usReturn) {
               case MBID_YES: FileSave(mp2);
               case MBID_NO:
                  WinPostMsg(hwnd,WM_CLOSE,MPVOID,MPVOID);break;
               case MBID_CANCEL:
                  if(bGame){//�᫨ 諠 ���,����᪠�� ���⭮
                     WinStartTimer(hab,hwnd,IDT_MOVE,100);
                     WinStartTimer(hab,hwnd,IDT_GAME,1000);}break;
               default:break;}}
         else WinPostMsg(hwnd,WM_CLOSE,MPVOID,MPVOID);break;

   case IDM_DIRECTION_START:
         if(bStart) {
            if(bGame){//�᫨ ���� ���
               bGame = 0;//��⠭��������
               WinStopTimer(hab,hwnd,IDT_MOVE);
               WinStopTimer(hab,hwnd,IDT_GAME);}
            else{//�᫨ ��� ��⠭������
               bGame = 1;//��ࠥ� �����
               WinStartTimer(hab,hwnd,IDT_MOVE,100);
               WinStartTimer(hab,hwnd,IDT_GAME,1000);}
            WinCheckMenuItem(hwndMenu, IDM_DIRECTION_START, !bGame);
            WinCheckMenuItem(hwndPopupMenu, IDM_DIRECTION_START, !bGame);}break;

   case IDM_BACKGRND:
      bBackgrndRun = !bBackgrndRun;
      WinCheckMenuItem(hwndMenu, IDM_BACKGRND, bBackgrndRun);
      break;

   case IDM_FRAME_CTRL:
      {
         static BOOL bFrameHidden = FALSE;
         if (!bFrameHidden) {
            WinSetParent(hwndTitleBar, HWND_OBJECT, FALSE);
            WinSetParent(hwndSysMenu,  HWND_OBJECT, FALSE);
            WinSetParent(hwndMinMax,   HWND_OBJECT, FALSE);
            WinSetParent(hwndMenuBar,  HWND_OBJECT, FALSE);
            WinSendMsg(hwndMainFrame, WM_UPDATEFRAME,
               (MPARAM)(FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON | FCF_MENU), NULL);
            WinInvalidateRect(hwndMainFrame, NULL, TRUE);
            WinUpdateWindow(hwndMainFrame);
            bFrameHidden = TRUE;
         } else {
            WinSetParent(hwndTitleBar, hwndMainFrame, FALSE);
            WinSetParent(hwndSysMenu,  hwndMainFrame, FALSE);
            WinSetParent(hwndMinMax,   hwndMainFrame, FALSE);
            WinSetParent(hwndMenuBar,  hwndMainFrame, FALSE);
            WinSendMsg(hwndMainFrame, WM_UPDATEFRAME,
               (MPARAM)(FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON | FCF_MENU), NULL);
            WinInvalidateRect(hwndMainFrame, NULL, TRUE);
            WinUpdateWindow(hwndMainFrame);
            bFrameHidden = FALSE;
         }
         WinCheckMenuItem(hwndMenu, IDM_FRAME_CTRL, bFrameHidden);
      }
      break;

   case IDM_SOUND_ON:
      bSound = 1;/*��� ����祭*/break;

   case IDM_SOUND_OFF:
      bSound = 0;/*��� �몫�祭*/break;

   case IDM_STYLE_2D:
      bStyle = 0;WinInvalidateRect(hwnd,NULL,FALSE);break;

   case IDM_STYLE_3D:
      bStyle = 1;WinInvalidateRect(hwnd,NULL,FALSE);break;

   case IDM_LEVEL_0:
   case IDM_LEVEL_1:
   case IDM_LEVEL_2:
   case IDM_LEVEL_3:
   case IDM_LEVEL_4:
   case IDM_LEVEL_5:
   case IDM_LEVEL_6:
   case IDM_LEVEL_7:
   case IDM_LEVEL_8:
   case IDM_LEVEL_9:
   case IDM_LEVEL_10:
   case IDM_LEVEL_11:
      //��࠭���� ����࠭���� ��। ���室�� �� ᫥���騩 �஢���
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      if(bStart && iScore != iBScore){
         usReturn = MessageBox(hwnd, IDMSG_SAVE," ",
                       MB_YESNOCANCEL | MB_INFORMATION, 0);
         if(usReturn == MBID_YES) FileSave(mp2); else
         if(usReturn == MBID_CANCEL) {
            if(bGame){//�᫨ 諠 ���,����᪠�� ���⭮
                  WinStartTimer(hab,hwnd,IDT_MOVE,100);
                  WinStartTimer(hab,hwnd,IDT_GAME,1000);}
            break;}}
      //���室 �� ᫥���騩 �஢���
      switch(SHORT1FROMMP(mp1)){
         case IDM_LEVEL_0: InitLevel(0); break;
         case IDM_LEVEL_1: InitLevel(1); break;
         case IDM_LEVEL_2: InitLevel(2); break;
         case IDM_LEVEL_3: InitLevel(3); break;
         case IDM_LEVEL_4: InitLevel(4); break;
         case IDM_LEVEL_5: InitLevel(5); break;
         case IDM_LEVEL_6: InitLevel(6); break;
         case IDM_LEVEL_7: InitLevel(7); break;
         case IDM_LEVEL_8: InitLevel(8); break;
         case IDM_LEVEL_9: InitLevel(9); break;
         case IDM_LEVEL_10:InitLevel(10);break;
         case IDM_LEVEL_11:InitLevel(11);break;}break;

      case IDM_SETTINGS_ALL:
      if(bGame){//�᫨ ���� ���
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      bChange = 0;//��������� �� ���
      /* �㭪�� ������� */
      WinDlgBox( HWND_DESKTOP,  /*��� ��㥬*/
         hwnd,            /*��������*/
         SettingsDlgProc, /*���������� ��楤��*/
         (HMODULE)0,         /*㪠��⥫� �����*/
         iLangBase+DLG_SETTINGS,    /*㪠��⥫� ������� � .rc*/
         NULL);              /*�� ��� � �㤠 ���*/
      /* �㭪�� ������� */
      if(bGame){//�᫨ ���� ���
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_LANGUAGE_EN:
   case IDM_LANGUAGE_NL:
   case IDM_LANGUAGE_ES:
   case IDM_LANGUAGE_DE:
   case IDM_LANGUAGE_FR:
   case IDM_LANGUAGE_IT:
      SetLanguage((int)SHORT1FROMMP(mp1)-IDM_LANGUAGE_EN);
      ApplyLanguage();
      UpdateTitleText(hwnd,0); break;

   case IDM_HELPINDEX:
      HelpIndex(); break;

   case IDM_HELPGENERAL:
      HelpGeneral(); break;

   case IDM_HELPUSINGHELP:
      HelpUsingHelp(); break;

   case IDM_HELPKEYS:
      HelpKeys(); break;

   case IDM_HELPPRODUCTINFO:
WinDlgBox(HWND_DESKTOP, hwndMain,
 	        (PFNWP)ProductInfoDlgProc, 0,
 	        iLangBase+DLG_ABOUTTHISPROGRAM, (PVOID)NULL);
      break;

   default: break;
   }
}   /* End of MainCommand  */
/**************************************************************************
 *  Name       : MainChar(HWND hwnd, MPARAM mp1, MPARAM mp2)
 *
 *  Description: ��뢠���� �� ����⨨ ������.
 *
 *  Concepts:    ��ࠡ��稪 ᮡ��� WM_CHAR .
 *
 *  API's      : [none]
 *
 *  Parameters : hmnd = 奭�� ����
 *               usVK = ����㠫�� ��� ������
 *               mp1 = first message parameter
 *               mp2 = second message parameter
 *************************************************************************/
VOID MainChar(HWND hwnd, MPARAM mp1, MPARAM mp2)
{  USHORT usVK;

   usVK = SHORT2FROMMP(mp2);
   switch(usVK){
      case VK_F2:
         mp1 = MPFROMSHORT(IDM_STYLE_2D);
         mp2 = MPFROMHWND(hwndMenu);
         WinPostMsg(hwnd, WM_COMMAND, mp1,mp2);break;

      case VK_F3:
         mp1 = MPFROMSHORT(IDM_STYLE_3D);
         mp2 = MPFROMHWND(hwndMenu);
         WinPostMsg(hwnd, WM_COMMAND, mp1,mp2);break;

      case VK_ESC://��室
         mp1 = MPFROMSHORT(IDM_FILEEXIT);
         WinPostMsg(hwnd, WM_COMMAND, mp1,mp2);break;

      case 0://�� ᯨ - ����৭���
         if(bGame){//�᫨ ���� ���
           Runner.xRight =  0;
           Runner.yTop   =  0;}break;

      case VK_RIGHT://���� ���ࠢ� - ���� �������
         if(bGame){//�᫨ ���� ���
            Runner.xRight =  1;
            Runner.yTop   =  0;}break;

      case VK_LEFT: //������ - ᪠��� ������
         if(bGame){//�᫨ ���� ���
            Runner.xRight = -1;
            Runner.yTop   =  0;}break;

      case VK_DOWN: //⠬ �㤥�, ⠬ ��訩 �த��
         if(bGame){//�᫨ ���� ���
            Runner.xRight =  0;
            Runner.yTop   = -1;}break;

      case VK_UP:   //��ᠫ�� �� ����� ᨤ��
         if(bGame){//�᫨ ���� ���
            Runner.xRight =  0;
            Runner.yTop   =  1;}break;

      case VK_SPACE:
      case VK_NEWLINE:
         mp1 = MPFROMSHORT(IDM_DIRECTION_START);
         WinPostMsg(hwnd, WM_COMMAND, mp1,mp2);break;

      default:break;}
}   /* End of MainCommand  */
/**************************************************************************
 *  Name       : MainTimer(ULONG ulTIMER)
 *
 *  Description: ��뢠���� �� ����祭�� ᮮ�饭�� �� ⠩��஢.
 *
 *  Concepts:    ��ࠡ��稪 ᮡ��� WM_TIMER .
 *
 *  API's      : [none]
 *
 *  Parameters : hmnd = 奭�� ����
 *     ulTIMER = �����䨪��� ⠩���
 *************************************************************************/
VOID MainTimer(HWND hwnd, ULONG ulTIMER)
{  HPS hps;
   int i;

   hps = WinGetPS(hwnd);
   switch(ulTIMER) { BOOL bMoveRunner;
      case IDT_MOVE ://��諮 �६� ���������
         if(Field[Runner.yBottom][Runner.xLeft] == CLR_FIELD){
            Field[Runner.yBottom][Runner.xLeft] = CLR_NEW;
            bNew = 1;}
         if(Runner.xRight || Runner.yTop){//������� ������
            Quatro(&hps,Runner.yBottom,Runner.xLeft);
            MoveRunner();
            bMoveRunner = 1;}
         for(i=0;i<QSize;i++) {//��ࠥ� ���� ��㦪�
            if(Balls[i].yTop){//�᫨ ����� ��� �������
               Quatro(&hps,Balls[i].yBottom,Balls[i].xLeft);
               if(MoveBall(i))CTPOKA(&hps,0);//�������
               Kpyr(&hps, Balls[i].yBottom,
                          Balls[i].xLeft, CLR_BALLS);}
            Quatro(&hps,Hunters[i].yBottom,Hunters[i].xLeft);
            MoveHunter(i);//�������
            Kpyr(&hps, Hunters[i].yBottom,//��㥬 ���� ��㦪�
                       Hunters[i].xLeft, CLR_HUNTERS);}
         if(bMoveRunner)//��㥬�� ������
            Kpyr(&hps, Runner.yBottom,Runner.xLeft, CLR_RUNNER);
         /* �஢�ઠ �� ��� */
         for(i=0;i<QSize;i++) {
            if (Field[Balls[i].yBottom][Balls[i].xLeft] == CLR_NEW ||
               (Balls[i].xLeft   == Runner.xLeft &&
                Balls[i].yBottom == Runner.yBottom)) {
               Replace(CLR_NEW,CLR_BREAK,&hps);bNew = 0;
               if(bSound) DosBeep(100,500);
               else DosSleep(500);
               Replace(CLR_BREAK,CLR_FIELD,&hps);
               Quatro(&hps,Runner.yBottom,Runner.xLeft);
               Runner.xLeft   = Memory.x;//���� �������
               Runner.yBottom = Memory.y;bNew = 0;/*���� �� ����塞*/
               Runner.xRight = 0;Runner.yTop   = 0;//�⮨�
               Kpyr(&hps, Balls[i].yBottom,Balls[i].xLeft, CLR_BALLS);
               Kpyr(&hps, Runner.yBottom,Runner.xLeft, CLR_RUNNER);
               iScore -= 50;CTPOKA(&hps,0);/*��樠��! ���*/}
            if (Hunters[i].xLeft   == Runner.xLeft &&
                Hunters[i].yBottom == Runner.yBottom) {
               if(bSound) DosBeep(100,500);
               else DosSleep(500);
               Quatro(&hps,Hunters[i].yBottom,Hunters[i].xLeft);
               MoveHunter(i);//�������
               Kpyr(&hps, Hunters[i].yBottom,//��㥬 ���� ��㦪�
                          Hunters[i].xLeft, CLR_HUNTERS);
               Kpyr(&hps, Runner.yBottom,//��㥬 ���� ��㦮�
                          Runner.xLeft, CLR_RUNNER);
               iScore -= 50;CTPOKA(&hps,0);/*��樠��! ���*/}}
         /* ����� �஢�ન �� ��� */
         if(Field[Runner.yBottom][Runner.xLeft] == CLR_CHANNEL){
            if(bNew){
               int j;long lMax;

               WinStopTimer(hab,hwnd,IDT_MOVE);
               WinStopTimer(hab,hwnd,IDT_GAME);
               if(bHalt){//��⠭����������
                  Runner.xRight = 0;Runner.yTop   = 0;}
               /*��墠� ����਩*/
               lMax = 100;//�.�.>15 (梥� CLR_* �� -5 �� 15)
               for(i=1;i<Col-1;i++)
                  for(j=1;j<Row-1;j++){
                     if (Field[j][i] == CLR_FIELD)//����-�㦭� �஢�ઠ
                        if (Field[j-1][i] < 100 &&//᭨��-�㦨�
                            Field[j][i-1] < 100){//� ᧠��-�㦨�
                           Field[j][i] = ++lMax;}//�㬥�㥬
                        else if (Field[j-1][i] < 100)//᭨��-�㦨�
                           Field[j][i] = Field[j][i-1];//��६ ᧠��
                        else if (Field[j][i-1] < 100)//᧠��-�㦨�
                           Field[j][i] = Field[j-1][i];//��६ ᭨��
                        else {//�� ᢮�����
                           Field[j][i] = Field[j-1][i];//��६ ᭨��
                           if (Field[j-1][i] != Field[j][i-1])//�᫨ ���!=���
                              Replace(Field[j][i-1],Field[j-1][i],NULL);}/*of else*/}//of if
               //ᬮ�ਬ ������ १�ࢠ樨
               for(i=0;i<QSize;i++) if(Field[Balls[i].yBottom][Balls[i].xLeft] > 100)
                  Replace(Field[Balls[i].yBottom][Balls[i].xLeft],CLR_FIELD,NULL);
               //��⨬ �� ��⠫쭮� ��� �����
               for(i=1;i<Col-1;i++)
                  for(j=1;j<Row-1;j++)
                     if(Field[j][i] > 100) Field[j][i] = CLR_NEW;
               /*����� ��墠� ����਩*/
               Replace(CLR_NEW, CLR_CHANNEL, &hps );//���塞 訫� �� �뫮
               CTPOKA(&hps,0);//��樠��! ���
               if(bSound) {//���� ������
                  DosBeep(500,50);
                  DosBeep(1000,50);
                  DosBeep(2000,50);}
               WinStartTimer(hab,hwnd,IDT_MOVE,100);
               WinStartTimer(hab,hwnd,IDT_GAME,1000);}//if(bNew)
            Memory.x = Runner.xLeft;//���� �������
            Memory.y = Runner.yBottom;
            bNew = 0;/*���� �� ����塞*/}break;

      case IDT_GAME ://� �६� ����
         usTime -= 1;
         if(iScore - iOScore > ((Row-2)*(Col-2)*4)/5 ||//�� �먣ࠫ�
           (iScore - iOScore > ((Row-2)*(Col-2)*2)/3 &&
            usTime == 0 )) {
            if(bGame){//�᫨ ���� ���
               WinStopTimer(hab,hwnd,IDT_MOVE);
               WinStopTimer(hab,hwnd,IDT_GAME);}
            if (usLevel < MAXLEVEL) {//���室 �� ᫥���騩 �஢���
               MessageBox(hwnd, IDMSG_OK," ",
                  MB_OK | MB_INFORMATION, 0);//⨯� ok
               iOScore = iScore;//���������� ���� �窨
               usLevel++;
               InitNewGame(1);
               WinInvalidateRect(hwnd,NULL,FALSE);}
            else {//��諨 �� �।���
               MessageBox(hwnd, IDMSG_CONGRATULATIONS,
                  " ", MB_OK | MB_INFORMATION, 0);//����ࠢ�����
               if(iScore > iHScore) HScoresPrf(2);//����ᥭ�� � HighScores
               bStart = 0; bGame = 0;}}
         else if(iScore - iOScore < ((Row-2)*(Col-2)*2)/3 &&
                 usTime == 0 ) {//�ந�ࠫ
                  bStart = 0;
                  if(bGame){//�᫨ ���� ���
                     bGame =0;//��⠭��������
                     WinStopTimer(hab,hwnd,IDT_MOVE);
                     WinStopTimer(hab,hwnd,IDT_GAME);}
                  if(iScore > iHScore) HScoresPrf(1);//����ᥭ�� � HighScores
                  else MessageBox(hwnd, IDMSG_SORRY," ",
                                    MB_OK | MB_INFORMATION, 0);}//�ந�ࠫ
         else CTPOKA(&hps,2);break;

   default:break;}/*of switch*/
   WinReleasePS(hps);
}   /* End of MainCommand  */
/***************************  End of main.c  ****************************/

