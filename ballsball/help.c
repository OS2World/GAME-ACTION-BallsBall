/**************************************************************************
 *  File name  :  help.c
 *
 *  Description:  This module contains all the routines for interfacing
 *		  the IPF Help Manager.
 *
 *		  This source file contains the following functions:
 *
 *		  InitHelp()
 *		  HelpIndex()
 *		  HelpGeneral()
 *		  HelpUsingHelp()
 *		  HelpKeys()
 *		  HelpProductInfo() - ᮪�⨫
 *		  DisplayHelpPanel(idPanel)
 *		  DestroyHelpInstance()
 *
 *  Concepts   :  help manager
 *
 *  API's      :  WinLoadString
 *		  WinCreateHelpInstance
 *		  WinAssociateHelpInstance
 *		  WinSendMsg
 *		  WinDlgBox
 *		  WinDestroyHelpInstance
 *		  WinMessageBox
 *		  WinAlarm
 *
 *    Files   : OS2.H, STRING.H, MAIN.H, DLG.H, HELP.H, XTRN.H
 *************************************************************************/

/* Include files, macros, defined constants, and externs */

#define	 INCL_WINHELP

#include <os2.h>
#include <string.h>
#include "main.h"
#include "dlg.h"
#include "help.h"
#include "xtrn.h"

#define HELPLIBRARYNAMELEN  20

/* Global variables */
static HWND hwndHelpInstance;
static CHAR szLibName[HELPLIBRARYNAMELEN];
static CHAR szWindowTitle[HELPLIBRARYNAMELEN];

/* Entry point declarations */
//MRESULT EXPENTRY ProductInfoDlgProc(HWND hwnd,
//				    ULONG msg, MPARAM mp1, MPARAM mp2);
/**************************************************************************
 *
 *  Name       : InitHelp()
 *
 *  Description:  Initializes the IPF help facility
 *
 *  Concepts:	  Called once during initialization of the program
 *
 *		  Initializes the HELPINIT structure and creates the
 *		  help instance.  If successful, the help instance
 *		  is associated with the main window.
 *
 *  API's      :  WinLoadString
 *		  WinCreateHelpInstance
 *		  WinAssociateHelpInstance
 *************************************************************************/
VOID InitHelp(VOID)
{  HELPINIT hini;

   /* if we return because of an error, Help will be disabled */
   fHelpEnabled = FALSE;

   /* initialize help init structure */
   hini.cb = sizeof(HELPINIT);
   hini.ulReturnCode = 0;

   hini.pszTutorialName = (PSZ)NULL;   /* if tutorial added, add name here */

   hini.phtHelpTable = (PHELPTABLE)MAKELONG(TEMPLATE_HELP_TABLE, 0xFFFF);
   hini.hmodHelpTableModule = 0;
   hini.hmodAccelActionBarModule = 0;
   hini.idAccelTable = 0;
   hini.idActionBar = 0;

   if(!WinLoadString(hab,
		     (HMODULE)0,
		     IDS_HELPWINDOWTITLE,
		     HELPLIBRARYNAMELEN,
		     (PSZ)szWindowTitle)){
      MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
         (PSZ)NULL, MB_OK | MB_ERROR, FALSE); return; }

   hini.pszHelpWindowTitle = (PSZ)szWindowTitle;

   /* if debugging, show panel ids, else don't */
#ifdef DEBUG
   hini.fShowPanelId = CMIC_SHOW_PANEL_ID;
#else
   hini.fShowPanelId = CMIC_HIDE_PANEL_ID;
#endif

   if(!WinLoadString(hab,
		     (HMODULE)0,
		     IDS_HELPLIBRARYNAME,
		     HELPLIBRARYNAMELEN,
		     (PSZ)szLibName)) {
      MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
         (PSZ)NULL, MB_OK | MB_ERROR, FALSE); return; }

   hini.pszHelpLibraryName = (PSZ)szLibName;

   /* creating help instance */
   hwndHelpInstance = WinCreateHelpInstance(hab, &hini);

   if(hwndHelpInstance == NULLHANDLE || hini.ulReturnCode) {
      MessageBox(hwndMainFrame, IDMSG_HELPLOADERROR,
         (PSZ)NULL, MB_OK | MB_ERROR, TRUE); return; }

   /* associate help instance with main frame */
   if(!WinAssociateHelpInstance(hwndHelpInstance, hwndMainFrame)) {
      MessageBox(hwndMainFrame, IDMSG_HELPLOADERROR,
         (PSZ)NULL, MB_OK | MB_ERROR, TRUE); return; }

   /* help manager is successfully initialized so set flag to TRUE */
   fHelpEnabled = TRUE;
}   /* End of InitHelp	 */
/**************************************************************************
 *
 *  Name       : HelpGeneral()
 *
 *  Description: Processes the WM_COMMAND message posted by the
 *		 General Help item of the Help menu.
 *
 *  Concepts:	 Called from MainCommand when the General Help
 *		 menu item is selected.
 *
 *		 Sends an HM_EXT_HELP message to the help
 *		 instance so that the default Extended Help is
 *		 displayed.
 *
 *  API's      : WinSendMsg
 *************************************************************************/
