/**************************************************************************
 *  File name  :  file.c
 *
 *  Description:  This module contains the code for the WM_COMMAND messages
 *		  posted by the standard File menu.
 *
 *		  This source file contains the following functions:
 *
 *		  FileOpen(mp2);
 *		  FileSave(mp2);
 *		  FileSaveAs(mp2);
 *		  GetFileName();
 *		  UpdateTitleText(hwnd,bNew);
 *		  TemplateOpenFilterProc(hwnd, msg, mp1, mp2)
 *		  TemplateSaveFilterProc(hwnd, msg, mp1, mp2)
 *
 *  Concepts   :  file management
 *
 *  API's      :  WinLoadString
 *		  WinFileDlg
 *		  WinSetWindowText
 *		  WinWindowFromID
 *		  WinDefFileDlgProc
 *
 *  Required
 *    Files    :  OS2.H, STRING.H, MAIN.H, HELP.H, XTRN.H, GAME.H,
 *      STDLIB.H
 *************************************************************************/
/* Include files, macros, defined constants, and externs */

#define INCL_WINFRAMEMGR
#define INCL_WINSWITCHLIST
#define INCL_WINSTDFILE
#define INCL_WINSHELLDATA

#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "game.h"
#include "xtrn.h"
#include "help.h"

/* Global variables */

CHAR szFullPath[CCHMAXPATH] = "";

/* Entry point declarations */

/**************************************************************************
 *
 *  Name       : FileOpen(mp2)
 *
 *  Description: Processes the File menu's Open item
 *
 *  Concepts:  Called whenever OPEN from the FILE menu is selected
 *
 *	       Calls the standard file open dialog to get the
 *	       file name.  The file name is passed onto DosOpen
 *	       which returns the handle to the file.  The file
 *	       input procedure is called and then the file handle
 *	       is closed.
 *
 *  API's      : WinLoadString
 *		 WinFileDlg
 *		 DosOpen
 *		 DosClose
 *
 *  Parameters :  mp2	   = second message parameter
 *************************************************************************/
