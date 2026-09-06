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
POINTL LevelBeginptl;//��砫� ������ '�஢���'
POINTL LevelEndptl;//����� ������ '�஢���'
POINTL ScoreEndptl;//����� ������ '�窨'
POINTL TimeEndptl;//����� ������ '�६�'
/* Entry point declarations */

/**************************************************************************
 *  Name       : CellHit(prcl, i, j)
 *
 *  Description: TRUE when the cell (i,j) overlaps the update region.
 *
 *  Concepts:	  Tests the same inclusive pixel range that Quatro()
 *		  paints, so only exposed cells are redrawn.
 *************************************************************************/
static BOOL CellHit(RECTL *prcl, int i, int j)
{  int cl = j*BmpSize + 1;       /* first painted pixel, left   */
   int cr = j*BmpSize + BmpSize; /* past the last painted pixel */
   int cb = i*BmpSize;           /* first painted pixel, bottom */
   int ct = i*BmpSize + BmpSize; /* past the top row            */

   if(prcl->xRight <= cl) return FALSE;
   if(prcl->xLeft  >= cr) return FALSE;
   if(prcl->yTop   <= cb) return FALSE;
   if(prcl->yBottom>= ct) return FALSE;
   return TRUE;
}   /* End of CellHit */

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
   //��㥬 ���� (only the exposed cells)
   for(i=0;i<Row;i++)
      for(j=0;j<Col;j++)
         if(CellHit(&rclUpdate,i,j)) Quatro(&hps,i,j);
   if(CellHit(&rclUpdate,Runner.yBottom,Runner.xLeft))
      Kpyr(&hps,Runner.yBottom,Runner.xLeft,CLR_RUNNER);
   for(i=0;i<QSize;i++) {
      if(CellHit(&rclUpdate,Hunters[i].yBottom,Hunters[i].xLeft))
         Kpyr(&hps,Hunters[i].yBottom,Hunters[i].xLeft,CLR_HUNTERS);
      if(CellHit(&rclUpdate,Balls[i].yBottom,Balls[i].xLeft))
         Kpyr(&hps,Balls[i].yBottom, Balls[i].xLeft,CLR_BALLS);}
   //����� (status strip) if it was exposed
   if(rclUpdate.yTop > BmpSize*Row && rclUpdate.yBottom < BmpSize*Row+LineHeight)
      CTPOKA(&hps,1);
   WinEndPaint(hps);
}   /* End of MainPaint	  */
/**************************************************************************
 *
 *  Name       : Quatro(*HPS phps,int i, int j)
 *
 *  Description: ���� �����⨪
 *
 *  Concepts:  ����砥� 㪠��⥫� �� ����࠭�⢮ �⮡ࠦ����
 *	       � ���� ������ ࠧ��஬ BmpSize � ���न��⠬�
 *        i � j
 *
 *
 *  API's      :
 *
 *  Parameters :  phps - 㪠��⥫� �� hps
 *                i,j - ����� ������� ������ Field
 *************************************************************************/
