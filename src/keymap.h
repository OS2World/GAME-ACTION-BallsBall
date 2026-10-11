/**************************************************************************
 *  File name  :  keymap.h
 *
 *  Description:  Keyboard and joystick mapping ("Key Mapping..." dialog).
 *************************************************************************/
#ifndef KEYMAP_H
#define KEYMAP_H

/* actions of the game */
#define ACT_LEFT      0
#define ACT_RIGHT     1
#define ACT_UP        2
#define ACT_DOWN      3
#define ACT_START     4     /* start / pause */
#define ACT_STOP      5     /* stop the runner (joystick only; any other key stops it) */
#define KM_ACTIONS    6
#define KM_KEYACTS    5     /* the first five can be mapped to a key */

#define IDT_JOY       2002  /* joystick polling timer */

VOID   KmInit(VOID);                      /* open the joystick driver */
VOID   KmDone(VOID);
VOID   KmLoad(HINI hini);                 /* mappings from bb.ini     */
VOID   KmSave(HINI hini);
INT    KmKeyAction(MPARAM mp1, MPARAM mp2);   /* WM_CHAR -> action or -1 */
VOID   KmJoyPoll(VOID);                   /* called by the IDT_JOY timer */
VOID   KmDialog(HWND hwndOwner);          /* the dialog               */

/* implemented in main.c */
VOID   RunnerAction(INT act);

#endif