VOID FileOpen(MPARAM mp2)
{  FILEDLG fdg;
   CHAR szTitle[MESSAGELEN], szButton[MESSAGELEN];
   HINI hini;//ini file handle
   //char szMsg[100];
   char szName[100];
   int i,j;
   int co,ro,qs;
   SHORT ti,le,ne,sc,os;
   long *(*fi);  //все поле
   RECTL ru,*ba,*hu;
   POINTL me;

   fdg.cbSize = sizeof(FILEDLG);

   if(!WinLoadString(hab, (HMODULE)0, IDS_OPEN, MESSAGELEN, szTitle) ||
      !WinLoadString(hab, (HMODULE)0, IDS_OPEN, MESSAGELEN, szButton)||
      !WinLoadString(hab, (HMODULE)0, IDS_FILEOPENEXT, CCHMAXPATH,
		     fdg.szFullFile)){
      MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
         (PSZ)NULL, MB_OK | MB_ERROR, TRUE);return;}

   fdg.pszTitle = szTitle;
   fdg.pszOKButton = szButton;
   fdg.ulUser = 0L;
   fdg.fl = FDS_HELPBUTTON | FDS_CENTER | FDS_OPEN_DIALOG;
   fdg.pfnDlgProc = (PFNWP)TemplateOpenFilterProc;
   fdg.lReturn = 0L;
   fdg.lSRC = 0L; fdg.hMod = 0;
   fdg.usDlgId = FILEOPEN;
   fdg.x = 0; fdg.y = 0;
   fdg.pszIType	      = (PSZ)NULL;
   fdg.papszITypeList = (PAPSZ)NULL;
   fdg.pszIDrive      = (PSZ)NULL;
   fdg.papszIDriveList= (PAPSZ)NULL;
   fdg.sEAType	       = (SHORT)0;
   fdg.papszFQFilename= (PAPSZ)NULL;
   fdg.ulFQFCount     = 0L;
   /* get the file */
   if(!WinFileDlg(HWND_DESKTOP, hwndMain, &fdg)) return;
   if(fdg.lReturn == ID_OK){//если нажали OK
      if((hini = PrfOpenProfile(hab,fdg.szFullFile))) {
         co = PrfQueryProfileInt(hini,"Size","Columns",0);
         ro = PrfQueryProfileInt(hini,"Size","Rows",0);
         qs = PrfQueryProfileInt(hini,"Size","Count of Balls",0);
         le = PrfQueryProfileInt(hini,"State","Level",-1);
         ti = PrfQueryProfileInt(hini,"State","Time",-1);
         ne = PrfQueryProfileInt(hini,"State","New",2);
         sc = PrfQueryProfileInt(hini,"Scores","Score",-1);
         os = PrfQueryProfileInt(hini,"Scores","Old Score",-1);
         if (co > 100 || co < 50 || ro > 60  || ro < 30 ||
             qs > 15  || qs < 4  || le > 11  || le < 0  ||
             ti > 180 || ti < 0  || ne > 1   || ne < 0  ||
             sc < 0   || os < 0  || os > sc  || qs != le+4) {
            PrfCloseProfile(hini);
            MessageBox(hwndMain, IDMSG_CANNOTOPENINPUTFILE,
               (PSZ)NULL,MB_OK | MB_ERROR, FALSE); return;}
         fi = malloc(ro*sizeof(*fi));
         for(i=0;i<ro;i++) fi[i] = malloc(co*sizeof(CLR_FIELD));
         //вертикальные линии
         for(i=0;i<ro;i++)fi[i][0]    = 1;
         for(i=0;i<ro;i++)fi[i][co-1] = 1;
         //горизонтальные линии
         for(j=0;j<co;j++)fi[0][j]    = 1;
         for(j=0;j<co;j++)fi[ro-1][j] = 1;
         for(i=1;i<ro-1;i++)//пишем поле
            for(j=1;j<co-1;j++) {
               sprintf(szName,"%d,%d",i,j);
               fi[i][j] = PrfQueryProfileInt(hini,"Field",szName,-1);
               if( fi[i][j] >3 || fi[i][j] < 0) {
                  PrfCloseProfile(hini);
                  free(fi);
                  MessageBox(hwndMain, IDMSG_CANNOTOPENINPUTFILE,
                     (PSZ)NULL,MB_OK | MB_ERROR, FALSE); return;}}
         /*дальше-шарики,проверка и переприсвоение*/
         hu=malloc(sizeof(Runner)*qs);//выделение памяти
         ba=malloc(sizeof(Runner)*qs);//выделение памяти
         for(i=0;i<qs;i++) {
            sprintf(szName,"xLeft%d",i);
            ba[i].xLeft = PrfQueryProfileInt(hini,"Balls",szName,-1);
            hu[i].xLeft = PrfQueryProfileInt(hini,"Hunters",szName,-1);
            sprintf(szName,"xRight%d",i);
            ba[i].xRight = PrfQueryProfileInt(hini,"Balls",szName,2);
            hu[i].xRight = PrfQueryProfileInt(hini,"Hunters",szName,2);
            sprintf(szName,"yBottom%d",i);
            ba[i].yBottom = PrfQueryProfileInt(hini,"Balls",szName,-1);
            hu[i].yBottom = PrfQueryProfileInt(hini,"Hunters",szName,-1);
            sprintf(szName,"yTop%d",i);
            ba[i].yTop = PrfQueryProfileInt(hini,"Balls",szName,2);
            hu[i].yTop = PrfQueryProfileInt(hini,"Hunters",szName,2);
            if(ba[i].xLeft   <0 || ba[i].xLeft   > co-1 ||
               ba[i].yBottom <0 || ba[i].yBottom > ro-1 ||
               abs(ba[i].xRight) !=1 || abs(ba[i].yTop) !=1 ||
               fi[ba[i].yBottom][ba[i].xLeft] !=0       ||
               hu[i].xLeft   <0 || hu[i].xLeft   > co-1 ||
               hu[i].yBottom <0 || hu[i].yBottom > ro-1 ||
               abs(hu[i].xRight+hu[i].yTop) !=1 ||
               fi[hu[i].yBottom][hu[i].xLeft] !=1 ){
               PrfCloseProfile(hini);
               free(fi); free(hu); free(ba);
               MessageBox(hwndMain, IDMSG_CANNOTOPENINPUTFILE,
                  (PSZ)NULL,MB_OK | MB_ERROR, FALSE); return;}}
         ru.xLeft   = PrfQueryProfileInt(hini,"Runner","xLeft"  ,-1);
         ru.xRight  = PrfQueryProfileInt(hini,"Runner","xRight" ,2);
         ru.yBottom = PrfQueryProfileInt(hini,"Runner","yBottom",-1);
         ru.yTop    = PrfQueryProfileInt(hini,"Runner","yTop"   ,2);
         me.x = PrfQueryProfileInt(hini,"Memory","x"   ,-1);
         me.y = PrfQueryProfileInt(hini,"Memory","y"   ,-1);
         PrfCloseProfile(hini);
         if (ru.xLeft   <0 || ru.xLeft   > co-1 ||
             ru.yBottom <0 || ru.yBottom > ro-1 ||
             (abs(ru.xRight+ru.yTop) != 0 &&
              abs(ru.xRight+ru.yTop) != 1) ||
             me.x <0 || me.x > co-1 ||
             me.y <0 || me.y > ro-1 ||
             fi[me.y][me.x] != 1) {
             free(fi); free(hu); free(ba);
             MessageBox(hwndMain, IDMSG_CANNOTOPENINPUTFILE,
                (PSZ)NULL,MB_OK | MB_ERROR, FALSE); return;}
         /*здесь д.б. переприсвоение*/
         MainY += BmpSize*(Row - ro);
         Col = co; Row = ro; QSize = qs; usLevel = le;
         InitNewGame(1); bNew    = ne; //путь (не) проторяем
         iScore = sc; iOScore = os;iBScore = iScore;
         for(i=1;i<Row-1;i++)//пишем поле
            for(j=1;j<Col-1;j++)
               switch(fi[i][j]) {
                  case 1: Field[i][j] = CLR_CHANNEL; break;
                  case 2: Field[i][j] = CLR_NEW    ; break;
                  case 3: Field[i][j] = CLR_BREAK  ; break;
                  default:Field[i][j] = CLR_FIELD  ; break;}
         for(i=0;i<QSize;i++) {
            Balls[i].xLeft   = ba[i].xLeft;
            Balls[i].xRight  = ba[i].xRight;
            Balls[i].yBottom = ba[i].yBottom;
            Balls[i].yTop    = ba[i].yTop;
            Hunters[i].xLeft   = hu[i].xLeft;
            Hunters[i].xRight  = hu[i].xRight;
            Hunters[i].yBottom = hu[i].yBottom;
            Hunters[i].yTop    = hu[i].yTop;}
         Runner.xLeft   = ru.xLeft;
         Runner.xRight  = ru.xRight;
         Runner.yBottom = ru.yBottom;
         Runner.yTop    = ru.yTop;
         Memory.x = me.x; Memory.y = me.y;
         strcpy(szFullPath, fdg.szFullFile);
         free(fi); free(hu); free(ba);
         UpdateTitleText(hwndMainFrame,0);
         WinSetWindowPos(
            hwndMainFrame,//что будем кроить
            HWND_TOP,//наверьхь его
            MainX,MainY,//координаты окна
            BmpSize*Col+2,BmpSize*Row+40+LineHeight,//размеры
            SWP_SIZE | SWP_MOVE );
         WinInvalidateRect(hwndMain,NULL,FALSE);return;}}
   mp2;
}   /* End of FileOpen	 */
/**************************************************************************
 *
 *  Name       : FileSave(mp2)
 *
 *  Description: Processes the File menu's Save item
 *
 *  Concepts:  Берет имя(если его еще нет) и пишет туда как в
 *        ini-файл все конкретные данные об игре
 *
 *  Parameters :  mp2	   = second message parameter
 *************************************************************************/