VOID Quatro(PHPS phps,int i, int j)
{  RECTL rec;//��� �ᮢ���
   POINTL ptl;//�㤠 � ��㤠 �ᮢ���
   //��㥬 ������
   if(Field == NULL) return;//�᫨ ���樠����樨 �� �뫮
   rec.xLeft   = j*BmpSize+1;
   rec.xRight  = j*BmpSize+BmpSize;
   rec.yBottom = i*BmpSize;
   rec.yTop    = i*BmpSize+BmpSize-1;
   WinFillRect(*phps, &rec, Field[i][j]);
   if(bStyle){//��㥬 ����� 3D
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
 *  Description: ���� ��㦮�
 *
 *  Concepts:  ����砥� 㪠��⥫� �� ����࠭�⢮ �⮡ࠦ����
 *	       � ���� ��� ࠧ��஬ BmpSize � ���न��⠬�
 *        i � j 梥�  lColor
 *
 *  Parameters :  phps - 㪠��⥫� �� hps
 *                i,j - ����� ������� ������ Field
 *                lColor - 梥� ��㦪�
 *************************************************************************/
VOID Kpyr(PHPS phps,int i, int j, long lColor)
{  ARCPARAMS ap = {1,1,0,0};//஢�� ���
   POINTL ptl;//�㤠 � ��㤠 �ᮢ���

   GpiSetArcParams(*phps,&ap);//஢�� ���
   GpiSetColor(*phps,CLR_WHITE);//���� ������
   ptl.x=j*BmpSize+BmpSize/2;//業�� ��㣠
   ptl.y=i*BmpSize+BmpSize/2-1;
   GpiMove(*phps,&ptl);//� 業�� ��㣠
   GpiFullArc(*phps,DRO_OUTLINE,//��㥬 ������
      MAKEFIXED(BmpSize/2,BmpSize/2));
   GpiSetColor(*phps,lColor);//梥� ����७����
   GpiFullArc(*phps,DRO_FILL,//��㥬 ����७�����
      MAKEFIXED(BmpSize/2-1,BmpSize/2-1));
   if(bStyle){//��㥬 ������� 3D
      RECTL rec;//��� �ᮢ���
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
 *  Description: ���� �㪢�
 *
 *  Concepts:  ����砥� 㪠��⥫� �� ����࠭�⢮ �⮡ࠦ����
 *	       � ���� ⥪�騥 ��ਡ��� ����: �஢��� � �窨.
 *
 *  API's      :
 *
 *  Parameters :  phps - 㪠��⥫� �� hps
 *        usAll = ����ᮢ뢠�� �� ��� ⮫쪮 �窨
 *        0 - �窨
 *        1 - ��
 *        2 - �६�
 *************************************************************************/
VOID CTPOKA(PHPS phps, USHORT usAll)
{  POINTL ptl;//��� �ᮢ���
   RECTL rec;//䮭
   char sz[20];
   char fmt[20];//������ �ᥬ��� ��� ���па�

   if(usAll)rec.xLeft   = 0;//��襬 ��,�६�,�஢���
   else     rec.xLeft   = LevelEndptl.x;//�窨
   if(usAll == 2)//��襬 �६�
      rec.xRight  = TimeEndptl.x;//TimeEndptl 㦥 ��뢠����
   else rec.xRight  = Col*BmpSize+2;//��襬 ��,�窨,�஢���
   rec.yBottom = BmpSize*Row;
   rec.yTop    = BmpSize*Row+LineHeight;
   WinFillRect(*phps, &rec, CLR_STRING);
   GpiSetColor(*phps,CLR_CHAR);//梥� ����७����
   ptl.y=BmpSize*Row+5;
   if(usAll == 2 || usAll == 1){//��襬 �� ��� �६�
      WinLoadString(hab, (HMODULE)0, iLangBase+IDS_FMT_TIME, 20, fmt);
      sprintf(sz,fmt,usTime);
      ptl.x = 5;
      GpiCharStringAt(*phps,&ptl,strlen(sz),sz);
      GpiQueryCurrentPosition(*phps,&TimeEndptl);}
   if(usAll == 1){//�᫨ ��襬 ��
      WinLoadString(hab, (HMODULE)0, iLangBase+IDS_FMT_LEVEL, 20, fmt);
      sprintf(sz,fmt,usLevel);
      ptl.x = LevelBeginptl.x;
      GpiCharStringAt(*phps,&ptl,strlen(sz),sz);
      GpiQueryCurrentPosition(*phps,&LevelEndptl);}
   if(usAll == 0 || usAll == 1){//��襬 �� ��� �窨
      WinLoadString(hab, (HMODULE)0, iLangBase+IDS_FMT_SCORE, 20, fmt);
      sprintf(sz,fmt,
         iScore,
         ((iScore - iOScore)*125)/((Row-2)*(Col-2)));// 4/5 ����=100%
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
 *  Description: ���� �����⨪ � �� ���� ��� 梥�
 *
 *  Concepts:  ������ ��� ���筮�� �����⨪�. ����室������
 *	       � ��� �������� �� ࠧࠡ�⪥ �������. ���� ��
 *        ���室��, � ��।��뢠�� ��� ���稫� ��
 *        ��५���稢��� ��� �ணࠬ��. ����-�����.
 *
 *  Parameters :  phps - 㪠��⥫� �� hps
 *                i,j - ���न����
 *                lColor - 梥�
 *************************************************************************/
VOID DlgQuatro(PHPS phps,int i, int j, LONG lColor)
{  RECTL rec;//��� �ᮢ���
   POINTL ptl;//�㤠 � ��㤠 �ᮢ���
   //��㥬 ������
   rec.xLeft   = j+1;
   rec.xRight  = j+bs;
   rec.yBottom = i;
   rec.yTop    = i+bs-1;
   WinFillRect(*phps, &rec, lColor);
   if(st){//��㥬 ����� 3D
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
 *  Description: ���� ��㦮� � �� ����
 *
 *  Concepts:  ����砥� 㪠��⥫� �� ����࠭�⢮ �⮡ࠦ����
 *	       � ���� ��� ࠧ��஬ BmpSize � ���न��⠬�
 *        i � j 梥�  lColor
 *
 *  Parameters :  phps - 㪠��⥫� �� hps
 *                i,j - ���न���� ��㦪�
 *                lColor - 梥� ��㦪�
 *************************************************************************/
VOID DglKpyr(PHPS phps,int i, int j, long lColor)
{  ARCPARAMS ap = {1,1,0,0};//஢�� ���
   POINTL ptl;//�㤠 � ��㤠 �ᮢ���

   GpiSetArcParams(*phps,&ap);//஢�� ���
   GpiSetColor(*phps,CLR_WHITE);//���� ������
   ptl.x = j+bs/2;//業�� ��㣠
   ptl.y = i+bs/2-1;
   GpiMove(*phps,&ptl);//� 業�� ��㣠
   GpiFullArc(*phps,DRO_OUTLINE,//��㥬 ������
      MAKEFIXED(bs/2,bs/2));
   GpiSetColor(*phps,lColor);//梥� ����७����
   GpiFullArc(*phps,DRO_FILL,//��㥬 ����७�����
      MAKEFIXED(bs/2-1,bs/2-1));
   if(st){//��㥬 ������� 3D
      RECTL rec;//��� �ᮢ���
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
 *  Description: ������ 梥� � ����ᨬ��� �� ������
 *
 *  Concepts:  � ����ᨬ��� �� ⮣�, �� � ����� 梥� ��� �������
 *        ������ ���(梥�) ⥬��� ��� ��⠢��� ��� ���������
 *
 *  Parameters :  lColor - 梥�
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

