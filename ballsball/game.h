/**************************************************************************
 *  File name  :  game.h
 *
 *  Description:  ��� ��������� ᮤ�ন� ��।������ ���
 *		  ����.
 *
 *  Concepts   :  game
 *************************************************************************/

extern long *(*Field);  //�� ����
/*梥�*/
extern long CLR_FIELD;  //����誮-����
extern long CLR_CHANNEL; //��ਤ��
extern long CLR_NEW;    //�������� �� ��ਤ��
extern long CLR_BREAK;  //㡨�� ��������
extern long CLR_RUNNER; //���㭮�
extern long CLR_HUNTERS;//��⭨��
extern long CLR_BALLS;  //��稪�
extern long CLR_STRING; //䮭 ��� �㪢
extern long CLR_CHAR;   //梥� �㪢
/*�㦭� ���窨*/
extern BOOL bStart;//����� �����
extern BOOL bGame;//���� ���
extern BOOL bNew; //����塞 ����
extern BOOL bStyle;//2d ��� 3d
extern BOOL bSound;//���
extern BOOL bHalt;//��⠭���� ��᫥ �ਡ����
extern BOOL bChange;//���������� ����ன�� ����
extern USHORT usLevel;//�஢���
extern int iScore;//�窨
extern int iOScore;//�窨 � ��諮� ����
extern int iBScore;//�窨 � ��砫� ����
extern int iHScore;//������ � ����⪥
extern USHORT usTime;//�६� �� ��砫� ����
/*������ �ਪ*/
extern RECTL Runner;//����騩
extern POINTL Memory;//��᫥���� ������ � ��ਤ��
/*��।�*/
extern RECTL *Hunters;//��⭨��(� ��ਤ���)
extern RECTL *Balls;//���(� ����)
/*ࠧ����*/
extern int QSize;//ࠧ��� ��।��
extern int BmpSize;//ࠧ��� ���⨭��
extern int Col;//������⢮ �⮫�楢
extern int Row;//������⢮ ��ப
/***************************  End of game.h  ****************************/

