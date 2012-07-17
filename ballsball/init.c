/**************************************************************************
 *  File name  :  init.c
 *
 *  Description:  This module contains the code for application
 *		  initialization, as well as the code for exit list
 *		  processing
 *
 *		  This source file contains the following functions:
 *
 *		  Init()
 *		  InitMainWindow(hwnd, mp1, mp2)
 *		  ExitProc(usTermCode)
 *      InitQueue(BOOL bQueue,int iNum)
 *      InitNewGame(BOOL bOld)
 *      InitPrf()
 *      InitQueue(BOOL bQueue,int iNum)
 *      NotUnique(int iNum, PPOINTL ppQueue)
 *      ClosePrf()
 *      HScoresPrf(bChange)
 *      VOID InitLevel(usl)
 *      BOOL InitFont()
 *
 *  Concepts   :  initialization
 *
 *  API's      :  DosExitList
 *		  DosExit
 *		  WinLoadString
 *		  WinRegisterClass
 *		  WinIsWindow
 *		  WinDestroyWindow
 *		  WinDestroyMsgQueue
 *		  WinTerminate
 *
 *  Required
 *    Files    :  OS2.H, STRING.H, STDIO.H, STDLIB.H, MAIN.H,
 *      XTRN.H, GAME.H, DLG.H
 *************************************************************************/

/* Include files, macros, defined constants, and externs */

#define	 INCL_WIN
#define	 INCL_WINWINDOWMGR
#define	 INCL_WINSHELLDATA
#define	 INCL_DOSPROCESS
#define   INCL_GPILCIDS

#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "dlg.h"
#include "game.h"
#include "xtrn.h"

/* Global variables */
long *(*Field);  //все поле
long CLR_FIELD;  //полюшко-поле
long CLR_CHANNEL; //коридор
long CLR_NEW;    //кандидат на коридор
long CLR_BREAK;  //убили кандидата
long CLR_RUNNER; //бегунок
long CLR_HUNTERS;//охотники
long CLR_BALLS;  //мячики
long CLR_STRING; //фон для букв
long CLR_CHAR;   //цвет букв
BOOL bNew; //проторяем путь
BOOL bGame;//идет игра
BOOL bStyle;//2d или 3d
BOOL bSound;//звук
BOOL bHalt;//остановка после прибавки
USHORT usLevel;//уровень
int iScore;//очки
int iOScore;//очки с прошлой игры
int iHScore;//минимум в десятке
int iBScore;//очки с начала игры
USHORT usTime;//время от начала игры

RECTL Runner;//играющий
POINTL Memory;//последняя позиция в коридоре
//очереди
RECTL *Hunters;//охотники(в коридорах)
RECTL *Balls;//мячи(в поле)
//размеры
int QSize;//размер очередей
int BmpSize;//размер картинки
int Col;//количество столбцев
int Row;//количество строк
int LineHeight;//размер текстовой строки
//координаты окна
long MainX;
long MainY;

/* Entry point declarations */

/**************************************************************************
 *  Name       : Init()
 *
 *  Description:  Performs initialization functions required
 *		  before the main window can be created.
 *
 *  Concepts:	  Called once before the main window is created.
 *
 *		  - Installs the routine ExitProc into the
 *		    DosExitList chain
 *		  - registers all window classes
 *		  - performs any command line processing
 *
 *  API's      :  DosExitList
 *		  DosExit
 *		  WinLoadString
 *		  WinRegisterClass
 *
 *  Parameters :  [none]
 *
 *  Return     :  TRUE = initialization is successful
 *		  FALSE = initialization failed
 *
 *************************************************************************/