VOID FileSave(MPARAM mp2)
{  HINI hini;//ini file handle
   char szMsg[100];
   char szName[100];
   int i,j;

   if(szFullPath[0] == '\0') {
      FileSaveAs(mp2); return; }
   /* open the file */
   if((hini = PrfOpenProfile(hab,szFullPath))){
      sprintf(szMsg,"%d",usLevel);
      PrfWriteProfileString(hini,"State","Level",szMsg);
      sprintf(szMsg,"%d",usTime);
      PrfWriteProfileString(hini,"State","Time",szMsg);
      sprintf(szMsg,"%d",bNew);
      PrfWriteProfileString(hini,"State","New",szMsg);
      sprintf(szMsg,"%d",Col);
      PrfWriteProfileString(hini,"Size","Columns",szMsg);
      sprintf(szMsg,"%d",Row);
      PrfWriteProfileString(hini,"Size","Rows",szMsg);
      sprintf(szMsg,"%d",QSize);
      PrfWriteProfileString(hini,"Size","Count of Balls",szMsg);
      sprintf(szMsg,"%d",QSize);
      PrfWriteProfileString(hini,"Size","Count of Hunters",szMsg);
      sprintf(szMsg,"%d",iScore);
      PrfWriteProfileString(hini,"Scores","Score",szMsg);
      sprintf(szMsg,"%d",iOScore);
      PrfWriteProfileString(hini,"Scores","Old Score",szMsg);
      for(i=1;i<Row-1;i++)//пишем поле
         for(j=1;j<Col-1;j++) {
            if(Field[i][j] == CLR_FIELD)
               sprintf(szMsg,"%d",0);
            else if(Field[i][j] == CLR_CHANNEL)
               sprintf(szMsg,"%d",1);
            else if(Field[i][j] == CLR_NEW)
               sprintf(szMsg,"%d",2);
            else if(Field[i][j] == CLR_BREAK)
               sprintf(szMsg,"%d",3);
            sprintf(szName,"%d,%d",i,j);
            PrfWriteProfileString(hini,"Field",szName,szMsg);}
      for(i=0;i<QSize;i++) {//пишем шарики
         sprintf(szName,"xLeft%d",i);
         sprintf(szMsg,"%d",Balls[i].xLeft);
         PrfWriteProfileString(hini,"Balls",szName,szMsg);
         sprintf(szMsg,"%d",Hunters[i].xLeft);
         PrfWriteProfileString(hini,"Hunters",szName,szMsg);
         sprintf(szName,"xRight%d",i);
         sprintf(szMsg,"%d",Balls[i].xRight);
         PrfWriteProfileString(hini,"Balls",szName,szMsg);
         sprintf(szMsg,"%d",Hunters[i].xRight);
         PrfWriteProfileString(hini,"Hunters",szName,szMsg);
         sprintf(szName,"yBottom%d",i);
         sprintf(szMsg,"%d",Balls[i].yBottom);
         PrfWriteProfileString(hini,"Balls",szName,szMsg);
         sprintf(szMsg,"%d",Hunters[i].yBottom);
         PrfWriteProfileString(hini,"Hunters",szName,szMsg);
         sprintf(szName,"yTop%d",i);
         sprintf(szMsg,"%d",Balls[i].yTop);
         PrfWriteProfileString(hini,"Balls",szName,szMsg);
         sprintf(szMsg,"%d",Hunters[i].yTop);
         PrfWriteProfileString(hini,"Hunters",szName,szMsg);}
      sprintf(szMsg,"%d",Runner.xLeft);
      PrfWriteProfileString(hini,"Runner","xLeft",szMsg);
      sprintf(szMsg,"%d",Runner.xRight);
      PrfWriteProfileString(hini,"Runner","xRight",szMsg);
      sprintf(szMsg,"%d",Runner.yBottom);
      PrfWriteProfileString(hini,"Runner","yBottom",szMsg);
      sprintf(szMsg,"%d",Runner.yTop);
      PrfWriteProfileString(hini,"Runner","yTop",szMsg);
      sprintf(szMsg,"%d",Memory.x);
      PrfWriteProfileString(hini,"Memory","x",szMsg);
      sprintf(szMsg,"%d",Memory.y);
      PrfWriteProfileString(hini,"Memory","y",szMsg);
      PrfCloseProfile(hini);
      iBScore = iScore;}
   else MessageBox(hwndMain, IDMSG_CANNOTWRITETOFILE,
          (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
   mp2;
}   /* End of FileSave	 */
/**************************************************************************
 *
 *  Name       : FileSaveAs(mp2)
 *
 *  Description: Processes the File menu's Save as item
 *
 *  Concepts:  Called whenever SAVE AS from the FILE menu is selected
 *
 *	       Routine prompts the user for the name of the file,
 *	       then saves the file.
 *
 *  Parameters :  mp2	   = second message parameter
 *************************************************************************/
VOID FileSaveAs(MPARAM mp2)
{
   /* Get a name for the file */
   if(!GetFileName()) return;
   UpdateTitleText(hwndMainFrame,0);
   FileSave(mp2);
   mp2;
}   /* End of FileSaveAs   */
/**************************************************************************
 *
 *  Name       : GetFileName()
 *
 *  Description: gets the name of the save file
 *
 *  Concepts:	 calls the standard file open dialog to get the
 *		 file name.
 *
 *  API's      : WinLoadString
 *		 WinFileDlg
 *
 *  Return     :  TRUE if successful in getting a file name
 *		  FALSE if not successful in getting a file name
 *************************************************************************/
BOOL GetFileName(VOID)
{  FILEDLG fdg;
   CHAR szTitle[MESSAGELEN], szButton[MESSAGELEN];
   ULONG sT;
   FILE *f,*fopen();//файлы

   while(TRUE) {
      fdg.cbSize = sizeof(FILEDLG);
      if(!WinLoadString(hab, 0, IDS_SAVE, MESSAGELEN, szTitle)) {
          MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
             (PSZ)NULL, MB_OK | MB_ERROR, TRUE); return FALSE; }
      if(!WinLoadString(hab, 0, IDS_SAVE, MESSAGELEN, szButton)) {
          MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
             (PSZ)NULL, MB_OK | MB_ERROR, TRUE); return FALSE; }
      fdg.pszTitle = szTitle;
      fdg.pszOKButton = szButton;

      fdg.ulUser = 0L;
      fdg.fl = FDS_HELPBUTTON | FDS_CENTER | FDS_SAVEAS_DIALOG;
      fdg.pfnDlgProc = (PFNWP)TemplateSaveFilterProc;
      fdg.lReturn = 0L; fdg.lSRC = 0L;
      fdg.hMod = (HMODULE)NULL;
      fdg.usDlgId = FILESAVE;
      fdg.x = 0; fdg.y = 0;
      fdg.pszIType = (PSZ)NULL;
      fdg.papszITypeList = (PAPSZ)NULL;
      fdg.pszIDrive = (PSZ)NULL;
      fdg.papszIDriveList = (PAPSZ)NULL;
      fdg.sEAType = (SHORT)0;
      fdg.papszFQFilename = (PAPSZ)NULL;
      fdg.ulFQFCount = 0L;
      if(szFullPath[0] == '\0'){//загоняем имя по умолчанию
         if(!WinLoadString(hab, (HMODULE)0, IDS_FILEOPENEXT,
               CCHMAXPATH, fdg.szFullFile)){
         MessageBox(hwndMain, IDMSG_CANNOTLOADSTRING,
            (PSZ)NULL, MB_OK | MB_ERROR, TRUE); return FALSE;}}
      else strcpy(fdg.szFullFile, szFullPath);
      /* get the file */
      if(!WinFileDlg(HWND_DESKTOP, hwndMain, &fdg)) return FALSE;
      if(fdg.lReturn != ID_OK) return FALSE;
      //проверяем файл на уже существование
      if((f=fopen(fdg.szFullFile,"r"))!=NULL) {
         fclose(f);
         sT = MessageBox(hwndMain, IDMSG_OVERWRITEFILE,
   		          "Warning!", MB_QUERY | MB_YESNOCANCEL, FALSE);
   	   if(sT == MBID_CANCEL) return FALSE;
   	   if(sT == MBID_YES) break; }
      else break; }   /* while(TRUE) */
   /* copy file name and path returned into buffers */
   strcpy(szFullPath, fdg.szFullFile);
   return TRUE;
}   /* End of GetFileName   */
/**************************************************************************
 *
 *  Name       : UpdateTitleText
 *
 *  Description: Updates the text in the main window's title bar to
 *		 display the app name, followed by the separator,
 *		 followed by the file name.
 *
 *  Concepts :	 Called at init time and when the text file is changed.
 *		 Gets the program name, appends the separator, and
 *		 appends the file name.
 *
 *  API's      : WinLoadString
 *		 WinSetWindowText
 *		 WinWindowFromID
 *
 *  Parameters : hwnd = window handle
 *     bNew = создание новой игры
 *************************************************************************/
