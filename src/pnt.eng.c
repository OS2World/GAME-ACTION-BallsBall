/**************************************************************************
 *  File name  :  pnt.c
 *
 *  Description:  This module contains the code for the main client
 *		  window painting.
 *
 *		  This source file contains the following functions:
 *
 *		  MainPaint(hwnd)
 *      Quatro( phps,i, j)
 *      FieldRedraw( phps)
 *      Kpyr( phps,i, j, lColor)
 *      CTPOKA( phps, bAll)
 *      DlgQuatro( phps,i, j, lColor)
 *      DlgKpyr( phps,i, j, lColor)
 *      VOID ColorCorrect(lColor)
 *
 *  Concepts   :  window painting
 *
 *  API's      :  WinBeginPaint
 *		  WinFillRect
 *		  WinEndPaint
 *
 *  Required
 *    Files    :  OS2.H, MAIN.H, XTRN.H, game.h
 *************************************************************************/
/* Include files, macros, defined constants, and externs */

#define	 INCL_WINSYS
#define	 INCL_GPIPRIMITIVES

#include <os2.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "game.h"
#include "xtrn.h"

/* Global variables */
POINTL LevelBeginptl;//начало надписи 'уровень'
POINTL LevelEndptl;//конец надписи 'уровень'
POINTL ScoreEndptl;//конец надписи 'очки'
POINTL TimeEndptl;//конец надписи 'время'
/* Entry point declarations */

/**************************************************************************
 *
 *  Name       : MainPaint(hwnd)
 *
 *  Description: Paints the main client window.
 *
 *  Concepts:  Routine is called whenver the client window
 *	       procedure receives a WM_PAINT message
 *
 *	       - begins painting by calling WinBeginPaint
 *		   and retrieving the HPS for the window
 *	       - performs any painting desired
 *	       - ends painting by calling WinEndPaint
 *
 *  API's      :  WinBeginPaint
 *		  WinFillRect
 *		  WinEndPaint
 *
 *  Parameters :  hwnd	   = window handle
 *************************************************************************/
VOID MainPaint(HWND hwnd)
{  RECTL rclUpdate;
   HPS hps;
   int i,j;

   hps = WinBeginPaint(hwnd, NULLHANDLE, &rclUpdate);
   WinFillRect(hps, &rclUpdate, CLR_WHITE);
   //рисуем поле
   for(i=0;i<Row;i++)for(j=0;j<Col;j++)Quatro(&hps,i,j);
   Kpyr(&hps,Runner.yBottom,Runner.xLeft,CLR_RUNNER);
   for(i=0;i<QSize;i++) {
      Kpyr(&hps,Hunters[i].yBottom,Hunters[i].xLeft,CLR_HUNTERS);
      Kpyr(&hps,Balls[i].yBottom, Balls[i].xLeft,CLR_BALLS);}
   //цыфры
   CTPOKA(&hps,1);
   WinEndPaint(hps);
}   /* End of MainPaint	  */
/**************************************************************************
 *
 *  Name       : Quatro(*HPS phps,int i, int j)
 *
 *  Description: рисует квадратик
 *
 *  Concepts:  Получает указатель на пространство отображения
 *	       и рисует квадрат размером BmpSize с координатами
 *        i и j
 *
 *
 *  API's      :
 *
 *  Parameters :  phps - указатель на hps
 *                i,j - номера элемента матрицы Field
 *************************************************************************/
VOID Quatro(PHPS phps,int i, int j)
{  RECTL rec;//где рисовать
   POINTL ptl;//куда и откуда рисовать
   //рисуем квадрат
   if(Field == NULL) return;//если инициализации не было
   rec.xLeft   = j*BmpSize+1;
   rec.xRight  = j*BmpSize+BmpSize;
   rec.yBottom = i*BmpSize;
   rec.yTop    = i*BmpSize+BmpSize-1;
   WinFillRect(*phps, &rec, Field[i][j]);
   if(bStyle){//рисуем линии 3D
      if(Field[i][j]>6)
         GpiSetColor(*phps,CLR_DARKGRAY);
      else
         GpiSetColor(*phps,Field[i][j]+8);
      ptl.x=j*BmpSize;
      ptl.y=i*BmpSize;
      GpiMove(*phps,&ptl);
      ptl.x=j*BmpSize+BmpSize-1;
      GpiLine(*phps,&ptl);
      GpiMove(*phps,&ptl);
      ptl.y=i*BmpSize+BmpSize;
      GpiLine(*phps,&ptl);
      ptl.x=j*BmpSize+BmpSize-2;
      ptl.y=i*BmpSize+BmpSize-1;
      GpiMove(*phps,&ptl);
      ptl.y=i*BmpSize+1;
      GpiLine(*phps,&ptl);
      GpiMove(*phps,&ptl);
      ptl.x=j*BmpSize+1;
      GpiLine(*phps,&ptl);}
}   /* End of Quatro */
/**************************************************************************
 *
 *  Name       : Kpyr(HPS* phps,int i, int j, long lColor)
 *
 *  Description: рисует кружок
 *
 *  Concepts:  Получает указатель на пространство отображения
 *	       и рисует круг размером BmpSize с координатами
 *        i и j цвета  lColor
 *
 *  Parameters :  phps - указатель на hps
 *                i,j - номера элемента матрицы Field
 *                lColor - цвет кружка
 *************************************************************************/
