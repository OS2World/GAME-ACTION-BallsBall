/**************************************************************************
 *  File name  :  dlg.c
 *
 *  Description:  This module contains the Dialog Procedures for the user
 *		  defined dialogs as well as any support code they need.
 *
 *		  This source file contains the following functions:
 *
 *		  ProductInfoDlgProc(hwnd, msg, mp1, mp2)
 *		  SetSysMenu(hDlg)
 *      HScoresDlgProc( hwndDlg, msg, mp1, mp2 )
 *      DlgProc(hwndDlg, msg, mp1, mp2 )
 *      SettingsDlgProc(hwndDlg, msg, mp1, mp2 )
 *
 *  Concepts   :  dialog box
 *
 *  API's      :  WinDismissDlg
 *		  WinDefDlgProc
 *		  WinWindowFromID
 *		  WinSendMsg
 *
 *  Required
 *    Files    :  OS2.H, STDIO.H, STRING.H, MAIN.H, DLG.H,
 *    XTRN.H, GAME.H
 *************************************************************************/
/* Include files, macros, defined constants, and externs */

#define	 INCL_WIN
#define	 INCL_WINMENUS
#define	 INCL_WINWINDOWMGR
#define	 INCL_WINFRAMEMGR
#define	 INCL_WINLISTBOXES
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "dlg.h"
#include "xtrn.h"
#include "game.h"

/* Global variables */
char *szName;//��� ������ 祬�����
SHORT *pHScores;//���ᨢ �窮� 祬������
char *(pszHNames[10]);//���ᨢ 祬������
/* �㡫��� ��� ����஥� */
long r,h,ba,c,f,br,n,s,ch,*p;//
BOOL st,so,ha;
int bs,co,ro;//ࠧ��� ���⨭��, �᫮ �⮫�殢 � ��ப
BOOL bDraw;//�ᮢ���� ������� ����஥�
BOOL bChange;//���������� ����ன�� ����
int iNoOK = 0;//�� �室���
/**************************************************************************
 *
 *  Name       : ProductInfoDlgProc(hwnd, msg, mp1, mp2)
 *
 *  Description: Processes all messages sent to the Product information
 *		 dialog
 *
 *  Concepts:  The Product information dialog has only a button control,
 *	       so this routine processes only WM_COMMAND messages.  Any
 *	       WM_COMMAND posted must have come from the OK
 *	       button, so we dismiss the dialog upon receiving it.
 *
 *  API's      :  WinDismissDlg
 *		  WinDefDlgProc
 *
 *  Parameters :  hwnd	   = window handle
 *		  msg	   = message i.d.
 *		  mp1	   = first message parameter
 *		  mp2	   = second message parameter
 *
 *  Return     :  dependent on message sent
 *
 *************************************************************************/
MRESULT EXPENTRY ProductInfoDlgProc(
			 HWND hwnd,	 /* handle of window */
			 USHORT msg,	 /* id of message */
			 MPARAM mp1,	 /* first message parameter */
			 MPARAM mp2)	 /* second message parameter */
{  SWP swpDESKTOP;//����砫�� ���न��� � ࠧ��஢ DESKTOPa

   switch(msg) {
      case WM_INITDLG:
         WinQueryWindowPos(HWND_DESKTOP,&swpDESKTOP);
         WinSetWindowPos(
            hwnd,//�� �㤥� �ந��
            HWND_TOP,//�������� ���
            (swpDESKTOP.cx-424)/2,//x ���न��� ����
            (swpDESKTOP.cy-364)/2,//y ���न��� ����
            424,//x ࠧ���
            364,//y ࠧ���
            SWP_SIZE | SWP_MOVE );
         WinSetWindowPos(
            WinWindowFromID(hwnd,DID_OK),//�� �㤥� �ந��
            HWND_TOP,//�������� ���
            6,//x ���न��� ����
            6,//y ���न��� ����
            412,//x ࠧ���
            32,//y ࠧ���
            SWP_SIZE | SWP_MOVE );
         WinSetWindowPos(
            WinWindowFromID(hwnd,IDA_BITMAP),//�� �㤥� �ந��
            HWND_TOP,//�������� ���
            6,//x ���न��� ����
            40,//y ���न��� ����
            412,//x ࠧ���
            300,//y ࠧ���
            SWP_SIZE | SWP_MOVE );
         SetSysMenu(hwnd); /* system menu for this dialog */
	      return MRFROMSHORT(FALSE);

     case WM_CHAR://����⨥ ������
     case WM_COMMAND:
	   /* no matter what the command, close the dialog */
	       WinDismissDlg(hwnd, TRUE); break;

      default: return(WinDefDlgProc(hwnd, msg, mp1, mp2)); break; }
   return (MRESULT)NULL;
}   /*	End of ProductInfoDlgProc   */
/**************************************************************************
 *
 *  Name       : SetSysMenu(hDlg)
 *
 *  Description: Sets only the Move and Close items of the system menu
 *
 *  Concepts:  Any dialog box is free to call this routine, to edit
 *	       which menu items will appear on its System Menu pulldown.
 *
 *  API's      :  WinWindowFromID
 *		  WinSendMsg
 *
 *  Parameters :  hDlg	   = window handle of the dialog
 *
 *  Return     :  [none]
 *
 *************************************************************************/