VOID UpdateTitleText(HWND hwnd, BOOL bNew)
{  CHAR szBuf[MAXNAMEL+TITLESEPARATORLEN+CCHMAXPATH];
   CHAR szSeparator[TITLESEPARATORLEN+1];
   PSZ pszT;

   WinLoadString(hab, (HMODULE)0, IDS_APPNAME, MAXNAMEL, szBuf);
   WinLoadString(hab, (HMODULE)0, IDS_TITLEBARSEPARATOR,
		 TITLESEPARATORLEN, szSeparator);
   strcat(szBuf, szSeparator);
   if(szFullPath[0] == '\0' || bNew){
      pszT = szUntitled;szFullPath[0] = '\0';}
   else pszT = szFullPath;
   strcat(szBuf, pszT);
   WinSetWindowText(WinWindowFromID(hwnd, FID_TITLEBAR), szBuf);
}   /* End of UpdateTitleText	*/
/**************************************************************************
 *
 *  Name       : TemplateOpenFilterProc(hwnd, msg, mp1, mp2)
 *
 *  Description: Filters the help messages to the open dialog
 *
 *  Concepts :	 If help is requested during the standard OPEN
 *		 dialog, this routine will display an appropriate
 *		 panel.
 *
 *  API's      : WinDefFileDlgProc
 *
 *  Parameters : hwnd = window handle
 *		 message = message i.d.
 *		 mp1	 = first message parameter
 *		 mp2	 = second message parameter
 *
 *  Return     :  the result of the message
 *************************************************************************/