VOID Kpyr(PHPS phps,int i, int j, long lColor)
{  ARCPARAMS ap = {1,1,0,0};//ровный круг
   POINTL ptl;//куда и откуда рисовать

   GpiSetArcParams(*phps,&ap);//ровный круг
   GpiSetColor(*phps,CLR_WHITE);//белый ободок
   ptl.x=j*BmpSize+BmpSize/2;//центр круга
   ptl.y=i*BmpSize+BmpSize/2-1;
   GpiMove(*phps,&ptl);//в центр круга
   GpiFullArc(*phps,DRO_OUTLINE,//рисуем ободок
      MAKEFIXED(BmpSize/2,BmpSize/2));
   GpiSetColor(*phps,lColor);//цвет внутренности
   GpiFullArc(*phps,DRO_FILL,//рисуем внутренность
      MAKEFIXED(BmpSize/2-1,BmpSize/2-1));
   if(bStyle){//рисуем элемент 3D
      RECTL rec;//где рисовать
      rec.xLeft   = j*BmpSize+BmpSize/2+1;
      rec.xRight  = j*BmpSize+BmpSize/2+BmpSize/4+1;
      rec.yBottom = i*BmpSize+BmpSize/2;
      rec.yTop    = i*BmpSize+BmpSize/2+BmpSize/4;
      WinFillRect(*phps, &rec, CLR_WHITE);}
}   /* End of Kpyr */
/**************************************************************************
 *
 *  Name       : CTPOKA(HPS* phps, BOOL bAll)
 *
 *  Description: рисует буквы
 *
 *  Concepts:  Получает указатель на пространство отображения
 *	       и пишет текущие атрибуты игры: уровень и очки.
 *
 *  API's      :
 *
 *  Parameters :  phps - указатель на hps
 *        usAll = перерисовывать все или только очки
 *        0 - очки
 *        1 - все
 *        2 - время
 *************************************************************************/
VOID CTPOKA(PHPS phps, USHORT usAll)
{  POINTL ptl;//где рисовать
   RECTL rec;//фон
   char sz[20];

   if(usAll)rec.xLeft   = 0;//пишем все,время,уровень
   else     rec.xLeft   = LevelEndptl.x;//очки
   if(usAll == 2)//пишем время
      rec.xRight  = TimeEndptl.x;//TimeEndptl уже вызывалось
   else rec.xRight  = Col*BmpSize+2;//пишем все,очки,уровень
   rec.yBottom = BmpSize*Row;
   rec.yTop    = BmpSize*Row+LineHeight;
   WinFillRect(*phps, &rec, CLR_STRING);
   GpiSetColor(*phps,CLR_CHAR);//цвет внутренности
   ptl.y=BmpSize*Row+5;
   if(usAll == 2 || usAll == 1){//пишем все или время
      sprintf(sz,"Time-%d ",usTime);
      ptl.x = 5;
      GpiCharStringAt(*phps,&ptl,strlen(sz),sz);
      GpiQueryCurrentPosition(*phps,&TimeEndptl);}
   if(usAll == 1){//если пишем все
      sprintf(sz,"Level-%d ",usLevel);
      ptl.x = LevelBeginptl.x;
      GpiCharStringAt(*phps,&ptl,strlen(sz),sz);
      GpiQueryCurrentPosition(*phps,&LevelEndptl);}
   if(usAll == 0 || usAll == 1){//пишем все или очки
      sprintf(sz,"Score-%d(%d%%)      ",
         sScore,
         ((sScore - sOScore)*125)/((Row-2)*(Col-2)));// 4/5 поля=100%
      ptl.x = LevelEndptl.x;
      GpiCharStringAt(*phps,&ptl,strlen(sz),sz);
      GpiQueryCurrentPosition(*phps,&ScoreEndptl);}
   if(usAll == 1 && (ScoreEndptl.x > Col*BmpSize ||
      LevelBeginptl.x < TimeEndptl.x )) {
      //sprintf(sz,"T-%d,L-%d,S-%d,CB-%d",TimeEndptl.x+5,LevelBeginptl.x,ScoreEndptl.x,Col*BmpSize);
      //WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,
      //   sz,"OneMore",0,MB_OK);
      LevelBeginptl.x = MAX(TimeEndptl.x+5,
         LevelBeginptl.x-(ScoreEndptl.x - Col*BmpSize+5));
      CTPOKA(phps, usAll);}
}   /* End of CTPOKA */
/**************************************************************************
 *
 *  Name       : DlgQuatro(*HPS phps,int i, int j, LONG lColor)
 *
 *  Description: рисует квадратик в любом месте любого цвета
 *
 *  Concepts:  Родной брат обычного квадратика. Необходимость
 *	       в нем возникла при разработке диалога. Старый не
 *        подходил, и переделывать его значило бы
 *        перелопачивать всю программу. Елки-палки.
 *
 *  Parameters :  phps - указатель на hps
 *                i,j - координаты
 *                lColor - цвет
 *************************************************************************/