VOID SetSysMenu(HWND hDlg)
{  HWND     hSysMenu;
   MENUITEM Mi;
   ULONG    Pos;
   MRESULT  Id;
   SHORT    cItems;

   /*We only want Move and Close in the system menu.*/
   hSysMenu = WinWindowFromID(hDlg, FID_SYSMENU);
   WinSendMsg( hSysMenu, MM_QUERYITEM ,
      MPFROM2SHORT(SC_SYSMENU, FALSE), MPFROMP((PCH) & Mi));
   Pos = 0L;
   cItems = (SHORT)WinSendMsg( Mi.hwndSubMenu, MM_QUERYITEMCOUNT,
				(MPARAM)NULL, (MPARAM)NULL);
   while (cItems--) {
      Id = WinSendMsg( Mi.hwndSubMenu, MM_ITEMIDFROMPOSITION ,
         MPFROMLONG(Pos), (MPARAM)NULL);
      switch (SHORT1FROMMR(Id)) {
         case SC_MOVE:
         case SC_CLOSE: Pos++;  /* Don't delete that one. */ break;
         default:
            WinSendMsg( Mi.hwndSubMenu, MM_DELETEITEM ,
               MPFROM2SHORT((USHORT)Id, TRUE), (MPARAM)NULL);}}
}   /*	End of SetSysMenu  */
/**************************************************************************
 *
 *  Name       : DlgProc(hwndDlg, msg, mp1, mp2 )
 *
 *  Description: ��楤�� ����������� ���� ����� �����
 *
 *  Concepts:  ���� �� Service. ���頥��� � ����������� ����
 *	       � ���� �� ���� ��� ������ ����. �᫨ ��� �� ����,
 *	       �ॡ�� ���, ���� �� �����.
 *
 *  API's      :  WinDismissDlg
 *		  WinDefDlgProc
 *
 *  Parameters :  hwndDlg	   = dialog window handle
 *		  msg	   = message i.d.
 *		  mp1	   = first message parameter
 *		  mp2	   = second message parameter
 *
 *  Return     :  dependent on message sent
 *
 *************************************************************************/
MRESULT EXPENTRY DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
   switch ( msg ) {
      case WM_COMMAND:
         WinQueryWindowText(
            WinWindowFromID( hwndDlg, EF_ENTRYNAME ),
            256,szName );//�����頥� ⥪��
         if(szName[0] != '\0') WinDismissDlg( hwndDlg, TRUE );
         return (MRESULT) FALSE;

      default: return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );}
   return (MRESULT) FALSE;
}   /* End of DlgProc */
/**************************************************************************
 *
 *  Name       : HScoresDlgProc(hwndDlg, msg, mp1, mp2 )
 *
 *  Description: ��楤�� ����������� ���� High Scores
 *
 *  Concepts: ���頥��� � ����������� ���� � �ᯮ�����
 *  � List Box'� ����� � �窨 祬������.
 *
 *  API's      :  WinDismissDlg
 *		  WinDefDlgProc
 *
 *  Parameters :  hwndDlg	   = dialog window handle
 *		  msg	   = message i.d.
 *		  mp1	   = first message parameter
 *		  mp2	   = second message parameter
 *
 *  Return     :  dependent on message sent
 *
 *************************************************************************/
