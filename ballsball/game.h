/**************************************************************************
 *  File name  :  game.h
 *
 *  Description:  Этот заголовок содержит определения для
 *		  игры.
 *
 *  Concepts   :  game
 *************************************************************************/

extern long *(*Field);  //все поле
/*цвета*/
extern long CLR_FIELD;  //полюшко-поле
extern long CLR_CHANNEL; //коридор
extern long CLR_NEW;    //кандидат на коридор
extern long CLR_BREAK;  //убили кандидата
extern long CLR_RUNNER; //бегунок
extern long CLR_HUNTERS;//охотники
extern long CLR_BALLS;  //мячики
extern long CLR_STRING; //фон для букв
extern long CLR_CHAR;   //цвет букв
/*нужные штучки*/
extern BOOL bStart;//можно играть
extern BOOL bGame;//идет игра
extern BOOL bNew; //проторяем путь
extern BOOL bStyle;//2d или 3d
extern BOOL bSound;//звук
extern BOOL bHalt;//остановка после прибавки
extern BOOL bChange;//изменились настройки поля
extern USHORT usLevel;//уровень
extern int iScore;//очки
extern int iOScore;//очки с прошлой игры
extern int iBScore;//очки с начала игры
extern int iHScore;//минимум в десятке
extern USHORT usTime;//время от начала игры
/*главный шарик*/
extern RECTL Runner;//играющий
extern POINTL Memory;//последняя позиция в коридоре
/*очереди*/
extern RECTL *Hunters;//охотники(в коридорах)
extern RECTL *Balls;//мячи(в поле)
/*размеры*/
extern int QSize;//размер очередей
extern int BmpSize;//размер картинки
extern int Col;//количество столбцев
extern int Row;//количество строк
/***************************  End of game.h  ****************************/

