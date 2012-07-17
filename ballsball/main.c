/**************************************************************************
 *  File name  :  main.c
 *
 *  Description:  создание окна, функции окна и обработчик
 *                событий на выбор опции в меню
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


/* Global variables */
HWND hwndMainFrame = NULLHANDLE;    /* handle to the main frame window */
HWND hwndMain;                      /* handle to the main client window */
HWND hwndMenu;                      /* хендл главного меню */
HWND hwndPopupMenu;      /* хендл плавающего меню */
HDC  hdcMain;                       /* handle to the DC of the client */
HAB  hab;                           /* anchor block for the process */
HMQ  hmq;                           /* handle to the process' message queue */
CHAR szAppName[MAXNAMEL];           /* buffer for application name string */
CHAR szUntitled[MESSAGELEN];        /* buffer for "Untitled" string */
BOOL fHelpEnabled;                  /* flag to determine if help is enabled */
BOOL bStart;//можно играть

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
   BOOL bInit;//если инициализация прошла аварийно

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
   /* инициализация настроек и игры */
   bInit = InitPrf();
   InitFont( hdcMain); bStart = 1;
   /* изменение размеров главного окна */
   WinSetWindowPos(
      hwndMainFrame,//что будем кроить
      HWND_TOP,//наверьхь его
      MainX,MainY,//координаты окна
      BmpSize*Col+2,BmpSize*Row+40+LineHeight,//размеры
      SWP_SIZE | SWP_MOVE );
   /* еще одна инициализация настроек и игры */
   InitNewGame(0);//новая игра
   InitHelp();
   if(!bInit)//если инициализация прошла аварийно
      MessageBox(hwndMain, IDMSG_CANNOTLOADSETTINGS,
         "Warning", MB_OK | MB_ERROR, TRUE);
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

   case WM_ACTIVATE://обращаем или обращали внимание на другие окна
         bGame = 0;//останавливаем игру
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);
      break;

   case WM_BUTTON1DOWN://мышка
      {//координаты мышки относительно координат бегунка
      long  lx,ly;
      //во-первых,делаем окно активным
      if(WinQueryActiveWindow(HWND_DESKTOP)!=hwndMainFrame) {
        WinSetActiveWindow(HWND_DESKTOP,hwndMainFrame);
        break;}
      //во-вторых,узнаем координаты беглеца
      lx = SHORT1FROMMP(mp1)-Runner.xLeft*BmpSize-BmpSize/2-1;
      ly = SHORT2FROMMP(mp1)-Runner.yBottom*BmpSize-BmpSize/2+2;
      //в-третьих,заставляем его слушаться мыши
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

   case WM_BUTTON2DOWN://плавающее меню
      //во-первых,делаем окно активным
      if(WinQueryActiveWindow(HWND_DESKTOP)!=hwndMainFrame) {
        WinSetActiveWindow(HWND_DESKTOP,hwndMainFrame);
        break;}
      //во-вторых,рисуем плавающее меню
      MenuRedraw(bSound-7);//ставим звук
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

   case WM_CHAR://нажатие клавиши
       if(!(SHORT1FROMMP(mp1) & KC_KEYUP) &&
          !(SHORT1FROMMP(mp1) & KC_PREVDOWN))
          MainChar(hwnd,mp1,mp2);break;

   case WM_INITMENU:
       InitMenu(mp1, mp2);break;

   case HM_QUERY_KEYS_HELP:
       return (MRESULT)PANEL_HELPKEYS;/* return id of key help panel */break;

   case WM_DESTROY:
      if(bGame){//если идет игра - останавливаем
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
 *      szTitle  = заголовок
 *                fsStyle  = style flags for the message box
 *                fBeep   = should an alarm be sounded?
 *
 *  Return     :  return value from WinMessageBox
 *************************************************************************/
ULONG MessageBox(HWND hwndOwner, ULONG idMsg, PSZ szTitle, ULONG fsStyle, BOOL fBeep)
{  CHAR szText[MESSAGELEN];

   if (!WinLoadMessage(hab, (HMODULE)NULL, idMsg,
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
      if(bGame){//если идет игра
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
               if(bGame){//если шла игра,запускаем обратно
                  WinStartTimer(hab,hwnd,IDT_MOVE,100);
                  WinStartTimer(hab,hwnd,IDT_GAME,1000);}break;
            default:break;}}
      else{usLevel = 0; InitNewGame(0);iBScore = 0;
           UpdateTitleText(hwndMainFrame,1);
           WinInvalidateRect(hwnd,NULL,FALSE);} break;

   case IDM_FILEOPEN:
      if(bGame){//если идет игра
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
               if(bGame){//если шла игра,запускаем обратно
                  WinStartTimer(hab,hwnd,IDT_MOVE,100);
                  WinStartTimer(hab,hwnd,IDT_GAME,1000);}break;
            default:break;}}
      else FileOpen(mp2); break;

   case IDM_FILESAVE:
      if(bGame){//если идет игра
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      FileSave(mp2);
      if(bGame){//если идет игра
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_FILESAVEAS:
      if(bGame){//если идет игра
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      FileSaveAs(mp2);
      if(bGame){//если идет игра
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_HIGHSCORES:
      if(bGame){//если идет игра
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      HScoresPrf(0);
      if(bGame){//если идет игра
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

   case IDM_FILEEXIT:
         if(bGame){//если идет игра
            WinStopTimer(hab,hwnd,IDT_MOVE);//останавливаем
            WinStopTimer(hab,hwnd,IDT_GAME);}
         if(bStart && iScore != iBScore){
            usReturn = MessageBox(hwnd, IDMSG_SAVE," ",
                         MB_YESNOCANCEL | MB_INFORMATION, 0);
            switch(usReturn) {
               case MBID_YES: FileSave(mp2);
               case MBID_NO:
                  WinPostMsg(hwnd,WM_CLOSE,MPVOID,MPVOID);break;
               case MBID_CANCEL:
                  if(bGame){//если шла игра,запускаем обратно
                     WinStartTimer(hab,hwnd,IDT_MOVE,100);
                     WinStartTimer(hab,hwnd,IDT_GAME,1000);}break;
               default:break;}}
         else WinPostMsg(hwnd,WM_CLOSE,MPVOID,MPVOID);break;

   case IDM_DIRECTION_START:
         if(bStart) {
            if(bGame){//если идет игра
               bGame = 0;//останавливаем
               WinStopTimer(hab,hwnd,IDT_MOVE);
               WinStopTimer(hab,hwnd,IDT_GAME);}
            else{//если игра остановлена
               bGame = 1;//играем дальше
               WinStartTimer(hab,hwnd,IDT_MOVE,100);
               WinStartTimer(hab,hwnd,IDT_GAME,1000);}}break;

   case IDM_SOUND_ON:
      bSound = 1;/*звук включен*/break;

   case IDM_SOUND_OFF:
      bSound = 0;/*звук выключен*/break;

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
      //сохранение наигранного перед переходом на следующий уровень
      if(bGame){//если идет игра
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      if(bStart && iScore != iBScore){
         usReturn = MessageBox(hwnd, IDMSG_SAVE," ",
                       MB_YESNOCANCEL | MB_INFORMATION, 0);
         if(usReturn == MBID_YES) FileSave(mp2); else
         if(usReturn == MBID_CANCEL) {
            if(bGame){//если шла игра,запускаем обратно
                  WinStartTimer(hab,hwnd,IDT_MOVE,100);
                  WinStartTimer(hab,hwnd,IDT_GAME,1000);}
            break;}}
      //переход на следующий уровень
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
      if(bGame){//если идет игра
         WinStopTimer(hab,hwnd,IDT_MOVE);
         WinStopTimer(hab,hwnd,IDT_GAME);}
      bChange = 0;//изменений еще нет
      /* функция диалога */
      WinDlgBox( HWND_DESKTOP,  /*где рисуем*/
         hwnd,            /*владелец*/
         SettingsDlgProc, /*диалоговая процедура*/
         (HMODULE)0,         /*указатель модуля*/
         DLG_SETTINGS,    /*указатель диалога в .rc*/
         NULL);              /*на нет и суда нет*/
      /* функция диалога */
      if(bGame){//если идет игра
            WinStartTimer(hab,hwnd,IDT_MOVE,100);
            WinStartTimer(hab,hwnd,IDT_GAME,1000);} break;

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
	        DLG_ABOUTTHISPROGRAM, (PVOID)NULL);
      break;

   default: break;
   }
}   /* End of MainCommand  */
/**************************************************************************
 *  Name       : MainChar(HWND hwnd, MPARAM mp1, MPARAM mp2)
 *
 *  Description: вызывается при нажатии клавиши.
 *
 *  Concepts:    обработчик события WM_CHAR .
 *
 *  API's      : [none]
 *
 *  Parameters : hmnd = хендл окна
 *               usVK = виртуальный код клавиши
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

      case VK_ESC://выход
         mp1 = MPFROMSHORT(IDM_FILEEXIT);
         WinPostMsg(hwnd, WM_COMMAND, mp1,mp2);break;

      case 0://не спи - замерзнешь
         if(bGame){//если идет игра
           Runner.xRight =  0;
           Runner.yTop   =  0;}break;

      case VK_RIGHT://идет направо - песнь заводит
         if(bGame){//если идет игра
            Runner.xRight =  1;
            Runner.yTop   =  0;}break;

      case VK_LEFT: //налево - сказку говорит
         if(bGame){//если идет игра
            Runner.xRight = -1;
            Runner.yTop   =  0;}break;

      case VK_DOWN: //там чудеса, там леший бродит
         if(bGame){//если идет игра
            Runner.xRight =  0;
            Runner.yTop   = -1;}break;

      case VK_UP:   //русалка на ветвях сидит
         if(bGame){//если идет игра
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
 *  Description: вызывается при получении сообщения от таймеров.
 *
 *  Concepts:    обработчик события WM_TIMER .
 *
 *  API's      : [none]
 *
 *  Parameters : hmnd = хендл окна
 *     ulTIMER = идентификатор таймера
 *************************************************************************/
VOID MainTimer(HWND hwnd, ULONG ulTIMER)
{  HPS hps;
   int i;

   hps = WinGetPS(hwnd);
   switch(ulTIMER) { BOOL bMoveRunner;
      case IDT_MOVE ://пришло время двигаться
         if(Field[Runner.yBottom][Runner.xLeft] == CLR_FIELD){
            Field[Runner.yBottom][Runner.xLeft] = CLR_NEW;
            bNew = 1;}
         if(Runner.xRight || Runner.yTop){//двигаем беглеца
            Quatro(&hps,Runner.yBottom,Runner.xLeft);
            MoveRunner();
            bMoveRunner = 1;}
         for(i=0;i<QSize;i++) {//стираем старые кружки
            if(Balls[i].yTop){//если имеет смысл двигать
               Quatro(&hps,Balls[i].yBottom,Balls[i].xLeft);
               if(MoveBall(i))CTPOKA(&hps,0);//двигаем
               Kpyr(&hps, Balls[i].yBottom,
                          Balls[i].xLeft, CLR_BALLS);}
            Quatro(&hps,Hunters[i].yBottom,Hunters[i].xLeft);
            MoveHunter(i);//двигаем
            Kpyr(&hps, Hunters[i].yBottom,//рисуем новые кружки
                       Hunters[i].xLeft, CLR_HUNTERS);}
         if(bMoveRunner)//рисуемем беглеца
            Kpyr(&hps, Runner.yBottom,Runner.xLeft, CLR_RUNNER);
         /* проверка на бряк */
         for(i=0;i<QSize;i++) {
            if (Field[Balls[i].yBottom][Balls[i].xLeft] == CLR_NEW ||
               (Balls[i].xLeft   == Runner.xLeft &&
                Balls[i].yBottom == Runner.yBottom)) {
               Replace(CLR_NEW,CLR_BREAK,&hps);bNew = 0;
               if(bSound) DosBeep(100,500);
               else DosSleep(500);
               Replace(CLR_BREAK,CLR_FIELD,&hps);
               Quatro(&hps,Runner.yBottom,Runner.xLeft);
               Runner.xLeft   = Memory.x;//старые знакомые
               Runner.yBottom = Memory.y;bNew = 0;/*путь не проторяем*/
               Runner.xRight = 0;Runner.yTop   = 0;//стоим
               Kpyr(&hps, Balls[i].yBottom,Balls[i].xLeft, CLR_BALLS);
               Kpyr(&hps, Runner.yBottom,Runner.xLeft, CLR_RUNNER);
               iScore -= 50;CTPOKA(&hps,0);/*официант! счет*/}
            if (Hunters[i].xLeft   == Runner.xLeft &&
                Hunters[i].yBottom == Runner.yBottom) {
               if(bSound) DosBeep(100,500);
               else DosSleep(500);
               Quatro(&hps,Hunters[i].yBottom,Hunters[i].xLeft);
               MoveHunter(i);//двигаем
               Kpyr(&hps, Hunters[i].yBottom,//рисуем новые кружки
                          Hunters[i].xLeft, CLR_HUNTERS);
               Kpyr(&hps, Runner.yBottom,//рисуем новый кружок
                          Runner.xLeft, CLR_RUNNER);
               iScore -= 50;CTPOKA(&hps,0);/*официант! счет*/}}
         /* конец проверки на бряк */
         if(Field[Runner.yBottom][Runner.xLeft] == CLR_CHANNEL){
            if(bNew){
               int j;long lMax;

               WinStopTimer(hab,hwnd,IDT_MOVE);
               WinStopTimer(hab,hwnd,IDT_GAME);
               if(bHalt){//останавливаемся
                  Runner.xRight = 0;Runner.yTop   = 0;}
               /*захват территорий*/
               lMax = 100;//д.б.>15 (цвета CLR_* от -5 до 15)
               for(i=1;i<Col-1;i++)
                  for(j=1;j<Row-1;j++){
                     if (Field[j][i] == CLR_FIELD)//поле-нужна проверка
                        if (Field[j-1][i] < 100 &&//снизу-чужие
                            Field[j][i-1] < 100){//и сзади-чужие
                           Field[j][i] = ++lMax;}//нумеруем
                        else if (Field[j-1][i] < 100)//снизу-чужие
                           Field[j][i] = Field[j][i-1];//берем сзади
                        else if (Field[j][i-1] < 100)//сзади-чужие
                           Field[j][i] = Field[j-1][i];//берем снизу
                        else {//все свободно
                           Field[j][i] = Field[j-1][i];//берем снизу
                           if (Field[j-1][i] != Field[j][i-1])//если зад!=низ
                              Replace(Field[j][i-1],Field[j-1][i],NULL);}/*of else*/}//of if
               //смотрим занятые резервации
               for(i=0;i<QSize;i++) if(Field[Balls[i].yBottom][Balls[i].xLeft] > 100)
                  Replace(Field[Balls[i].yBottom][Balls[i].xLeft],CLR_FIELD,NULL);
               //метим все остальное как новое
               for(i=1;i<Col-1;i++)
                  for(j=1;j<Row-1;j++)
                     if(Field[j][i] > 100) Field[j][i] = CLR_NEW;
               /*конец захвата территорий*/
               Replace(CLR_NEW, CLR_CHANNEL, &hps );//меняем шило на мыло
               CTPOKA(&hps,0);//официант! счет
               if(bSound) {//медь звучащая
                  DosBeep(500,50);
                  DosBeep(1000,50);
                  DosBeep(2000,50);}
               WinStartTimer(hab,hwnd,IDT_MOVE,100);
               WinStartTimer(hab,hwnd,IDT_GAME,1000);}//if(bNew)
            Memory.x = Runner.xLeft;//старые знакомые
            Memory.y = Runner.yBottom;
            bNew = 0;/*путь не проторяем*/}break;

      case IDT_GAME ://а время идет
         usTime -= 1;
         if(iScore - iOScore > ((Row-2)*(Col-2)*4)/5 ||//вы выиграли
           (iScore - iOScore > ((Row-2)*(Col-2)*2)/3 &&
            usTime == 0 )) {
            if(bGame){//если идет игра
               WinStopTimer(hab,hwnd,IDT_MOVE);
               WinStopTimer(hab,hwnd,IDT_GAME);}
            if (usLevel < MAXLEVEL) {//переход на следующий уровень
               MessageBox(hwnd, IDMSG_OK," ",
                  MB_OK | MB_INFORMATION, 0);//типа ok
               iOScore = iScore;//запоминаем прошлые очки
               usLevel++;
               InitNewGame(1);
               WinInvalidateRect(hwnd,NULL,FALSE);}
            else {//дошли до предела
               MessageBox(hwnd, IDMSG_CONGRATULATIONS,
                  " ", MB_OK | MB_INFORMATION, 0);//поздравления
               if(iScore > iHScore) HScoresPrf(2);//занесение в HighScores
               bStart = 0; bGame = 0;}}
         else if(iScore - iOScore < ((Row-2)*(Col-2)*2)/3 &&
                 usTime == 0 ) {//проиграл
                  bStart = 0;
                  if(bGame){//если идет игра
                     bGame =0;//останавливаем
                     WinStopTimer(hab,hwnd,IDT_MOVE);
                     WinStopTimer(hab,hwnd,IDT_GAME);}
                  if(iScore > iHScore) HScoresPrf(1);//занесение в HighScores
                  else MessageBox(hwnd, IDMSG_SORRY," ",
                                    MB_OK | MB_INFORMATION, 0);}//проиграл
         else CTPOKA(&hps,2);break;

   default:break;}/*of switch*/
   WinReleasePS(hps);
}   /* End of MainCommand  */
/***************************  End of main.c  ****************************/

