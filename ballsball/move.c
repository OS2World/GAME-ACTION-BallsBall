/**************************************************************************
 *  File name  :  move.c
 *
 *  Description:  ��� ����� ᮤ�ন� �㭪樨 ��� ����஫� �
 *		  �������� ࠧ��� �ਪ��.
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
 *  Description: ������� ���न���� ������
 *
 *  Concepts:	  �᫨ �� ��������, ����� ���न���� ������
 *************************************************************************/
VOID MoveRunner()
{
   if(Runner.xLeft   + Runner.xRight <  0   ||//�஢��塞
      Runner.xLeft   + Runner.xRight >= Col ||//�� �����������
      Runner.yBottom + Runner.yTop   <  0   ||//��।�������
      Runner.yBottom + Runner.yTop   >= Row ){
      Runner.xRight = 0;//������� ���㤠
      Runner.yTop   = 0;}
   Runner.xLeft   += Runner.xRight;//�������
   Runner.yBottom += Runner.yTop;
}   /* End of MoveHunter */
/**************************************************************************
 *  Name       : MoveHunter(int iNum)
 *
 *  Description: ������� ���न���� ��⭨�� � ����஬ iNum
 *
 *  Concepts:	 ��᫥��� �������� ���� ��᫮��樨 �
 *		 ࠧ��뢠�� ��, �᫨ ����.
 *
 *  Parameters :  iNum = ����� ��।��������� ��⭨��
 *************************************************************************/
VOID MoveHunter(int iNum)
{  LONG *x,*y,*f,*lr;//��뫪� �� ���न����
   int iXMax,iYMax,i,j;//���孨� �࠭� � ᬥ饭��
   USHORT usCase = 0;
   float fRandom;

   if(Hunters[iNum].yTop) {//�᫨ ��������� �� ��ਪ�
      x  = &(Hunters[iNum].xLeft);y  = &(Hunters[iNum].yBottom);
      f  = &(Hunters[iNum].yTop); lr = &(Hunters[iNum].xRight);
      i  = 1;j = 0;/*���� - �� ����*/iXMax = Col;iYMax = Row;}
   else  {//�᫨ ��������� �� ����
      x  = &(Hunters[iNum].yBottom);y  = &(Hunters[iNum].xLeft);
      f  = &(Hunters[iNum].xRight); lr = &(Hunters[iNum].yTop);
      i = 0;j = 1;/*���� - �� ��ਪ�*/iXMax = Row;iYMax = Col;}
   if(*x + 1 < iXMax &&
      Field[Hunters[iNum].yBottom+j][Hunters[iNum].xLeft+i] == CLR_CHANNEL)
      usCase =  1;
   i*=-1;j*=-1;//� ��㣮� ��஭�
   if(*x - 1 >=0     &&
      Field[Hunters[iNum].yBottom+j][Hunters[iNum].xLeft+i] == CLR_CHANNEL)
      usCase += 2;
   if(Hunters[iNum].yTop){i = 0;j = *f;}//�᫨ ��������� �� ��ਪ�
   else                  {i = *f;j = 0;}//�᫨ ��������� �� ����
   if(*y + *f >=0 && *y + *f < iYMax &&
      Field[Hunters[iNum].yBottom+j][Hunters[iNum].xLeft+i] == CLR_CHANNEL)
      usCase += 4;
   if(usCase == 3 || usCase == 5 || usCase == 6)
      fRandom = rand()*2/RAND_MAX;//�롮� �� ���� ���ࠢ�����
   if(usCase == 7)
      fRandom = rand()*3/RAND_MAX;//�롮� �� ��� ���ࠢ�����
   switch(usCase) {
      case 0: *f *= -1; *y += *f; break;//�����!
      case 1: *x +=  1 ; *f = 0; *lr =  1; break;//���� ���ࠢ�����
      case 2: *x -=  1 ; *f = 0; *lr = -1; break;
      case 4: *y += *f; break;
      case 3://��� ���ࠢ�����
         if(fRandom < 1){*x += 1; *f = 0; *lr =  1;}
         else           {*x -= 1; *f = 0; *lr = -1;}break;
      case 5:
         if(fRandom < 1){*x += 1; *f = 0; *lr =  1;}
         else            *y += *f;break;
      case 6:
         if(fRandom < 1){*x -= 1; *f = 0; *lr = -1;}
         else            *y += *f;break;
      case 7://�� ���ࠢ�����
         if(fRandom < 1)     {*x += 1; *f = 0; *lr =  1;}
         else if(fRandom < 2){*x -= 1; *f = 0; *lr = -1;}
         else                 *y += *f;break;
      default: break;}
}   /* End of MoveHunter */
/**************************************************************************
 *  Name       : MoveBall(int iNum)
 *
 *  Description: ������� ���न���� �ਪ� � ����஬ iNum
 *
 *  Concepts:	 ��᫥��� �������� ���� ��᫮��樨 �
 *		 ࠧ��뢠�� ��, �᫨ ����.
 *
 *  API's      :
 *
 *  Parameters :  iNum = ����� ��।��������� �ਪ�
 *
 *  Return     :  ��⨭�, �᫨ �ਪ �������, ����, �᫨ ��
 *     ������(�㦭� ��� ����ᮢ�� ���)
 *************************************************************************/
BOOL MoveBall(int iNum)
{
   if(Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL ||
      Field[Balls[iNum].yBottom][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL ||
      Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft] == CLR_CHANNEL) {
      if(Field[Balls[iNum].yBottom][Balls[iNum].xLeft+Balls[iNum].xRight] != CLR_CHANNEL &&
         Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft]   != CLR_CHANNEL) {
            Balls[iNum].xRight *= -1;//㤠� �� 㣮�
            Balls[iNum].yTop   *= -1;}
      else {if(Field[Balls[iNum].yBottom][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL)
               Balls[iNum].xRight *= -1;//���⨪��쭠� �⥭�
            if(Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft] == CLR_CHANNEL)
               Balls[iNum].yTop   *= -1;}/*of else*/}//of if
   if(Field[Balls[iNum].yBottom+Balls[iNum].yTop][Balls[iNum].xLeft+Balls[iNum].xRight] == CLR_CHANNEL){
      Balls[iNum].yTop = 0;Balls[iNum].xRight = 0;
      iScore += 100;return 1;}//�� �������
   else {//�������
      Balls[iNum].yBottom+= Balls[iNum].yTop;
      Balls[iNum].xLeft  += Balls[iNum].xRight;return 0;}
}   /* End of MoveBall */
/**************************************************************************
 *  Name       : Replace(long lOld, long lNew, PHPS phps)
 *
 *  Description: ������� ������ Field lOld �� lNew
 *
 *  Concepts:	  ��ॡ�ࠥ� �� ���⪨ Field � lOld �����
 *      ᮤ�ন��� ���⮪ � lOld �� lNew.
 *
 *  Parameters :  lOld = ��஥ ᮤ�ন���
 *      lNew = ����� ᮤ�ন���
 *      phps = 㪠��⥫� �� ��
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