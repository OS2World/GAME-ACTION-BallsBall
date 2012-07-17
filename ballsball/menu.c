/**************************************************************************
 *  File name  :  menu.c
 *
 *  Description:  файл с пользовательскими командами
 *		  по управлению меню.
 *
 *		  This source file contains the following functions:
 *
 *		  InitMenu(MPARAM mp1, MPARAM mp2)
 *		  EnableMenuItem(HWND hwndMenu, USHORT idItem, BOOL fEnable)
 *                MenuRedraw(MPARAM mp2, int iMenu)
 *		
 *  Concepts   :  message processing
 *
 *  API's      :
 *		
 *
 *    Files    :  OS2.H, MAIN.H, DLG.H, XTRN.H, GAME.H
 *************************************************************************/

/* Include files, macros, defined constants, and externs */

#define INCL_WINMENUS

#include <os2.h>
#include "game.h"
#include "main.h"
#include "dlg.h"
#include "xtrn.h"

/* Global variables */


/* Entry point declarations */

/**************************************************************************
 *
 *  Name       : InitMenu()
 *
 *  Description: Processes the WM_INITMENU message for the main window,
 *		 disabling any menus that are not active.
 *
 *  Concepts:	 Routine is called each time a menu is dropped.
 *
 *		 A switch statement branches control based upon
 *		 the id of the menu that is being displayed.
 *
 *  API's      :  [none]
 *
 *  Parameters :  mp1  = first message parameter
 *		  mp2  = second message parameter
 *************************************************************************/
VOID InitMenu(MPARAM mp1, MPARAM mp2)
{  /* define a shorthand way of denoting the menu handle */
   hwndMenu = HWNDFROMMP(mp2);

   switch(SHORT1FROMMP(mp1)) {

   case IDM_SOUND:
      MenuRedraw(bSound-7); break;

   case IDM_STYLE:
      MenuRedraw(bStyle-9); break;

   case IDM_LEVEL:
      MenuRedraw(-1);
      MenuRedraw(usLevel); break;

   case IDM_HELP:
      EnableMenuItem(hwndMenu, IDM_HELPUSINGHELP, fHelpEnabled);
      EnableMenuItem(hwndMenu, IDM_HELPGENERAL, fHelpEnabled);
      EnableMenuItem(hwndMenu, IDM_HELPKEYS, fHelpEnabled);
      EnableMenuItem(hwndMenu, IDM_HELPINDEX, fHelpEnabled); break;

    default: break; }

}   /* End of InitMenu	 */
/**************************************************************************
 *
 *  Name       : EnableMenuItem(hwndMenu, idItem, fEnable)
 *
 *  Description: Enables or disables the menu item
 *
 *  Concepts:	 Called whenever a menu item is to be enabled or
 *		 disabled
 *
 *		 Sends a MM_SETITEMATTR to the menu with the
 *		 given item id.	 Sets the MIA_DISABLED attribute
 *		 flag if the item is to be disabled, clears the flag
 *		 if enabling.
 *
 *  API's      : WinSendMsg
 *
 *  Parameters :  hwndmenu = menu window handle
 *		  idItem   = menu item i.d.
 *		  fEnable  = enable (yes) or disable (no)
 *
 *  Return     :  [none]
 *
 *************************************************************************/
VOID EnableMenuItem(HWND hwndMenu, USHORT idItem, BOOL fEnable)
{  SHORT fsFlag;

   if(fEnable) fsFlag = 0;
   else        fsFlag = MIA_DISABLED;
   WinSendMsg(hwndMenu, MM_SETITEMATTR,
	      MPFROM2SHORT(idItem, TRUE),
	      MPFROM2SHORT(MIA_DISABLED, fsFlag));
}   /* End of EnableMenuItem() */
/**************************************************************************
 *
 *  Name       : MenuRedraw()
 *
 *  Description: ставит и убирает галочки в под меню
 *
 *
 *  Concepts:	 посылает сообщение в меню и в зависимости от
 *     входного параметра iMenu заставляет ставить и
 *     убирать галочки
 *
 *
 *  API's      :  [none]
 *
 *  Parameters :
 *		  mp2   = second message parameter
 *      iMenu = где именно ставить и убирать галки
 *************************************************************************/
VOID MenuRedraw(int iMenu)
{  /* define a shorthand way of denoting the menu handle */
   switch(iMenu) {
   case -6://включаем звук
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndPopupMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndPopupMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -7://выключаем звук
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndPopupMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndPopupMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -9://2D
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_2D,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_3D,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -8://3D
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_3D,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_2D,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -1://убираем галки из левелов
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_0,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_1,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_2,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_3,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_4,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_5,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_6,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_7,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_8,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_9,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_10,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//убираем галочку
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_11,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case 0://ставим галку на 0-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_0,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 1://ставим галку на 1-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_1,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 2://ставим галку на 2-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_2,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 3://ставим галку на 3-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_3,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 4://ставим галку на 4-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_4,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 5://ставим галку на 5-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_5,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 6://ставим галку на 6-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_6,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 7://ставим галку на 7-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_7,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 8://ставим галку на 8-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_8,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 9://ставим галку на 9-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_9,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 10://ставим галку на 10-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_10,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 11://ставим галку на 11-й левел
      WinSendMsg(hwndMenu,//метим галочкой
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_11,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

    default: break; }
}   /* End of InitMenu	 */
/***************************  End of user.c  ****************************/
