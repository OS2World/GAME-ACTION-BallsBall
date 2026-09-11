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
#define   INCL_DOSMODULEMGR

#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "dlg.h"
#include "game.h"
#include "xtrn.h"

/* Global variables */
long *(*Field);  //�� ����
long CLR_FIELD;  //����誮-����
long CLR_CHANNEL; //��ਤ��
long CLR_NEW;    //�������� �� ��ਤ��
long CLR_BREAK;  //㡨�� ��������
long CLR_RUNNER; //���㭮�
long CLR_HUNTERS;//��⭨��
long CLR_BALLS;  //��稪�
long CLR_STRING; //䮭 ��� �㪢
long CLR_CHAR;   //梥� �㪢
BOOL bNew; //����塞 ����
BOOL bGame;//���� ���
BOOL bStyle;//2d ��� 3d
BOOL bSound;//���
BOOL bHalt;//��⠭���� ��᫥ �ਡ����
USHORT usLevel;//�஢���
int iScore;//�窨
int iOScore;//�窨 � ��諮� ����
int iHScore;//������ � ����⪥
int iBScore;//�窨 � ��砫� ����
USHORT usTime;//�६� �� ��砫� ����

RECTL Runner;//����騩
POINTL Memory;//��᫥���� ������ � ��ਤ��
//��।�
RECTL *Hunters;//��⭨��(� ��ਤ���)
RECTL *Balls;//���(� ����)
//ࠧ����
int QSize;//ࠧ��� ��।��
int BmpSize;//ࠧ��� ���⨭��
int Col;//������⢮ �⮫�楢
int Row;//������⢮ ��ப
int LineHeight;//ࠧ��� ⥪�⮢�� ��ப�
//���न���� ����
long MainX;
long MainY;
//����
int iLang = LANG_EN;//������ ��� (0=EN,1=NL,2=ES,3=DE,4=FR)
int iLangBase = LANG_BASE_EN;//������ �듬���� ��� ������ resource id'�
CHAR szIniFile[CCHMAXPATH];//���� �� ��⮬ bb.ini ��� ��o� �糫���䨮��

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
{  HINI hinii;//��� �� �듬����
   ULONG cb    = sizeof(szIniFile); // size of the profile path buffer
   PSZ   pSlash;                    // last backslash in the exe path

   if(DosExitList(EXLST_ADD, (PFNEXITLIST)ExitProc)) {
      MessageBox(HWND_DESKTOP, IDMSG_CANNOTLOADEXITLIST,
		    (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
      DosExit(EXIT_PROCESS, RETURN_ERROR); }
   /* anchor bb.ini next to the executable so the working directory
      does not matter when the game is started */
   if(DosQueryModuleName((HMODULE)NULL, cb, szIniFile) ||
      (pSlash = strrchr(szIniFile, '\\')) == NULL)
      strncpy(szIniFile, "bb.ini", cb - 1);
   else
   {  *(pSlash+1) = '\0';
      strncat(szIniFile, "bb.ini", cb - strlen(szIniFile) - 1); }
   /* read the preferred language from bb.ini before strings load */
   iLang = LANG_EN;
   if((hinii = PrfOpenProfile(hab,szIniFile))){
      iLang = (int)PrfQueryProfileInt(hinii,"Settings","Language",LANG_EN);
      PrfCloseProfile(hinii);}
   if(iLang != LANG_NL && iLang != LANG_ES && iLang != LANG_DE && iLang != LANG_FR && iLang != LANG_IT)
      iLang = LANG_EN;
   switch(iLang) {
      case LANG_NL: iLangBase = LANG_BASE_NL; break;
      case LANG_ES: iLangBase = LANG_BASE_ES; break;
      case LANG_DE: iLangBase = LANG_BASE_DE; break;
      case LANG_FR: iLangBase = LANG_BASE_FR; break;
      case LANG_IT: iLangBase = LANG_BASE_IT; break;
      default:      iLangBase = LANG_BASE_EN; break; }
   /* load application name from resource file */
   if(0 == WinLoadString(hab, (HMODULE)0, iLangBase+IDS_APPNAME, MAXNAMEL, szAppName))
      return FALSE;
   /* load "untitled" string */
   if(!WinLoadString(hab, (HMODULE)0, iLangBase+IDS_UNTITLED, MESSAGELEN, szUntitled))
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
 *  Name       : LangText(id, max, pszBuf)
 *
 *  Description:  Loads the language-dependent string with the given
 *		  id from the current language's STRINGTABLE.  The id
 *		  is shifted by iLangBase, the number is a plain base
 *		  id from main.h/dlg.h.
 *
 *  Return     :  pszBuf, or NULL if pszBuf was NULL.
 *************************************************************************/
PSZ LangText(ULONG id, ULONG max, PSZ pszBuf)
{  if(pszBuf == NULL) return (PSZ)NULL;
   if(!WinLoadString(hab, (HMODULE)0, iLangBase+id, max, pszBuf))
      pszBuf[0] = '\0';
   return pszBuf;
}   /* End of LangText   */
/**************************************************************************
 *  Name       : SetLanguage(lang)
 *
 *  Description:  Selects the language for all subsequently loaded
 *		  resources and remembers the choice in bb.ini.
 *************************************************************************/
VOID SetLanguage(int lang)
{  HINI hinis;
   CHAR szL[4];

   if(lang == LANG_NL || lang == LANG_ES || lang == LANG_DE || lang == LANG_FR || lang == LANG_IT)
      iLang = lang;
   else iLang = LANG_EN;
   switch(iLang) {
      case LANG_NL: iLangBase = LANG_BASE_NL; break;
      case LANG_ES: iLangBase = LANG_BASE_ES; break;
      case LANG_DE: iLangBase = LANG_BASE_DE; break;
      case LANG_FR: iLangBase = LANG_BASE_FR; break;
      case LANG_IT: iLangBase = LANG_BASE_IT; break;
      default:      iLangBase = LANG_BASE_EN; break; }
   if((hinis = PrfOpenProfile(hab,szIniFile))){
      sprintf(szL,"%d",iLang);
      PrfWriteProfileString(hinis,"Settings","Language",szL);
      PrfCloseProfile(hinis);}
}   /* End of SetLanguage   */
/**************************************************************************
 *  Name       : FreeField()
 *
 *  Description: Frees the playing field, including every row.
 *
 *  Concepts:	  Field is a pointer array whose elements are per-row
 *		  allocations, so both the rows and the array itself must
 *		  be released.  Field is left as NULL.
 *************************************************************************/
VOID FreeField(VOID)
{  int i;

   if(Field == NULL) return;
   for(i=Row;i>0;i--) free(Field[i-1]);
   free(Field);
   Field = NULL;
}   /* End of FreeField */
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
   //����ࠥ� ������ � ��।��
   FreeField();
   free(Hunters);
   free(Balls);
}   /* End of ExitProc	  */
/**************************************************************************
 *  Name       : ScaleWinToDesktop(SWP *pswp)
 *
 *  Description: Scales the game window so that it is at least
 *		  1024 x 768 pixels when the desktop resolution allows it.
 *		  The cell size (BmpSize) is only ever increased and the
 *		  window is never made larger than the desktop.  Cells
 *		  stay square.
 *
 *  Parameters : pswp = current size of the desktop
 *************************************************************************/
static void ScaleWinToDesktop(SWP *pswp)
{  int needW, needH, fitW, fitH, need, fit;

   /* in case a broken bb.ini supplied unusable Col/Row, wait for the
      defaults path to fix them before dividing */
   if(Col < 1 || Row < 1) return;

   /* BmpSize needed for a window of at least 1024 x 768:
         window width  = BmpSize*Col + 2
         window height = BmpSize*Row + 40 + LineHeight (LineHeight ~16) */
   needW = (1024 - 2 + Col - 1) / Col;
   needH = (768 - 56 + Row - 1) / Row;
   need  = (needW > needH) ? needW : needH;

   /* largest square cell size the desktop can show */
   fitW = (pswp->cx - 4) / Col;
   fitH = (pswp->cy - 56) / Row;
   fit  = (fitW < fitH) ? fitW : fitH;

   if(fit > need) fit = need;       /* never larger than the desktop */
   if(fit > BmpSize) BmpSize = fit; /* only scale the window up     */
}   /* End of ScaleWinToDesktop */

/**************************************************************************
 *  Name       : InitPrf();
 *
 *  Description: ���樠������� ����ன�� ����
 *
 *  Concepts:	 ���� ������ �ᨫ��� ��ᢠ����� 梥� �
 *		 ��稥 ����ன��.� ���饬 �㤥� �௠�� �� �� ini-䠩��.
 *     ���, 㦥 �௠��.
 *************************************************************************/
BOOL InitPrf()
{  HINI hini;//ini file handle
   SWP swpDESKTOP;//����砫�� ���न��� � ࠧ��஢ DESKTOPa

   WinQueryWindowPos(HWND_DESKTOP,&swpDESKTOP);
   bGame   = 0;//��� �� ��砫���
   bNew    = 0; //���� �� ����塞
   usLevel = 0;//�㫥��� �஢���
   iScore  = 0;//�窨
   usTime  = 180;//��� �� ��砫���
   if((hini = PrfOpenProfile(hab,szIniFile))){
      BmpSize = PrfQueryProfileInt(hini,"Bitmaps","Size",10);
      Col     = PrfQueryProfileInt(hini,"Bitmaps","Columns",60);
      Row     = PrfQueryProfileInt(hini,"Bitmaps","Rows",40);
      MainX = PrfQueryProfileInt(hini,"Place","MainX",100);
      MainY = PrfQueryProfileInt(hini,"Place","MainY",100);
      ScaleWinToDesktop(&swpDESKTOP);
      MainY = MIN(swpDESKTOP.cy-(BmpSize*Row+40+20),MainY);
      CLR_FIELD   = PrfQueryProfileInt(hini,"Colors","Color of free field",CLR_PALEGRAY);//����誮-����
      CLR_CHANNEL = PrfQueryProfileInt(hini,"Colors","Color of channels",CLR_BLUE);//��ਤ��
      CLR_NEW     = PrfQueryProfileInt(hini,"Colors","Color of new channels",CLR_GREEN);//�������� �� ��ਤ��
      CLR_BREAK   = PrfQueryProfileInt(hini,"Colors","Color of break channels",CLR_RED);//㡨�� ��������
      CLR_RUNNER  = PrfQueryProfileInt(hini,"Colors","Color of runner",CLR_DARKCYAN);//���㭮�
      CLR_HUNTERS = PrfQueryProfileInt(hini,"Colors","Color of hunters",CLR_RED);//��⭨��
      CLR_BALLS   = PrfQueryProfileInt(hini,"Colors","Color of balls",CLR_BLUE);//��稪�
      CLR_STRING  = PrfQueryProfileInt(hini,"Colors","Color of background",CLR_DARKBLUE);//䮭 ��� �㪢
      CLR_CHAR    = PrfQueryProfileInt(hini,"Colors","Color of chars",CLR_WHITE);//梥� �㪢
      bStyle = PrfQueryProfileInt(hini,"Settings","Style(2D/3D)",1);//3d
      bSound = PrfQueryProfileInt(hini,"Settings","Sound",1);//��� ����祭
      bHalt  = PrfQueryProfileInt(hini,"Settings","Halt",1);//��⠭����������
      iHScore = PrfQueryProfileInt(hini,"High Scores","10",0);/*������ � ����⪥*/
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
          Col < 101 && Col > 49 && Row < 61 && Row > 29 ) {
          /* same core sizes as ScaleWinToDesktop: 1024 x 768 window */
          int needW = (1022 + Col - 1) / Col;   /* BmpSize for 1024 px width  */
          int needH = (712 + Row - 1) / Row;    /* BmpSize for 768 px height  */
          int need  = (needW > needH) ? needW : needH;
          if(BmpSize > 5 && BmpSize <= need) return 1; }
    }   /* End of if(hini = PrfOpenProfile(hab,szIniFile))  */
    BmpSize = 8;
   Col = 80; Row = 50;
   MainX = 100; MainY = 100;
   ScaleWinToDesktop(&swpDESKTOP);
   MainY = MIN(swpDESKTOP.cy-(BmpSize*Row+40+20),MainY);
   CLR_FIELD   = CLR_PALEGRAY;  //����誮-����
   CLR_CHANNEL  = CLR_BLUE;    //��ਤ��
   CLR_NEW     = CLR_GREEN;   //�������� �� ��ਤ��
   CLR_BREAK   = CLR_RED;     //㡨�� ��������
   CLR_RUNNER  = CLR_DARKCYAN;//���㭮�
   CLR_HUNTERS = CLR_RED;    //��⭨��
   CLR_BALLS   = CLR_BLUE;     //��稪�
   CLR_STRING  = CLR_DARKBLUE; //䮭 ��� �㪢
   CLR_CHAR    = CLR_WHITE;   //梥� �㪢
   bStyle  = 1;//3d
   bSound  = 1;//��� ����祭
   bHalt   = 1;//��⠭����������
   iHScore = 0;/*������ � ����⪥*/ return 0;
   }   /* End of InitPrf	  */
/**************************************************************************
 *  Name       : InitNewGame()
 *
 *  Description: ���樠�������(��頥�) ���� ��� ����� ���� �
 *		 ����ࠨ���� ��।� �ਪ��.
 *
 *
 *  Parameters : bOld = �� ᮢ��襭�� ����� ��� ��� ����
 *     ���室 �� ��㣮� �஢���
 *************************************************************************/
VOID InitNewGame(BOOL bOld)
{  int i,j;
   float fRandom;

   LevelBeginptl.x = Col*BmpSize;//��砫� �� �����⭮
   bGame = 0;//��⠭��������
   bStart = 1;//����� �����
   usTime  = 180;//��� �� ��砫���
   if(bOld) iScore += usLevel*10;//�窨
   else     iScore = 0;
   iOScore = iScore;
   bNew    = 0; //���� �� ����塞
   //������塞 ��஢�� ����
   FreeField();
   Field = malloc(Row*sizeof(*Field));
   for(i=0;i<Row;i++) Field[i] = malloc(Col*sizeof(CLR_FIELD));
   //����
   for(i=1;i<Row-1;i++)
      for(j=1;j<Col-1;j++)Field[i][j] = CLR_FIELD;
   //���⨪���� �����
   for(i=0;i<Row;i++)Field[i][0]     = CLR_CHANNEL;
   for(i=0;i<Row;i++)Field[i][Col-1] = CLR_CHANNEL;
   //��ਧ��⠫�� �����
   for(j=0;j<Col;j++)Field[0][j]     = CLR_CHANNEL;
   for(j=0;j<Col;j++)Field[Row-1][j] = CLR_CHANNEL;
   //������
   Runner.xLeft   = Col/2;
   Runner.yBottom = Row-1;
   Runner.xRight  = 0;
   Runner.yTop    = 0;
   //��� ���� � ��ਤ��
   Memory.x = Col/2;
   Memory.y = Row-1;
   //ࠧ��� ��।��
   QSize = 4+usLevel;
   //��।�
   free(Hunters);//����ࠥ� ������
   free(Balls);//����ࠥ� ������
   Hunters=malloc(sizeof(Runner)*QSize);//�뤥����� �����
   Balls=malloc(sizeof(Runner)*QSize);//�뤥����� �����
   for(i=0;i<QSize;i++) {
      do {//஧���� ���न��� ��� ��⭨���
         fRandom=rand()*(Col+2*Row-3)/RAND_MAX;
         j = fRandom;j=j/2*2;
         if(j<Row-2) {//���� �⮫���
            Hunters[i].xLeft   = 0;//���न����
            Hunters[i].yBottom = j+1;
            Hunters[i].xRight  = 0;//���ࠢ����� ��������
            if(i == i/2*2) Hunters[i].yTop = -1; //��⨢ ��
            else           Hunters[i].yTop =  1;}//�� ��
         else if(j<Col+Row-2) {//��ࢠ� ��ப�
            Hunters[i].xLeft   = j-Row+3;//���न����
            Hunters[i].yBottom = 0;
            Hunters[i].yTop    = 0;//���ࠢ����� ��������
            if(i == i/2*2) Hunters[i].xRight =  1; //��⨢ ��
            else           Hunters[i].xRight = -1;}//�� ��
         else {//��᫥���� �⮫���
            Hunters[i].xLeft   = Col-1;//���न����
            Hunters[i].yBottom = Col+2*Row-4-j;
            Hunters[i].xRight  = 0;//���ࠢ����� ��������
            if(i == i/2*2) Hunters[i].yTop =  1; //��⨢ ��
            else           Hunters[i].yTop = -1;}//�� ��
      } while( NotUnique(i, Hunters) );
      do {//஧���� ���न��� ��� �ਪ��
         fRandom=rand()*((Col-2)*(Row-2)-1)/RAND_MAX;
         Balls[i].yBottom = fRandom/(Col-2)+1;
         Balls[i].xLeft   = fRandom-(Balls[i].yBottom-1)*(Col-2)+1;
         } while( NotUnique(i, Balls) );
      switch(i-i/4*4) {//������ ���ࠢ�����
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
 *  Description: �஢���� ������� ��।� ��⭨���
 *		  ��� �ਪ�� �� �।��� ᮢ������� ���न���.
 *
 *  Parameters : ppQueue = ���樠�����㥬�� ��।�
 *      iNum = ���樠�����㥬� �������
 *
 *  Return    :	  �����頥� ���� �᫨ ������� 㭨�����
 *      � ������,�᫨ ������� � ⠪��� ���न��⠬� 㦥 ����
 *************************************************************************/
BOOL NotUnique(int iNum, PRECTL ppQueue)
{  int i;

   for(i=0;i<iNum;i++)//�� ᮢ������ � �।��騬�
      if(ppQueue[iNum].xLeft   == ppQueue[i].xLeft   &&
         ppQueue[iNum].yBottom == ppQueue[i].yBottom)return 1;
   if(ppQueue == Balls)/*�ਪ� �� ����� ��� ����*/{
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
 *  Description: ���� ����ன�� ���� � ini-䠩�.
 *
 *  Concepts:	  ���� � ����, ��� ��直� ��� ���楯権.
 *************************************************************************/
VOID ClosePrf()
{  HINI hini;//ini file handle
   char szMsg[100];
   SWP swpMain;//����砫�� ���न��� � ࠧ��஢ ����

   if((hini = PrfOpenProfile(hab,szIniFile))){
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
      sprintf(szMsg,"%d",iLang);
      PrfWriteProfileString(hini,"Settings","Language",szMsg);
      //����뢠�� .ini 䠩�
      PrfCloseProfile(hini);}
   else {CHAR szW[40];
      MessageBox(HWND_DESKTOP, IDMSG_CANNOTWRITESETTINGS,
           LangText(IDS_TITLE_WARNING, 40, szW), MB_OK | MB_ERROR, TRUE);}
}   /* End of ClosePrf */
/**************************************************************************
 *  Name       : HScoresPrf(BOOL bChange)
 *
 *  Description: ���� HighScores � ini-䠩�.
 *
 *  Concepts:	  ����訢��� ��� ��ப� � ���� ��
 *      � ini-䠩�.
 *************************************************************************/
VOID HScoresPrf(BOOL bChange)
{  HINI hini;//ini file handle
   char szMsg[256];
   char szHNames[10][256];
   int  i;
   SHORT sBuff,aHScores[10];
   char szNewScore[15];

   if((hini = PrfOpenProfile(hab,szIniFile))) {
      for(i=0;i<10;i++) {//�⠥� ᯨ᮪ 祬������
         sprintf(szMsg,"%d",i+1);
         aHScores[i] = PrfQueryProfileInt(hini,"High Scores",szMsg,0);
         sprintf(szMsg,"Name%d",i+1);
LangText(IDS_NONAME, 256, szHNames[i]);
          PrfQueryProfileString(hini,"High Scores",szMsg,
             szHNames[i],szHNames[i],256);
         pszHNames[i] = szHNames[i]; }
      pHScores = aHScores;
      if(bChange){//��⠢�� ������ 祬�����
         szName = szHNames[9]; aHScores[9] = iScore;
         /*������ ��� �����*/
WinDlgBox( HWND_DESKTOP, /*��� ��㥬*/
             hwndMainFrame,/*��������*/
             DlgProc,      /*���������� ��楤��*/
             (HMODULE)0,	  /*㪠��⥫� �����*/
             iLangBase+DLG_ENTERNAME,/*㪠��⥫� ������� � .rc*/
            NULL);		  /*�� ��� � �㤠 ���*/
         if(bChange == 2){CHAR szW[24];
             strcat(szName, LangText(IDS_WINNER, 24, szW));} i=0;
         //㯮�冷稢����
         for(i=9;i>0 && aHScores[i-1] < aHScores[i];i--) {
            strcpy(szMsg,szHNames[i]);//����� �������
            strcpy(szHNames[i],szHNames[i-1]);
            strcpy(szHNames[i-1],szMsg);
            sBuff = aHScores[i-1];//����� �窠��
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
         /*������ ������ HScore'ᮢ*/
WinDlgBox( HWND_DESKTOP,	/*��� ��㥬*/
             hwndMainFrame,  /*��������*/
             HScoresDlgProc, /*���������� ��楤��*/
             (HMODULE)0,	    /*㪠��⥫� �����*/
             iLangBase+DLG_HIGHSCORES, /*㪠��⥫� ������� � .rc*/
         NULL);		    /*�� ��� � �㤠 ���*/
         PrfCloseProfile(hini);}
   else MessageBox(HWND_DESKTOP, IDMSG_CANNOTLOADHSCORES,
          (PSZ)NULL, MB_OK | MB_ERROR, TRUE);
}   /* End of HScoresPrf */
/**************************************************************************
 *  Name       : InitLevel()
 *
 *  Description: ���樠������� ���� �஢���
 *
 *  Parameters : usl = �� ����� �஥�� ���室��
 *************************************************************************/
VOID InitLevel(USHORT usl)
{
   if(bGame){//�᫨ ���� ���
      WinStopTimer(hab,hwndMain,IDT_MOVE);
      WinStopTimer(hab,hwndMain,IDT_GAME);}
   usLevel = usl; InitNewGame(0);
   WinInvalidateRect(hwndMain,NULL,FALSE);
}   /* End of InitLevel */
/**************************************************************************
 *  Name       : InitFont();
 *
 *  Description: ������ ���� ����ன�� ����
 *
 *  Concepts:	 ���� �⠢�� ࠧ��� ��ப� � 楫�� ��� ���쭥�襣�
 *		 �ᯮ�짮����� � ����⪨ ࠧ��� ࠧ��஢ ��ப�.
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