BOOL Init(VOID)
{

   if(DosExitList(EXLST_ADD, (PFNEXITLIST)ExitProc)) {
      MessageBox(HWND_DESKTOP, IDMSG_CANNOTLOADEXITLIST,
		    (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
      DosExit(EXIT_PROCESS, RETURN_ERROR); }
   /* load application name from resource file */
   if(0 == WinLoadString(hab, (HMODULE)0, IDS_APPNAME, MAXNAMEL, szAppName))
      return FALSE;
   /* load "untitled" string */
   if(!WinLoadString(hab, (HMODULE)0, IDS_UNTITLED, MESSAGELEN, szUntitled))
       return FALSE;
   /* register the main client window class */
   if(!WinRegisterClass(hab,
		       (PSZ)szAppName,
		       (PFNWP)MainWndProc,
		       CS_SAVEBITS,
		       0L))
       return FALSE;

   return TRUE;
}  /* End of Init   */
/**************************************************************************
 *  Name       : ExitProc(usTermCode)
 *
 *  Description: Cleans up certain resources when the application
 *		 terminates.
 *
 *  Concepts:	 Routine is called by DosExitList when the
 *		 application exits.
 *
 *		 Global resources, such as the main window and
 *		 message queue, are destroyed and any system
 *		 resources used are freed.
 *
 *  API's      : WinIsWindow
 *		 WinDestroyWindow
 *		 WinDestroyMsgQueue
 *		 WinTerminate
 *		 DosExitList
 *
 *  Parameters :  usTermCode = termination code number
 *
 *  Return    :	  Returns EXLST_EXIT to the DosExitList handler
 *
 *************************************************************************/
VOID ExitProc()
{  /* destroy the main window if it exists */
   if(WinIsWindow(hab, hwndMainFrame))
      WinDestroyWindow(hwndMainFrame);
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   DosExitList(EXLST_EXIT, (PFNEXITLIST)NULL);	  /* termination complete */
   //забираем память у очередей
   free(Field);
   free(Hunters);
   free(Balls);
}   /* End of ExitProc	  */
/**************************************************************************
 *  Name       : InitPrf();
 *
 *  Description: инициализирует настройки игры
 *
 *  Concepts:	 пока волевым усилием присваивает цвета и
 *		 прочие настройки.В будущем будет черпать их из ini-файла.
 *     Вот, уже черпает.
 *************************************************************************/
BOOL InitPrf()
{  HINI hini;//ini file handle
   SWP swpDESKTOP;//получалка координат и размеров DESKTOPa

   WinQueryWindowPos(HWND_DESKTOP,&swpDESKTOP);
   bGame   = 0;//игра не началась
   bNew    = 0; //путь не проторяем
   usLevel = 0;//нулевой уровень
   iScore  = 0;//очки
   usTime  = 180;//игра не началась
   if((hini = PrfOpenProfile(hab,"bb.ini"))){
      BmpSize = PrfQueryProfileInt(hini,"Bitmaps","Size",10);
      Col     = PrfQueryProfileInt(hini,"Bitmaps","Columns",60);
      Row     = PrfQueryProfileInt(hini,"Bitmaps","Rows",40);
      MainX = PrfQueryProfileInt(hini,"Place","MainX",100);
      MainY = PrfQueryProfileInt(hini,"Place","MainY",100);
      MainY = MIN(swpDESKTOP.cy-(BmpSize*Row+40+20),MainY);
      CLR_FIELD   = PrfQueryProfileInt(hini,"Colors","Color of free field",CLR_PALEGRAY);//полюшко-поле
      CLR_CHANNEL = PrfQueryProfileInt(hini,"Colors","Color of channels",CLR_BLUE);//коридор
      CLR_NEW     = PrfQueryProfileInt(hini,"Colors","Color of new channels",CLR_GREEN);//кандидат на коридор
      CLR_BREAK   = PrfQueryProfileInt(hini,"Colors","Color of break channels",CLR_RED);//убили кандидата
      CLR_RUNNER  = PrfQueryProfileInt(hini,"Colors","Color of runner",CLR_DARKCYAN);//бегунок
      CLR_HUNTERS = PrfQueryProfileInt(hini,"Colors","Color of hunters",CLR_RED);//охотники
      CLR_BALLS   = PrfQueryProfileInt(hini,"Colors","Color of balls",CLR_BLUE);//мячики
      CLR_STRING  = PrfQueryProfileInt(hini,"Colors","Color of background",CLR_DARKBLUE);//фон для букв
      CLR_CHAR    = PrfQueryProfileInt(hini,"Colors","Color of chars",CLR_WHITE);//цвет букв
      bStyle = PrfQueryProfileInt(hini,"Settings","Style(2D/3D)",1);//3d
      bSound = PrfQueryProfileInt(hini,"Settings","Sound",1);//звук включен
      bHalt  = PrfQueryProfileInt(hini,"Settings","Halt",1);//останавливаться
      iHScore = PrfQueryProfileInt(hini,"High Scores","10",0);/*минимум в десятке*/
      PrfCloseProfile(hini);
      if( CLR_FIELD   != CLR_CHANNEL && CLR_FIELD   != CLR_NEW   &&
          CLR_FIELD   != CLR_BREAK   && CLR_CHANNEL != CLR_NEW   &&
          CLR_CHANNEL != CLR_BREAK   && CLR_NEW     != CLR_BREAK &&
         (CLR_FIELD == CLR_PALEGRAY || CLR_FIELD == CLR_BLUE ||
          CLR_FIELD == CLR_GREEN    || CLR_FIELD == CLR_CYAN ||
          CLR_FIELD == CLR_PINK     || CLR_FIELD == CLR_RED  ||
          CLR_FIELD == CLR_YELLOW ) &&
         (CLR_CHANNEL == CLR_PALEGRAY || CLR_CHANNEL == CLR_BLUE ||
          CLR_CHANNEL == CLR_GREEN    || CLR_CHANNEL == CLR_CYAN ||
          CLR_CHANNEL == CLR_PINK     || CLR_CHANNEL == CLR_RED  ||
          CLR_CHANNEL == CLR_YELLOW ) &&
         (CLR_NEW == CLR_PALEGRAY || CLR_NEW == CLR_BLUE ||
          CLR_NEW == CLR_GREEN    || CLR_NEW == CLR_CYAN ||
          CLR_NEW == CLR_PINK     || CLR_NEW == CLR_RED  ||
          CLR_NEW == CLR_YELLOW ) &&
         (CLR_BREAK == CLR_PALEGRAY || CLR_BREAK == CLR_BLUE ||
          CLR_BREAK == CLR_GREEN    || CLR_BREAK == CLR_CYAN ||
          CLR_BREAK == CLR_PINK     || CLR_BREAK == CLR_RED  ||
          CLR_BREAK == CLR_YELLOW ) &&
         (CLR_RUNNER == CLR_DARKGRAY  || CLR_RUNNER == CLR_BLUE     ||
          CLR_RUNNER == CLR_DARKGREEN || CLR_RUNNER == CLR_DARKCYAN ||
          CLR_RUNNER == CLR_DARKPINK  || CLR_RUNNER == CLR_RED      ||
          CLR_RUNNER == CLR_BROWN ) &&
         (CLR_HUNTERS == CLR_DARKGRAY  || CLR_HUNTERS == CLR_BLUE     ||
          CLR_HUNTERS == CLR_DARKGREEN || CLR_HUNTERS == CLR_DARKCYAN ||
          CLR_HUNTERS == CLR_DARKPINK  || CLR_HUNTERS == CLR_RED      ||
          CLR_HUNTERS == CLR_BROWN ) &&
         (CLR_BALLS == CLR_DARKGRAY  || CLR_BALLS == CLR_BLUE     ||
          CLR_BALLS == CLR_DARKGREEN || CLR_BALLS == CLR_DARKCYAN ||
          CLR_BALLS == CLR_DARKPINK  || CLR_BALLS == CLR_RED      ||
          CLR_BALLS == CLR_BROWN ) &&
         (CLR_STRING == CLR_DARKGRAY  || CLR_STRING == CLR_DARKBLUE ||
          CLR_STRING == CLR_DARKGREEN || CLR_STRING == CLR_DARKCYAN ||
          CLR_STRING == CLR_DARKPINK  || CLR_STRING == CLR_DARKRED  ||
          CLR_STRING == CLR_BROWN ) &&
         (CLR_CHAR == CLR_PALEGRAY || CLR_CHAR == CLR_BLUE ||
          CLR_CHAR == CLR_GREEN    || CLR_CHAR == CLR_CYAN ||
          CLR_CHAR == CLR_PINK     || CLR_CHAR == CLR_RED  ||
          CLR_CHAR == CLR_YELLOW   || CLR_CHAR == CLR_WHITE ) &&
          Col < 101 && Col > 49 && Row < 61 && Row > 29 &&
          BmpSize > 5 && BmpSize < 13) return 1; }
   BmpSize = 8;
   Col = 80; Row = 50;
   MainX = 100; MainY = 100;
   MainY = MIN(swpDESKTOP.cy-(BmpSize*Row+40+20),MainY);
   CLR_FIELD   = CLR_PALEGRAY;  //полюшко-поле
   CLR_CHANNEL  = CLR_BLUE;    //коридор
   CLR_NEW     = CLR_GREEN;   //кандидат на коридор
   CLR_BREAK   = CLR_RED;     //убили кандидата
   CLR_RUNNER  = CLR_DARKCYAN;//бегунок
   CLR_HUNTERS = CLR_RED;    //охотники
   CLR_BALLS   = CLR_BLUE;     //мячики
   CLR_STRING  = CLR_DARKBLUE; //фон для букв
   CLR_CHAR    = CLR_WHITE;   //цвет букв
   bStyle  = 1;//3d
   bSound  = 1;//звук включен
   bHalt   = 1;//останавливаться
   iHScore = 0;/*минимум в десятке*/ return 0;
   }   /* End of InitPrf	  */
/**************************************************************************
 *  Name       : InitNewGame()
 *
 *  Description: Инициализирует(очищает) поле для новой игры и
 *		 выстраивает очереди шариков.
 *
 *
 *  Parameters : bOld = это совершенно новая игра или просто
 *     переход на другой уровень
 *************************************************************************/
VOID InitNewGame(BOOL bOld)
{  int i,j;
   float fRandom;

   LevelBeginptl.x = Col*BmpSize;//начало не известно
   bGame = 0;//останавливаем
   bStart = 1;//можно играть
   usTime  = 180;//игра не началась
   if(bOld) iScore += usLevel*10;//очки
   else     iScore = 0;
   iOScore = iScore;
   bNew    = 0; //путь не проторяем
   //заполняем игровое поле
   free(Field);
   Field = malloc(Row*sizeof(*Field));
   for(i=0;i<Row;i++) Field[i] = malloc(Col*sizeof(CLR_FIELD));
   //поля
   for(i=1;i<Row-1;i++)
      for(j=1;j<Col-1;j++)Field[i][j] = CLR_FIELD;
   //вертикальные линии
   for(i=0;i<Row;i++)Field[i][0]     = CLR_CHANNEL;
   for(i=0;i<Row;i++)Field[i][Col-1] = CLR_CHANNEL;
   //горизонтальные линии
   for(j=0;j<Col;j++)Field[0][j]     = CLR_CHANNEL;
   for(j=0;j<Col;j++)Field[Row-1][j] = CLR_CHANNEL;
   //беглец
   Runner.xLeft   = Col/2;
   Runner.yBottom = Row-1;
   Runner.xRight  = 0;
   Runner.yTop    = 0;
   //его место в коридоре
   Memory.x = Col/2;
   Memory.y = Row-1;
   //размер очередей
   QSize = 4+usLevel;
   //очереди
   free(Hunters);//забираем память
   free(Balls);//забираем память
   Hunters=malloc(sizeof(Runner)*QSize);//выделение памяти
   Balls=malloc(sizeof(Runner)*QSize);//выделение памяти
   for(i=0;i<QSize;i++) {
      do {//розыгрыш координат для охотников
         fRandom=rand()*(Col+2*Row-3)/RAND_MAX;
         j = fRandom;j=j/2*2;
         if(j<Row-2) {//первый столбец
            Hunters[i].xLeft   = 0;//координаты
            Hunters[i].yBottom = j+1;
            Hunters[i].xRight  = 0;//направление движения
            if(i == i/2*2) Hunters[i].yTop = -1; //против чс
            else           Hunters[i].yTop =  1;}//по чс
         else if(j<Col+Row-2) {//первая строка
            Hunters[i].xLeft   = j-Row+3;//координаты
            Hunters[i].yBottom = 0;
            Hunters[i].yTop    = 0;//направление движения
            if(i == i/2*2) Hunters[i].xRight =  1; //против чс
            else           Hunters[i].xRight = -1;}//по чс
         else {//последний столбец
            Hunters[i].xLeft   = Col-1;//координаты
            Hunters[i].yBottom = Col+2*Row-4-j;
            Hunters[i].xRight  = 0;//направление движения
            if(i == i/2*2) Hunters[i].yTop =  1; //против чс
            else           Hunters[i].yTop = -1;}//по чс
      } while( NotUnique(i, Hunters) );
      do {//розыгрыш координат для шариков
         fRandom=rand()*((Col-2)*(Row-2)-1)/RAND_MAX;
         Balls[i].yBottom = fRandom/(Col-2)+1;
         Balls[i].xLeft   = fRandom-(Balls[i].yBottom-1)*(Col-2)+1;
         } while( NotUnique(i, Balls) );
      switch(i-i/4*4) {//задаем направления
         case 0:
            Balls[i].xRight = 1;
            Balls[i].yTop   = 1;
            break;
         case 1:
            Balls[i].xRight = -1;
            Balls[i].yTop   = 1;
            break;
         case 2:
            Balls[i].xRight = 1;
            Balls[i].yTop   = -1;
            break;
         case 3:
            Balls[i].xRight = -1;
            Balls[i].yTop   = -1;
            break;}/*of switch*/}//of for
}   /* End of InitNewGame	  */
/**************************************************************************
 *  Name       : BOOL NotUnique(int iNum, PPOINTL ppQueue)
 *
 *  Description: Проверяет элемент очереди охотников
 *		  или шариков на предмет совпадения координат.
 *
 *  Parameters : ppQueue = инициализируемая очередь
 *      iNum = инициализируемый элемент
 *
 *  Return    :	  Возвращает ЛОЖЬ если элемент уникальный
 *      и ИСТИНА,если элемент с такими координатами уже есть
 *************************************************************************/
BOOL NotUnique(int iNum, PRECTL ppQueue)
{  int i;

   for(i=0;i<iNum;i++)//не совпадает с предыдущими
      if(ppQueue[iNum].xLeft   == ppQueue[i].xLeft   &&
         ppQueue[iNum].yBottom == ppQueue[i].yBottom)return 1;
   if(ppQueue == Balls)/*шарики не мешают друг другу*/{
      int j,k;
      for(i=0;i<iNum;i++){
         j = ppQueue[i].xLeft   - ppQueue[iNum].xLeft;
         k = ppQueue[i].yBottom - ppQueue[iNum].yBottom;
         if(k+j == (k+j)/2*2 &&
           j != j/2*2) return 1;}}
   return 0;
}   /* End of NotUnique */
/**************************************************************************
 *  Name       : ClosePrf();
 *
 *  Description: пишет настройки игры в ini-файл.
 *
 *  Concepts:	  берет и пишет, без всяких тут концепций.
 *************************************************************************/
VOID ClosePrf()
{  HINI hini;//ini file handle
   char szMsg[100];
   SWP swpMain;//получалка координат и размеров окна

   if((hini = PrfOpenProfile(hab,"bb.ini"))){
      WinQueryWindowPos(hwndMainFrame,&swpMain);
      sprintf(szMsg,"%d",swpMain.x);
      PrfWriteProfileString(hini,"Place","MainX",szMsg);
      sprintf(szMsg,"%d",swpMain.y);
      PrfWriteProfileString(hini,"Place","MainY",szMsg);
      sprintf(szMsg,"%d",BmpSize);
      PrfWriteProfileString(hini,"Bitmaps","Size",szMsg);
      sprintf(szMsg,"%d",Col);
      PrfWriteProfileString(hini,"Bitmaps","Columns",szMsg);
      sprintf(szMsg,"%d",Row);
      PrfWriteProfileString(hini,"Bitmaps","Rows",szMsg);
      sprintf(szMsg,"%d",CLR_FIELD);
      PrfWriteProfileString(hini,"Colors","Color of free field",szMsg);
      sprintf(szMsg,"%d",CLR_CHANNEL);
      PrfWriteProfileString(hini,"Colors","Color of channels",szMsg);
      sprintf(szMsg,"%d",CLR_NEW);
      PrfWriteProfileString(hini,"Colors","Color of new channels",szMsg);
      sprintf(szMsg,"%d",CLR_BREAK);
      PrfWriteProfileString(hini,"Colors","Color of break channels",szMsg);
      sprintf(szMsg,"%d",CLR_RUNNER);
      PrfWriteProfileString(hini,"Colors","Color of runner",szMsg);
      sprintf(szMsg,"%d",CLR_HUNTERS);
      PrfWriteProfileString(hini,"Colors","Color of hunters",szMsg);
      sprintf(szMsg,"%d",CLR_BALLS);
      PrfWriteProfileString(hini,"Colors","Color of balls",szMsg);
      sprintf(szMsg,"%d",CLR_STRING);
      PrfWriteProfileString(hini,"Colors","Color of background",szMsg);
      sprintf(szMsg,"%d",CLR_CHAR);
      PrfWriteProfileString(hini,"Colors","Color of chars",szMsg);
      sprintf(szMsg,"%d",bStyle);
      PrfWriteProfileString(hini,"Settings","Style(2D/3D)",szMsg);
      sprintf(szMsg,"%d",bSound);
      PrfWriteProfileString(hini,"Settings","Sound",szMsg);
      sprintf(szMsg,"%d",bHalt);
      PrfWriteProfileString(hini,"Settings","Halt",szMsg);
      //закрываем .ini файл
      PrfCloseProfile(hini);}
   else MessageBox(HWND_DESKTOP, IDMSG_CANNOTWRITESETTINGS,
           "Warning", MB_OK | MB_ERROR, TRUE);
}   /* End of ClosePrf */
/**************************************************************************
 *  Name       : HScoresPrf(BOOL bChange)
 *
 *  Description: пишет HighScores в ini-файл.
 *
 *  Concepts:	  запрашивает имя игрока и пишет все
 *      в ini-файл.
 *************************************************************************/
VOID HScoresPrf(BOOL bChange)
{  HINI hini;//ini file handle
   char szMsg[256];
   char szHNames[10][256];
   int  i;
   SHORT sBuff,aHScores[10];
   char szNewScore[15];

   if((hini = PrfOpenProfile(hab,"bb.ini"))) {
      for(i=0;i<10;i++) {//читаем список чемпионов
         sprintf(szMsg,"%d",i+1);
         aHScores[i] = PrfQueryProfileInt(hini,"High Scores",szMsg,0);
         sprintf(szMsg,"Name%d",i+1);
         PrfQueryProfileString(hini,"High Scores",szMsg,
            "Noname",szHNames[i],256);
         pszHNames[i] = szHNames[i]; }
      pHScores = aHScores;
      if(bChange){//вставка нового чемпиона
         szName = szHNames[9]; aHScores[9] = iScore;
         /*диалог брачи имени*/
         WinDlgBox( HWND_DESKTOP, /*где рисуем*/
            hwndMainFrame,/*владелец*/
            DlgProc,      /*диалоговая процедура*/
            (HMODULE)0,	  /*указатель модуля*/
            DLG_ENTERNAME,/*указатель диалога в .rc*/
            NULL);		  /*на нет и суда нет*/
         if(bChange == 2) strcat(szName," - winner!"); i=0;
         //упорядочивание
         for(i=9;i>0 && aHScores[i-1] < aHScores[i];i--) {
            strcpy(szMsg,szHNames[i]);//обмен именами
            strcpy(szHNames[i],szHNames[i-1]);
            strcpy(szHNames[i-1],szMsg);
            sBuff = aHScores[i-1];//обмен очками
            aHScores[i-1] = aHScores[i]; aHScores[i] = sBuff;
            sprintf(szNewScore,"%d",aHScores[i]);
            sprintf(szMsg,"%d",i+1);
            PrfWriteProfileString(hini,"High Scores",szMsg,szNewScore);
            sprintf(szMsg,"Name%d",i+1);
            PrfWriteProfileString(hini,"High Scores",szMsg,szHNames[i]);}
         sprintf(szNewScore,"%d",aHScores[i]);
         sprintf(szMsg,"%d",i+1);
         PrfWriteProfileString(hini,"High Scores",szMsg,szNewScore);
         sprintf(szMsg,"Name%d",i+1);
         PrfWriteProfileString(hini,"High Scores",szMsg,szHNames[i]);}
         /*диалог показа HScore'сов*/
      WinDlgBox( HWND_DESKTOP,	/*где рисуем*/
         hwndMainFrame,  /*владелец*/
         HScoresDlgProc, /*диалоговая процедура*/
         (HMODULE)0,	    /*указатель модуля*/
         DLG_HIGHSCORES, /*указатель диалога в .rc*/
         NULL);		    /*на нет и суда нет*/
         PrfCloseProfile(hini);}
   else MessageBox(HWND_DESKTOP, IDMSG_CANNOTLOADHSCORES,
          (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
}   /* End of HScoresPrf */
/**************************************************************************
 *  Name       : InitLevel()
 *
 *  Description: Инициализирует новый уровень
 *
 *  Parameters : usl = на какой уроень переходим
 *************************************************************************/
VOID InitLevel(USHORT usl)
{
   if(bGame){//если идет игра
      WinStopTimer(hab,hwndMain,IDT_MOVE);
      WinStopTimer(hab,hwndMain,IDT_GAME);}
   usLevel = usl; InitNewGame(0);
   WinInvalidateRect(hwndMain,NULL,FALSE);
}   /* End of InitLevel */
/**************************************************************************
 *  Name       : InitFont();
 *
 *  Description: должна брать настройки шрифта
 *
 *  Concepts:	 пока ставит размер строки в целях его дальнейшего
 *		 использования и обкатки разных размеров строки.
 *************************************************************************/
BOOL InitFont( HDC hdc)
{  HPS hps;
   FONTMETRICS fmDefaultFont;
   SIZEL sizel = {0};

// get presentation space
hps = GpiCreatePS( WinQueryAnchorBlock( HWND_DESKTOP),
                   hdc,
                   &sizel,
                   PU_ARBITRARY | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC);
if (hps) {
   // determine line height of current font, which is the default
   // this saves us from selecting a font first...
   memset( &fmDefaultFont, 0, sizeof( fmDefaultFont));
   GpiQueryFontMetrics( hps, sizeof( fmDefaultFont), &fmDefaultFont);

   // we use fmDefaultFont.lMaxDescender * 2, otherwise the text
   // would just fit into the line
   LineHeight = fmDefaultFont.lMaxBaselineExt + (fmDefaultFont.lMaxDescender * 2);
   GpiDestroyPS( hps); }
return 0;
}
/***************************  End of init.c  ***************************/