MRESULT EXPENTRY TemplateOpenFilterProc(HWND hwnd, ULONG message,
					MPARAM mp1, MPARAM mp2 )
{
   if(message == WM_HELP) {
      DisplayHelpPanel(HID_FS_OPEN_DLG_HELP_PANEL);
      return (MRESULT)FALSE ; }

   return WinDefFileDlgProc( hwnd, message, mp1, mp2 ) ;
}  /*  End of TemplateOpenFilterProc  */
/**************************************************************************
 *
 *  Name       : TemplateSaveFilterProc(hwnd, msg, mp1, mp2)
 *
 *  Description: Filters the help messages to the save dialog
 *
 *  Concepts :	 If help is requested during the standard SAVEAS
 *		 dialog, this routine will display an appropriate
 *		 panel.
 *
 *  API's      : WinDefFileDlgProc
 *
 *  Parameters : hwnd = window handle
 *		 message = message i.d.
 *		 mp1	 = first message parameter
 *		 mp2	 = second message parameter
 *
 *  Return     :  the result of the message
 *************************************************************************/
MRESULT EXPENTRY TemplateSaveFilterProc(HWND hwnd, ULONG message,
					     MPARAM mp1, MPARAM mp2 )
{
   if(message == WM_HELP) {
      DisplayHelpPanel(HID_FS_SAVE_DLG_HELP_PANEL);
      return (MRESULT)FALSE; }
   return WinDefFileDlgProc( hwnd, message, mp1, mp2 );
}  /*  End of TemplateSaveFilterProc  */
/***************************  End of file.c  ***************************/

