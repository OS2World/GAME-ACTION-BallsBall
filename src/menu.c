/**************************************************************************
 *  File name  :  menu.c
 *
 *  Description:  䠩� � ���짮��⥫�᪨�� ���������
 *		  �� �ࠢ����� ����.
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
#define INCL_WINWINDOWMGR

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

   case IDM_LANGUAGE:
      MenuRedraw(-21-iLang); break;

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
 *  Description: �⠢�� � 㡨ࠥ� ����窨 � ��� ����
 *
 *
 *  Concepts:	 ���뫠�� ᮮ�饭�� � ���� � � ����ᨬ��� ��
 *     �室���� ��ࠬ��� iMenu ���⠢��� �⠢��� �
 *     㡨��� ����窨
 *
 *
 *  API's      :  [none]
 *
 *  Parameters :
 *		  mp2   = second message parameter
 *      iMenu = ��� ������ �⠢��� � 㡨��� �����
 *************************************************************************/
VOID MenuRedraw(int iMenu)
{  /* define a shorthand way of denoting the menu handle */
   switch(iMenu) {
   case -6://����砥� ���
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndPopupMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndPopupMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -7://�몫�砥� ���
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndPopupMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_OFF,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndPopupMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_SOUND_ON,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -9://2D
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_2D,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_3D,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -8://3D
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_3D,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_STYLE_2D,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case -1://㡨ࠥ� ����� �� �������
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_0,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_1,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_2,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_3,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_4,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_5,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_6,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_7,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_8,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_9,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_10,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_11,
         MPFROM2SHORT(MIA_CHECKED,0)); break;

   case 0://�⠢�� ����� �� 0-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_0,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 1://�⠢�� ����� �� 1-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_1,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 2://�⠢�� ����� �� 2-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_2,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 3://�⠢�� ����� �� 3-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_3,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 4://�⠢�� ����� �� 4-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_4,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 5://�⠢�� ����� �� 5-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_5,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 6://�⠢�� ����� �� 6-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_6,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 7://�⠢�� ����� �� 7-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_7,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 8://�⠢�� ����� �� 8-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_8,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 9://�⠢�� ����� �� 9-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_9,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 10://�⠢�� ����� �� 10-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_10,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case 11://�⠢�� ����� �� 11-� �����
      WinSendMsg(hwndMenu,//��⨬ ����窮�
         MM_SETITEMATTR,(MPARAM)IDM_LEVEL_11,
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

   case -21://����
   case -22://�������,���
   case -23://��������,���
   case -24://��������,���
   case -25://��������,���
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LANGUAGE_EN,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LANGUAGE_NL,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LANGUAGE_ES,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LANGUAGE_DE,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//㡨ࠥ� ������
         MM_SETITEMATTR,(MPARAM)IDM_LANGUAGE_FR,
         MPFROM2SHORT(MIA_CHECKED,0));
      WinSendMsg(hwndMenu,//�⠢�� ������
         MM_SETITEMATTR,(MPARAM)(IDM_LANGUAGE_EN+iLang),
         MPFROM2SHORT(MIA_CHECKED,MIA_CHECKED)); break;

    default: break; }
}   /* End of InitMenu	 */
/**************************************************************************
 *
 *  Name       : MenuSetLanguage(HWND hwndM)
 *
 *  Description: Re-texts every menu item of one menu window from the
 *		 current language's string table.
 *
 *  Concepts:	 The menu structure (identifiers, separators) is the
 *		 same in every language, only the text differs, so the
 *		 English skeleton menu is re-texted at run time.
 *
 *  API's      : WinLoadString, WinSendMsg(MM_SETITEMTEXT)
 *
 *************************************************************************/
