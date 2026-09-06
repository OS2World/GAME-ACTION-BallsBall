/**************************************************************************
 *  File name  :  xtrn.h
 *
 *  Description:  This header file contains the application-wide function
 *		  declarations and global external variables.
 *
 *  Concepts   :  global definition
 *
 *  API's      :  [none]
 *
 *  Required
 *    Files    :  [none]
 *************************************************************************/
/*��� ��।������*/
#define MAX(AA,BB) ((AA)>(BB)?(AA):(BB))
#define MIN(AAA,BBB) ((AAA)<(BBB)?(AAA):(BBB))
/* Global variables */
extern HWND hwndMainFrame;
extern HWND hwndMain;
extern HWND hwndMenu;
extern HWND hwndPopupMenu;
extern HAB hab;
extern HMQ hmq;
extern HDC hdcMain;
extern CHAR szAppName[];
extern CHAR szUntitled[];
extern BOOL fHelpEnabled;
extern POINTL TimeEndptl;//����� ������ '�६�'
extern POINTL LevelBeginptl;//��砫� ������ '�஢���'
extern POINTL LevelEndptl;//����� ������ '�஢���'
extern POINTL ScoreEndptl;//����� ������ '�窨'
//���न���� ����
extern long MainX;
extern long MainY;
extern CHAR szIniFile[];
extern char  *szName;//��� ������ 祬�����
extern SHORT *pHScores;//���ᨢ �窮� 祬������
extern char *(pszHNames[10]);//���ᨢ 祬������
/* �㡫��� ��� ����஥� */
extern long r,h,ba,c,f,br,n,s,ch,*p;
extern BOOL st,so,ha;
extern int bs,co,ro;

extern BOOL bDraw;//�ᮢ���� ������� ����஥�
extern int LineHeight;//ࠧ��� ⥪�⮢�� ��ப�
extern int iLang;//������ ��� (0=EN,1=NL,2=ES,3=DE,4=FR)
extern int iLangBase;//������ �듬���� ��� ������ resource id'�
/* Entry point declarations */

/* from main.c */
int main(VOID);
MRESULT EXPENTRY MainWndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
ULONG MessageBox(HWND hwndOwner, ULONG idMsg, PSZ szTitle, ULONG fsStyle, BOOL fBeep);
VOID MainCommand(HWND hwnd, MPARAM mp1, MPARAM mp2);
VOID MainChar(HWND hwnd, MPARAM mp1, MPARAM mp2);
VOID MainTimer(HWND hwnd, ULONG ulTIMER);
/* from init.c */
BOOL Init(VOID);
VOID ExitProc();
BOOL InitPrf();
VOID InitNewGame(BOOL bOld);
BOOL NotUnique(int iNum, PRECTL ppQueue);
VOID ClosePrf();
VOID HScoresPrf(BOOL bChange);
VOID InitLevel(USHORT usl);
BOOL InitFont( HDC hdc);
VOID FreeField(VOID);
VOID SetLanguage(int lang);
PSZ LangText(ULONG id, ULONG max, PSZ pszBuf);
/* from file.c */
VOID FileOpen(MPARAM mp2);
VOID FileSave(MPARAM mp2);
VOID FileSaveAs(MPARAM mp2);
BOOL GetFileName(VOID);
VOID UpdateTitleText(HWND hwnd, BOOL bNew);
MRESULT EXPENTRY FAR TemplateOpenFilterProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY FAR TemplateSaveFilterProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
/* from menu.c */
VOID InitMenu(MPARAM mp1, MPARAM mp2);
VOID EnableMenuItem(HWND hwndMenu, USHORT idItem, BOOL fEnable);
VOID MenuRedraw(int iMenu);
VOID ApplyLanguage(VOID);
/* from move.c */
VOID MoveRunner();
VOID MoveHunter(int iNum);
BOOL MoveBall(int iNum);
VOID Replace(long lOld, long lNew, PHPS phps);
/* from pnt.c */
VOID MainPaint(HWND hwnd);
VOID Quatro(HPS* phps,int i, int j);
VOID Kpyr(HPS* phps,int i, int j, long lColor);
VOID CTPOKA(HPS* phps, USHORT usAll);
VOID DlgQuatro(PHPS phps,int i, int j, LONG lColor);
VOID DglKpyr(PHPS phps,int i, int j, long lColor);
VOID ColorCorrect(long lColor);
/* from help.c */
VOID InitHelp(VOID);
VOID HelpIndex(VOID);
VOID HelpGeneral(VOID);
VOID HelpUsingHelp(VOID);
VOID HelpKeys(VOID);
//VOID HelpProductInfo(VOID);
VOID DisplayHelpPanel(ULONG idPanel);
VOID DestroyHelpInstance(VOID);
/* from dlg.c */
MRESULT EXPENTRY ProductInfoDlgProc(HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
VOID SetSysMenu( HWND hDlg );
MRESULT EXPENTRY DlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY HScoresDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 );
MRESULT EXPENTRY SettingsDlgProc( HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2 );
/***************************  End of xtrn.h  ****************************/