MRESULT EXPENTRY HScoresDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 )
{  int i;
   char szMsg[7];

   switch ( msg ) {
      case WM_INITDLG:
         for(i=0;i<10;i++) {
            WinSendMsg( WinWindowFromID( hwndDlg, LB_NAMES ),
               LM_INSERTITEM, (MPARAM)LIT_END , pszHNames[i] );
            sprintf(szMsg,"%d",pHScores[i]);
            WinSendMsg( WinWindowFromID( hwndDlg, LB_SCORES ),
               LM_INSERTITEM, (MPARAM)LIT_END , szMsg ); } break;

      case WM_COMMAND:
         WinDismissDlg( hwndDlg, TRUE );
         return (MRESULT) FALSE;

      default: return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );}
   return (MRESULT) FALSE;
}   /* End of HScoresDlgProc */
/**************************************************************************
 *
 *  Name       : SettingsDlgProc(hwndDlg, msg, mp1, mp2 )
 *
 *  Description: ��楤�� ����������� ���� ����஥� ����
 *
 *  Concepts: ���樠������� ᮮ⢥�����騥 �࣠�� �ࠢ�����
 *      � ����ᨬ��� �� ���ﭨ� ����஥� �� ������ ����᪠
 *      �������, � ����� �� ����ன�� � ����ᨬ��� ��
 *      ���ﭨ� �࣠��� �ࠢ����� �� ������ ��室� ��
 *      ������� (ࠧ㬥����, �᫨ ������ OK)
 *
 *  API's      :  WinDismissDlg
 *		  WinDefDlgProc
 *
 *  Parameters :  hwndDlg	   = dialog window handle
 *		  msg	   = message i.d.
 *		  mp1	   = first message parameter
 *		  mp2	   = second message parameter
 *
 *  Return     :  dependent on message sent
 *
 *************************************************************************/