VOID DlgQuatro(PHPS phps,int i, int j, LONG lColor)
{  RECTL rec;//где рисовать
   POINTL ptl;//куда и откуда рисовать
   //рисуем квадрат
   rec.xLeft   = j+1;
   rec.xRight  = j+bs;
   rec.yBottom = i;
   rec.yTop    = i+bs-1;
   WinFillRect(*phps, &rec, lColor);
   if(st){//рисуем линии 3D
      if(lColor>6)
         GpiSetColor(*phps,CLR_DARKGRAY);
      else
         GpiSetColor(*phps,lColor+8);
      ptl.x=j;
      ptl.y=i;
      GpiMove(*phps,&ptl);
      ptl.x=j+bs-1;
      GpiLine(*phps,&ptl);
      GpiMove(*phps,&ptl);
      ptl.y=i+bs;
      GpiLine(*phps,&ptl);
      ptl.x=j+bs-2;
      ptl.y=i+bs-1;
      GpiMove(*phps,&ptl);
      ptl.y=i+1;
      GpiLine(*phps,&ptl);
      GpiMove(*phps,&ptl);
      ptl.x=j+1;
      GpiLine(*phps,&ptl);}
}   /* End of DlgQuatro */
/**************************************************************************
 *
 *  Name       : DglKpyr(HPS* phps,int i, int j, long lColor)
 *
 *  Description: рисует кружок в любом месте
 *
 *  Concepts:  Получает указатель на пространство отображения
 *	       и рисует круг размером BmpSize с координатами
 *        i и j цвета  lColor
 *
 *  Parameters :  phps - указатель на hps
 *                i,j - координаты кружка
 *                lColor - цвет кружка
 *************************************************************************/
VOID DglKpyr(PHPS phps,int i, int j, long lColor)
{  ARCPARAMS ap = {1,1,0,0};//ровный круг
   POINTL ptl;//куда и откуда рисовать

   GpiSetArcParams(*phps,&ap);//ровный круг
   GpiSetColor(*phps,CLR_WHITE);//белый ободок
   ptl.x = j+bs/2;//центр круга
   ptl.y = i+bs/2-1;
   GpiMove(*phps,&ptl);//в центр круга
   GpiFullArc(*phps,DRO_OUTLINE,//рисуем ободок
      MAKEFIXED(bs/2,bs/2));
   GpiSetColor(*phps,lColor);//цвет внутренности
   GpiFullArc(*phps,DRO_FILL,//рисуем внутренность
      MAKEFIXED(bs/2-1,bs/2-1));
   if(st){//рисуем элемент 3D
      RECTL rec;//где рисовать
      rec.xLeft   = j+bs/2+1;
      rec.xRight  = j+bs/2+bs/4+1;
      rec.yBottom = i+bs/2;
      rec.yTop    = i+bs/2+bs/4;
      WinFillRect(*phps, &rec, CLR_WHITE);}
}   /* End of Kpyr */
/**************************************************************************
 *
 *  Name       : ColorCorrect(long lColor)
 *
 *  Description: делает цвет в зависимости от клиента
 *
 *  Concepts:  в зависимости от того, кто и какой цвет хочет получить
 *        делает его(цвет) темнее или оставляет без изменений
 *
 *  Parameters :  lColor - цвет
 *************************************************************************/
VOID ColorCorrect(long lColor)
{
   if((p == &h || p == &ba || p == &r)) {
      if (lColor == CLR_CYAN || lColor == CLR_GREEN ||
          lColor == CLR_PINK || lColor == CLR_YELLOW ) *p = lColor + 8;
      else if(lColor == CLR_PALEGRAY) *p = CLR_DARKGRAY;
      else  *p = lColor;}
   else if(p == &s) {
      if (lColor != CLR_PALEGRAY ) *p = lColor + 8;
      else *p = CLR_DARKGRAY; }
   else *p = lColor;
}   /* End of Kpyr */
/***************************  End of pnt.c  ****************************/

