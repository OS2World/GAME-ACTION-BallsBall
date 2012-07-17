/**************************************************************************
 *  File name  :  move.c
 *
 *  Description:  Этот модуль содержит функции для контроля и
 *		  движения разных шариков.
 *
 *		  This source file contains the following functions:
 *      MoveRunner()
 *      MoveHunter(int iNum)
 *      MoveBall(int iNum)
 *      Replace(long lOld, long lNew, PHPS phps)
 *
 *  Concepts   :  perpetuum mobile
 *
 *  API's      :
 *
 *    Files    :  OS2.H, STDLIB.H, XTRN.H, GAME.H
 *************************************************************************/
/* Include files, macros, defined constants, and externs */
#include <os2.h>
#include <stdlib.h>
#include "xtrn.h"
#include "game.h"
/* Global variables */

/* Entry point declarations */

/**************************************************************************
 *  Name       : MoveRunner()
 *
 *  Description: изменяет координаты беглеца
 *
 *  Concepts:	  если это возможно, меняет координаты беглеца
 *************************************************************************/
VOID MoveRunner()
{
   if(Runner.xLeft   + Runner.xRight <  0   ||//проверяем
      Runner.xLeft   + Runner.xRight >= Col ||//на возможность
      Runner.yBottom + Runner.yTop   <  0   ||//передвижения
      Runner.yBottom + Runner.yTop   >= Row ){
      Runner.xRight = 0;//двигать некуда
      Runner.yTop   = 0;}
   Runner.xLeft   += Runner.xRight;//двигаем
   Runner.yBottom += Runner.yTop;
}   /* End of MoveHunter */
/**************************************************************************
 *  Name       : MoveHunter(int iNum)
 *
 *  Description: изменяет координаты охотника с номером iNum
 *
 *  Concepts:	 обследует возможные места дислокации и
 *		 разыгрывает их, если надо.
 *
 *  Parameters :  iNum = номер передвигаемого охотника
 *************************************************************************/
VOID MoveHunter(int iNum)
{  LONG *x,*y,*f,*lr;//ссылки на координаты
   int iXMax,iYMax,i,j;//верхние грани и смещения
   USHORT usCase = 0;
   float fRandom;

   if(Hunters[iNum].yTop) {//если двигаемся по игрику
      x  = &(Hunters[iNum].xLeft);y  = &(Hunters[iNum].yBottom);
      f  = &(Hunters[iNum].yTop); lr = &(Hunters[iNum].xRight);
      i  = 1;j = 0;/*бока - по иксу*/iXMax = Col;iYMax = Row;}
   else  {//если двигаемся по иксу
      x  = &(Hunters[iNum].yBottom);y  = &(Hunters[iNum].xLeft);
      f  = &(Hunters[iNum].xRight); lr = &(Hunters[iNum].yTop);
      i = 0;j = 1;/*бока - по игрику*/iXMax = Row;iYMax = Col;}
   if(*x + 1 < iXMax &&
      Field[Hunters[iNum].yBottom+j][Hunters[iNum].xLeft+i] == CLR_CHANNEL)
      usCase =  1;
   i*=-1;j*=-1;//с другой стороны
   if(*x - 1 >=0     &&
      Field[Hunters[iNum].yBottom+j][Hunters[iNum].xLeft+i] == CLR_CHANNEL)
      usCase += 2;
   if(Hunters[iNum].yTop){i = 0;j = *f;}//если двигаемся по игрику
   else                  {i = *f;j = 0;}//если двигаемся по иксу
   if(*y + *f >=0 && *y + *f < iYMax &&
      Field[Hunters[iNum].yBottom+j][Hunters[iNum].xLeft+i] == CLR_CHANNEL)
      usCase += 4;
   if(usCase == 3 || usCase == 5 || usCase == 6)
      fRandom = rand()*2/RAND_MAX;//выбор из двух направлений
   if(usCase == 7)
      fRandom = rand()*3/RAND_MAX;//выбор из трех направлений
   switch(usCase) {
      case 0: *f *= -1; *y += *f; break;//назад!
      case 1: *x +=  1 ; *f = 0; *lr =  1; break;//одно направление
      case 2: *x -=  1 ; *f = 0; *lr = -1; break;
      case 4: *y += *f; break;
      case 3://два направления
         if(fRandom < 1){*x += 1; *f = 0; *lr =  1;}
         else           {*x -= 1; *f = 0; *lr = -1;}break;
      case 5:
         if(fRandom < 1){*x += 1; *f = 0; *lr =  1;}
         else            *y += *f;break;
      case 6:
         if(fRandom < 1){*x -= 1; *f = 0; *lr = -1;}
         else            *y += *f;break;
      case 7://три направления
         if(fRandom < 1)     {*x += 1; *f = 0; *lr =  1;}
         else if(fRandom < 2){*x -= 1; *f = 0; *lr = -1;}
         else                 *y += *f;break;
      default: break;}
}   /* End of MoveHunter */
/**************************************************************************
 *  Name       : MoveBall(int iNum)
 *
 *  Description: изменяет координаты шарика с номером iNum
 *
 *  Concepts:	 обследует возможные места дислокации и
 *		 разыгрывает их, если надо.
 *
 *  API's      :
 *
 *  Parameters :  iNum = номер передвигаемого шарика
 *
 *  Return     :  Истина, если шарик поймали, Ложь, если еще
 *     бегает(нужно для перерисовки счета)
 *************************************************************************/
BOOL MoveBall(int iNum)
{
   if(Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL ||
      Field[Balls[iNum].yBottom][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL ||
      Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft] == CLR_CHANNEL) {
      if(Field[Balls[iNum].yBottom][Balls[iNum].xLeft+Balls[iNum].xRight] != CLR_CHANNEL &&
         Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft]   != CLR_CHANNEL) {
            Balls[iNum].xRight *= -1;//удар об угол
            Balls[iNum].yTop   *= -1;}
      else {if(Field[Balls[iNum].yBottom][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL)
               Balls[iNum].xRight *= -1;//вертикальная стена
            if(Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft] == CLR_CHANNEL)
               Balls[iNum].yTop   *= -1;}/*of else*/}//of if
   if(Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL){
      Balls[iNum].yTop = 0;Balls[iNum].xRight = 0;
      iScore += 100;return 1;}//не двигаем
   else {//двигаем
      Balls[iNum].yBottom+= Balls[iNum].yTop;
      Balls[iNum].xLeft  += Balls[iNum].xRight;return 0;}
}   /* End of MoveBall */
/**************************************************************************
 *  Name       : Replace(long lOld, long lNew, PHPS phps)
 *
 *  Description: заменяет элементы Field lOld на lNew
 *
 *  Concepts:	  перебирает все клетки Field с lOld меняет
 *      содержимое клеток с lOld на lNew.
 *
 *  Parameters :  lOld = старое содержимое
 *      lNew = новое содержимое
 *      phps = указатель на хпс
 *************************************************************************/
VOID Replace(long lOld, long lNew, PHPS phps)
{  int i,j;

   for(i=0;i<Col;i++)
      for(j=0;j<Row;j++)
         if (Field[j][i] == lOld){
            Field[j][i] = lNew;
            if (lOld == CLR_NEW && lNew == CLR_CHANNEL)iScore++;
            else if (lOld == CLR_NEW && lNew == CLR_BREAK)iScore--;
            if (phps != NULL) Quatro(phps,j,i);}
}   /* End of Replace */
/***************************  End of user.c  ****************************/