MRESULT EXPENTRY SettingsDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 )
{  char szMsg[7];
   //RECTL rec,totalrec;
   RECTL totalrec;
   POINTL ptl;
   HPS hps;
   int i;

   totalrec.xLeft  = 245; totalrec.yBottom = 146;
   totalrec.xRight = 402; totalrec.yTop    = 310;

   switch ( msg ) {

      case WM_INITDLG://�.�. ���樠������
         f = CLR_FIELD; c = CLR_CHANNEL; n = CLR_NEW;
         br= CLR_BREAK; r = CLR_RUNNER;  h = CLR_HUNTERS;
         ba= CLR_BALLS; s = CLR_STRING;  ch= CLR_CHAR;
         st = bStyle; so = bSound; ha = bHalt;
         bs = BmpSize ; co = Col ; ro = Row;
         WinSendMsg(hwndDlg ,WM_MYINIT,NULL,NULL);break;

      case WM_MYINIT://�.�. ���樠������
         /*��⠭���� ⥪�� � ����� �����*/
         WinSendMsg(WinWindowFromID(hwndDlg, EF_BMPSIZE ),
            EM_SETTEXTLIMIT,(MPARAM)2,(MPARAM)0);
         WinSendMsg(WinWindowFromID(hwndDlg, EF_COL ),
            EM_SETTEXTLIMIT,(MPARAM)2,(MPARAM)0);
         WinSendMsg(WinWindowFromID(hwndDlg, EF_ROW ),
            EM_SETTEXTLIMIT,(MPARAM)2,(MPARAM)0);
         sprintf(szMsg,"%d",bs);
         WinSetWindowText(WinWindowFromID(hwndDlg, EF_BMPSIZE),szMsg);
         sprintf(szMsg,"%d",co);
         WinSetWindowText(WinWindowFromID(hwndDlg, EF_COL),szMsg);
         sprintf(szMsg,"%d",ro);
         WinSetWindowText(WinWindowFromID(hwndDlg, EF_ROW),szMsg);
         /*�⠢�� ����窨 � ������ OTHER*/
         if(so)
            WinSendMsg(WinWindowFromID(hwndDlg, CB_SOUND ),
                  BM_SETCHECK,MPFROMSHORT(1),NULL);
         if(ha)
            WinSendMsg(WinWindowFromID(hwndDlg, CB_HALT ),
                  BM_SETCHECK,MPFROMSHORT(1),NULL);
         /*�⠢�� ��� � ������ Style*/
         if(st)
            WinSendMsg(WinWindowFromID(hwndDlg, RB_3D ),
                  BM_SETCHECK,MPFROMSHORT(1),NULL);
         else WinSendMsg(WinWindowFromID(hwndDlg, RB_2D ),
                  BM_SETCHECK,MPFROMSHORT(1),NULL);
         /*�⠢�� ��� � ������ Colors(�� ������)*/
         WinSendMsg(WinWindowFromID(hwndDlg, RB_RUNNER ),
            BM_SETCHECK,MPFROMSHORT(1),NULL); p = &r;
         /*����ᮢ뢠��*/
         WinInvalidateRect(hwndDlg,&totalrec,TRUE);
         break;

      case WM_PAINT:{
         int j,k;//j-�ਭ�,k-����(⨯�)
         RECTL rec;
         //��砫�
         if(bs<=0)bs=BmpSize;
         /*����� �.�. �ᮢ���� ᠬ���ᮢ*/
         //᪮�쪮 ������� 楫�� ���⮪:
         k = (totalrec.yTop-LineHeight-totalrec.yBottom)/bs;
         k *= bs;
         k = totalrec.yTop-LineHeight-k;
         //��稭��� �ᮢ���
         hps = WinBeginPaint(hwndDlg,NULLHANDLE,&rec);
         //sprintf(szMsg,"%dx%d",rec.xLeft,rec.yBottom);
         //WinMessageBox(HWND_DESKTOP,HWND_DESKTOP,
         //   szMsg,"Move",0,MB_OK);
         if(!bDraw) {//���ᮢ뢠�� ��
            WinFillRect(hps, &rec, CLR_DARKGRAY);//ࠬ��
            rec.xLeft  = 1; rec.yBottom = 1;
            rec.xRight = 435; rec.yTop    = 367;
            WinFillRect(hps, &rec, CLR_PALEGRAY);//��� 䮭
            rec.yBottom = k;
            rec.yTop    = 310-LineHeight;
            j = (402-245)/bs; j *= bs;
            rec.xRight = j+245; rec.xLeft  = 245;
            WinFillRect(hps, &rec, CLR_WHITE);}//�����-����
         if( !bDraw || p == &f ) //����
            for(i=310-LineHeight-2*bs;i>=k;i-=bs)
               for(j=245+bs;j<402-bs;j+=bs)DlgQuatro(&hps,i,j,f);
         if( !bDraw || p == &c ) {//��ਤ���
            for(i=310-LineHeight-bs;i>=k;i-=bs) DlgQuatro(&hps,i,245,c);
            for(j=245;j<405-bs;j+=bs) DlgQuatro(&hps,310-LineHeight-bs,j,c);}
         if( !bDraw || p == &n || p == &f ) //���� ��ਤ���
            for(i=310-LineHeight-2*bs;i>k+2*bs;i-=bs) DlgQuatro(&hps,i,245+10*bs,n);
         if( !bDraw || p == &br || p == &f ) //��������� ��ਤ���
            for(j=245+bs;j<245+10*bs;j+=bs) DlgQuatro(&hps,k+3*bs,j,br);
         if( !bDraw || p == &r || p == &f || p == &n ) //���㭮�
            DglKpyr(&hps, k+3*bs, 245+10*bs, r);
         if( !bDraw || p == &ba || p == &f || p == &n ) //ࠧ����訩 �ਪ
            DglKpyr(&hps, k+3*bs, 245+5*bs, ba);
         if( !bDraw || p == &ba || p == &f ) //�ਪ
            DglKpyr(&hps, 310-LineHeight-5*bs, 245+12*bs, ba);
         if( !bDraw || p == &h || p == &c ) {//��⭨��
            DglKpyr(&hps, 310-LineHeight-5*bs, 245, h);
            DglKpyr(&hps, 310-LineHeight-bs, 245+7*bs, h);}
         if( !bDraw || p == &s ) {//CTPOKA
            rec.xLeft  = 245; rec.yBottom = 310-LineHeight;
            rec.yTop = 310;
            i = (402-245)/bs; i *= bs; rec.xRight = i+245;
            WinFillRect(hps, &rec, s);}
         if( !bDraw || p == &ch || p == &s ) {//�㪢�
            GpiSetColor(hps,ch); ptl.x = 255; ptl.y = 310-LineHeight+5;
            GpiCharStringAt(hps,&ptl,6,"Time-0");}
         bDraw = 0;
         WinEndPaint(hps);
         return 0;}


      case WM_CONTROL://�ࠢ�����
         switch( SHORT1FROMMP( mp1 ) ) {

            case RB_2D: st = 0;
               WinSendMsg(hwndDlg ,WM_MYINIT,NULL,NULL); break;
            case RB_3D: st = 1;
               WinSendMsg(hwndDlg ,WM_MYINIT,NULL,NULL); break;
            case CB_SOUND: so  = !so; break;
            case CB_HALT : ha  = !ha; break;
            case RB_RUNNER    : p = &r ; break;
            case RB_HUNTERS   : p = &h ; break;
            case RB_BALLS     : p = &ba; break;
            case RB_FIELD     : p = &f ; break;
            case RB_WAYS      : p = &c ; break;
            case RB_NEWWAYS   : p = &n ; break;
            case RB_BREAKWAYS : p = &br; break;
            case RB_TEXTBACK  : p = &s ; break;
            case RB_TEXTFORE  : p = &ch; break;

            case EF_BMPSIZE :
               if((USHORT)SHORT2FROMMP(mp1) == EN_KILLFOCUS ){
                  WinQueryWindowText(//��塞 䮪��
                     WinWindowFromID( hwndDlg, EF_BMPSIZE ),
                     sizeof(szMsg),szMsg );//�����頥� ⥪��
                  sscanf(szMsg,"%d",&i);
                  if( i>5 && i<13 && bs != i) {
                     bs = i;
                     WinInvalidateRect(hwndDlg,&totalrec,TRUE);}
                  else if( bs != i) {
                     MessageBox(hwndMain, IDMSG_BETWEENBMP,
                          (PSZ)NULL, MB_OK | MB_ERROR, FALSE);
                     sprintf(szMsg,"%d",bs);
                     WinSetWindowText(WinWindowFromID(hwndDlg,
                        EF_BMPSIZE),szMsg); }}

               else if((USHORT)SHORT2FROMMP(mp1) == EN_CHANGE ){
                  WinQueryWindowText(//��������� ⥪��
                     WinWindowFromID( hwndDlg, EF_BMPSIZE ),
                     sizeof(szMsg),szMsg );//�����頥� ⥪��
                  sscanf(szMsg,"%d",&i);
                  if( i>5 && i<13 ) {
                     bs = i; iNoOK = 0;//㩤��
                     WinInvalidateRect(hwndDlg,&totalrec,TRUE);}
                  else iNoOK = EF_BMPSIZE;/*�� 㩤��*/ }break;

            case EF_COL :
               if((USHORT)SHORT2FROMMP(mp1) == EN_KILLFOCUS ){
                  int i;
                  WinQueryWindowText(
                     WinWindowFromID( hwndDlg, EF_COL ),
                     sizeof(szMsg),szMsg );//�����頥� ⥪��
                  sscanf(szMsg,"%d",&i);
                  if( i>49 && i<101 ) { co = i; iNoOK = 0; }
                  else { iNoOK = EF_COL ;
                     MessageBox(hwndMain, IDMSG_BETWEENCOL,
                          (PSZ)NULL, MB_OK | MB_ERROR, FALSE);
                     sprintf(szMsg,"%d",co);
                     WinSetWindowText(WinWindowFromID(hwndDlg,
                        EF_COL),szMsg);}} break;

            case EF_ROW :
               if((USHORT)SHORT2FROMMP(mp1) == EN_KILLFOCUS ){
                  int i;
                  WinQueryWindowText(
                     WinWindowFromID( hwndDlg, EF_ROW ),
                     sizeof(szMsg),szMsg );//�����頥� ⥪��
                  sscanf(szMsg,"%d",&i);
                  if( i>29 && i<61 ) { ro = i;  iNoOK = 0; }
                  else { iNoOK = EF_ROW ;
                     MessageBox(hwndMain, IDMSG_BETWEENROW,
                          (PSZ)NULL, MB_OK | MB_ERROR, FALSE);
                     sprintf(szMsg,"%d",ro);
                     WinSetWindowText(WinWindowFromID(hwndDlg,
                        EF_ROW),szMsg);}} break;

            default: break; }

      case WM_COMMAND://������
         switch( SHORT1FROMMP( mp1 ) ) {
            //梥�
            case PB_BLUE  : ColorCorrect(CLR_BLUE);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);
               break;
            case PB_CYAN  : ColorCorrect(CLR_CYAN);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);break;
            case PB_GRAY  : ColorCorrect(CLR_PALEGRAY);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);break;
            case PB_GREEN : ColorCorrect(CLR_GREEN);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);break;
            case PB_PINK  : ColorCorrect(CLR_PINK);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);break;
            case PB_RED   : ColorCorrect(CLR_RED);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);break;
            case PB_YELLOW: ColorCorrect(CLR_YELLOW);
               bDraw = 1;
               WinInvalidateRect(hwndDlg,&totalrec,TRUE);break;
            //������ �ࠢ����� OK,Cancel,Default
            case PB_DEFAULT://�᫨ ������ Default
               bs = 10; co = 60; ro = 40;
               f  = CLR_PALEGRAY; c  = CLR_BLUE; n  = CLR_GREEN;
               br   = CLR_RED   ; r  = CLR_DARKCYAN; h  = CLR_RED;
               ba = CLR_BLUE    ; s  = CLR_DARKBLUE; ch = CLR_WHITE;
               st = 1; so = 1; ha = 1;
               bDraw = 1;
               WinSendMsg(hwndDlg ,WM_MYINIT,NULL,NULL);break;

            case DID_OK://�᫨ ������ OK
               if (iNoOK) {iNoOK = 0; return (MRESULT) FALSE;}
               if(f == c || f == n  || f == br ||
                  c == n || c == br || n == br ){
                  MessageBox(hwndMain, IDMSG_MUSTDIFFERENT,
                     (PSZ)NULL, MB_OK | MB_ERROR, FALSE);
                  f  = CLR_PALEGRAY; c  = CLR_BLUE; n  = CLR_GREEN;
                  br   = CLR_RED   ; r  = CLR_DARKCYAN; h  = CLR_RED;
                  ba = CLR_BLUE    ; s  = CLR_DARKBLUE; ch = CLR_WHITE;
                  bDraw = 1;
                  WinInvalidateRect(hwndDlg,&totalrec,TRUE);
                  return (MRESULT) FALSE; }
               if(CLR_FIELD  != f  || CLR_CHANNEL != c  ||
                  CLR_NEW    != n  || CLR_BREAK   != br ||
                  CLR_RUNNER != r  || CLR_HUNTERS != h  ||
                  CLR_BALLS  != ba || CLR_STRING  != s  ||
                  CLR_CHAR   != ch || bStyle      != st   ) {
                  bChange = 1;
                  Replace(CLR_FIELD  ,f+100 ,NULL);
                  Replace(CLR_CHANNEL,c+100 ,NULL);
                  Replace(CLR_BREAK  ,br+100,NULL);
                  Replace(CLR_NEW    ,n+100 ,NULL);
                  CLR_FIELD = f ; CLR_CHANNEL = c;
                  CLR_NEW     = n;
                  CLR_BREAK = br; CLR_RUNNER  = r;
                  CLR_HUNTERS = h;
                  CLR_BALLS = ba; CLR_STRING  = s;
                  CLR_CHAR    = ch;
                  Replace(f+100, CLR_FIELD  ,NULL);
                  Replace(c+100, CLR_CHANNEL, NULL);
                  Replace(br+100, CLR_BREAK ,NULL);
                  Replace(n+100 , CLR_NEW , NULL ); }
               MainY += BmpSize*Row - bs*ro;
               if( Col != co || Row != ro ){//�஢�ઠ ࠧ��஢
                  bChange = 1; Col = co ; Row = ro ;
                  i = sScore; InitNewGame(0);
                  sScore = i; sOScore = i;}
               if(BmpSize != bs) { bChange = 1; BmpSize = bs ; }
               bStyle = st; bSound = so; bHalt = ha;
               /* ��������� ࠧ��஢ �������� ���� */
               if(bChange) {
                  WinSetWindowPos( hwndMainFrame, HWND_TOP,
                     MainX,MainY,
                     BmpSize*Col+2,BmpSize*Row+40+LineHeight,
                     SWP_SIZE | SWP_MOVE );
                  WinInvalidateRect(hwndMain,NULL,FALSE); }

            case DID_CANCEL://�᫨ ������ �⬥��
               WinDismissDlg( hwndDlg, TRUE );
               return (MRESULT) FALSE;

            default: break; } break;

      default: return WinDefDlgProc( hwndDlg, msg, mp1, mp2 );}
   return (MRESULT) FALSE;
}   /* End of SettingsDlgProc */
/***************************  End of dlg.c  ****************************/