VOID  HelpGeneral(VOID)
{  /* this just displays the system extended help panel */
   if(fHelpEnabled)
      if(NULL != WinSendMsg(hwndHelpInstance, HM_EXT_HELP,
			    (MPARAM)NULL, (MPARAM)NULL))
	 MessageBox(hwndMain, IDMSG_HELPDISPLAYERROR, (PSZ)NULL,
		    MB_OK | MB_ERROR, FALSE);
}   /* End of HelpGeneral  */
/**************************************************************************
 *
 *  Name       : HelpUsingHelp()
 *
 *  Description: Processes the WM_COMMAND message posted by the
 *		 Using Help item of the Help menu.
 *
 *  Concepts:	 Called from MainCommand when the Using Help
 *		 menu item is selected.
 *
 *		 Sends an HM_DISPLAY_HELP message to the help
 *		 instance so that the default Using Help is
 *		 displayed.
 *
 *  API's      : WinSendMsg
 *************************************************************************/
VOID  HelpUsingHelp(VOID)
{  /* this just displays the system help for help panel */
   if(fHelpEnabled)
      if(NULL != WinSendMsg(hwndHelpInstance, HM_DISPLAY_HELP,
			    (MPARAM)NULL, (MPARAM)NULL))
	 MessageBox(hwndMain, IDMSG_HELPDISPLAYERROR, (PSZ)NULL,
		    MB_OK | MB_ERROR, FALSE);
}   /* End of HelpUsingHelp   */
/**************************************************************************
 *
 *  Name       : HelpKeys()
 *
 *  Description: Processes the WM_COMMAND message posted by the
 *		 Keys Help item of the Help menu.
 *
 *  Concepts:	 Called from MainCommand when the Keys Help
 *		 menu item is selected.
 *
 *		 Sends an HM_KEYS_HELP message to the help
 *		 instance so that the default Keys Help is
 *		 displayed.
 *
 *  API's      : WinSendMsg
 *************************************************************************/
VOID  HelpKeys(VOID)
{  /* this just displays the system keys help panel */
   if(fHelpEnabled)
      if(NULL != WinSendMsg(hwndHelpInstance, HM_KEYS_HELP,
			    (MPARAM)NULL, (MPARAM)NULL))
	 MessageBox(hwndMain, IDMSG_HELPDISPLAYERROR, (PSZ)NULL,
		    MB_OK | MB_ERROR, FALSE);
}   /* End of HelpKeys	 */
/**************************************************************************
 *
 *  Name       : HelpIndex()
 *
 *  Description: Processes the WM_COMMAND message posted by the
 *		 Help Index item of the Help menu.
 *
 *  Concepts:	 Called from MainCommand when the Help Index
 *		 menu item is selected.
 *
 *		 Sends an HM_INDEX_HELP message to the help
 *		 instance so that the default Help Index is
 *		 displayed.
 *
 *  API's      : WinSendMsg
 *************************************************************************/
VOID  HelpIndex(VOID)
{  /* this just displays the system help index panel */
   if(fHelpEnabled)
      if(NULL != WinSendMsg(hwndHelpInstance, HM_HELP_INDEX,
			     (MPARAM)NULL, (MPARAM)NULL))
	 MessageBox(hwndMain, IDMSG_HELPDISPLAYERROR, (PSZ)NULL,
		    MB_OK | MB_ERROR, FALSE);
}   /* End of HelpIndex() */
/**************************************************************************
 *
 *  Name       : HelpProductInfo()
 *
 *  Description: Processes the WM_COMMAND message posted by the
 *		 Product information item of the Help Menu.
 *
 *  Concepts:	 Called from MainCommand when the Product information
 *		 menu item is selected
 *
 *		 Calls WinDlgBox to display the Product information dialog.
 *
 *  API's      : WinDlgBox
 *************************************************************************/
//VOID  HelpProductInfo(VOID)
//{  /* display the Product Information dialog. */
//   WinDlgBox(HWND_DESKTOP, hwndMain,
//	     (PFNWP)ProductInfoDlgProc, 0,
//	     DLG_ABOUTTHISPROGRAM, (PVOID)NULL);
//}   /* End of HelpProductInfo() */
/**************************************************************************
 *
 *  Name       : DisplayHelpPanel(idPanel)
 *
 *  Description: Displays the help panel whose id is given
 *
 *  Concepts:	 Called whenever a help panel is desired to be
 *		 displayed, usually from the WM_HELP processing
 *		 of the dialog boxes.
 *
 *		 Sends HM_DISPLAY_HELP message to the help instance.
 *
 *  API's      : WinSendMsg
 *
 *  Parameters :  idPanel = panel i.d.
 *
 *  Return     :  [none]
 *
 *************************************************************************/
VOID DisplayHelpPanel(ULONG idPanel)
{
   if(fHelpEnabled)
      if(NULL != WinSendMsg(hwndHelpInstance,
			    HM_DISPLAY_HELP,
			    MPFROMLONG(idPanel),
			    MPFROMSHORT(HM_RESOURCEID)))
	 MessageBox(hwndMainFrame, IDMSG_HELPDISPLAYERROR,
       (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
}   /* End of DisplayHelpPanel */
/**************************************************************************
 *
 *  Name       : DestroyHelpInstance()
 *
 *  Description: Destroys the help instance for the application
 *
 *  Concepts:	 Called after exit from message loop.
 *
 *		 Calls WinDestroyHelpInstance() to destroy the
 *		 help instance.
 *
 *  API's      : WinDestroyHelpInstance
 *************************************************************************/
VOID DestroyHelpInstance(VOID)
{
   if(hwndHelpInstance != NULLHANDLE)
      WinDestroyHelpInstance(hwndHelpInstance);
}   /* End of DestroyHelpInstance   */
/***************************  End of help.c  ****************************/