static void MenuSetLanguage(HWND hwndM)
{  CHAR sz[128];

   #define LSET(id, ids) \
      if(WinLoadString(hab,(HMODULE)0, iLangBase+(ids), sizeof(sz), sz)) \
         WinSetMenuItemText(hwndM,(id),sz);
   LSET(IDM_FILE,    IDS_MEN_FILE)
   LSET(IDM_FILENEW, IDS_MEN_NEW)
   LSET(IDM_FILEOPEN,IDS_MEN_LOAD)
   LSET(IDM_FILESAVE,IDS_MEN_SAVE)
   LSET(IDM_FILESAVEAS,IDS_MEN_SAVEAS)
   LSET(IDM_DIRECTION_START,IDS_MEN_START)
   LSET(IDM_HIGHSCORES,IDS_MEN_HSCORES)
   LSET(IDM_FILEEXIT,IDS_MEN_EXIT)
   LSET(IDM_SETTINGS,IDS_MEN_SETTINGS)
   LSET(IDM_SOUND,   IDS_MEN_SOUND)
   LSET(IDM_SOUND_ON,IDS_MEN_SOUNDON)
   LSET(IDM_SOUND_OFF,IDS_MEN_SOUNDOFF)
   LSET(IDM_STYLE,   IDS_MEN_STYLE)
   LSET(IDM_STYLE_2D,IDS_MEN_STYLE2D)
   LSET(IDM_STYLE_3D,IDS_MEN_STYLE3D)
   LSET(IDM_LEVEL,   IDS_MEN_LEVEL)
   LSET(IDM_LANGUAGE,IDS_MEN_LANGUAGE)
   LSET(IDM_LANGUAGE_EN,IDS_MEN_LANG_EN)
   LSET(IDM_LANGUAGE_NL,IDS_MEN_LANG_NL)
   LSET(IDM_LANGUAGE_ES,IDS_MEN_LANG_ES)
   LSET(IDM_LANGUAGE_DE,IDS_MEN_LANG_DE)
   LSET(IDM_LANGUAGE_FR,IDS_MEN_LANG_FR)
   LSET(IDM_SETTINGS_ALL,IDS_MEN_SETTINGS_ALL)
   LSET(IDM_HELP,    IDS_MEN_HELP)
   LSET(IDM_HELPGENERAL,IDS_MEN_HELPGENERAL)
   LSET(IDM_HELPINDEX,IDS_MEN_HELPINDEX)
   LSET(IDM_HELPUSINGHELP,IDS_MEN_HELPUSING)
   LSET(IDM_HELPKEYS,IDS_MEN_HELPKEYS)
   LSET(IDM_HELPPRODUCTINFO,IDS_MEN_HELPPROD)
   #undef LSET
}   /* End of MenuSetLanguage */
/**************************************************************************
 *
 *  Name       : ReMenuSub(HWND hwndMenuWin, USHORT usItem)
 *
 *  Description: Re-texts the pull-down window attached to the given
 *		 submenu item of the given menu window, if any.
 *
 *  Concepts:	 Each pull-down menu is its own menu window, so it must be
 *		 re-texted separately.  The handle of the pull-down window
 *		 is obtained by querying the submenu item in its parent
 *		 menu window.
 *
 *  API's      : WinSendMsg(MM_QUERYITEM), MenuSetLanguage
 *
 *  Parameters :  hwndMenuWin  = parent menu window
 *		  usItem      = id of the submenu item
 *************************************************************************/
static VOID ReMenuSub(HWND hwndMenuWin, USHORT usItem)
{  MENUITEM mi;

   if((MRESULT)0 != WinSendMsg(hwndMenuWin, MM_QUERYITEM,
                  MPFROM2SHORT(usItem, TRUE), (MPARAM)&mi)
      && mi.hwndSubMenu != NULLHANDLE)
      MenuSetLanguage(mi.hwndSubMenu);
}   /* End of ReMenuSub */
/**************************************************************************
 *
 *  Name       : ApplyLanguage()
 *
 *  Description: Re-texts the main menu bar, all its pull-down menus, and
 *		 the popup menu for the selected language.  Called at
 *		 startup and whenever the language is changed.
 *
 *  Concepts:	 Every pull-down menu is a separate menu window, so the
 *		 texts are updated window by window: first the action bar
 *		 window itself, then each pull-down obtained through the
 *		 submenu item's hwndSubMenu.
 *
 *  API's      : WinWindowFromID, MenuSetLanguage, ReMenuSub
 *
 *************************************************************************/
VOID ApplyLanguage(VOID)
{  HWND    hwndMenuBar;
   MENUITEM mi;

   if(hwndMainFrame == NULLHANDLE)
      return;
   hwndMenuBar = WinWindowFromID(hwndMainFrame, FID_MENU);
   if(hwndMenuBar == NULLHANDLE)
      return;

   MenuSetLanguage(hwndMenuBar);            /* action bar items */

   if((MRESULT)0 != WinSendMsg(hwndMenuBar, MM_QUERYITEM,
                  MPFROM2SHORT(IDM_FILE, TRUE), (MPARAM)&mi)
      && mi.hwndSubMenu != NULLHANDLE)
      MenuSetLanguage(mi.hwndSubMenu);      /* File pull-down  */

   if((MRESULT)0 != WinSendMsg(hwndMenuBar, MM_QUERYITEM,
                  MPFROM2SHORT(IDM_SETTINGS, TRUE), (MPARAM)&mi)
      && mi.hwndSubMenu != NULLHANDLE)
   {  MenuSetLanguage(mi.hwndSubMenu);      /* Settings pull-down */
      ReMenuSub(mi.hwndSubMenu, IDM_SOUND);
      ReMenuSub(mi.hwndSubMenu, IDM_STYLE);
      ReMenuSub(mi.hwndSubMenu, IDM_LEVEL);
      ReMenuSub(mi.hwndSubMenu, IDM_LANGUAGE); }

   if((MRESULT)0 != WinSendMsg(hwndMenuBar, MM_QUERYITEM,
                  MPFROM2SHORT(IDM_HELP, TRUE), (MPARAM)&mi)
      && mi.hwndSubMenu != NULLHANDLE)
      MenuSetLanguage(mi.hwndSubMenu);      /* Help pull-down   */

   if(hwndPopupMenu != NULLHANDLE)
      MenuSetLanguage(hwndPopupMenu);       /* popup menu       */
}   /* End of ApplyLanguage */
/***************************  End of user.c  ****************************/
