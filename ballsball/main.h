/**************************************************************************
 *  File name  :  main.h
 *
 *  Description:  This header file contains the application wide
 *		  constants and structure definitions.
 *
 *  Concepts   :  [none]
 *
 *  API's      :  [none]
 *
 *  Required
 *    Files    :  [none]
 *************************************************************************/
#define MAXLEVEL                       11
/* resource identifier */
#define IDR_MAIN                       1
//идентификаторы таймеров
#define IDT_MOVE                       2000
#define IDT_GAME                       2001
/* Standard Dialog box ids */
#define FILEOPEN                       2000
#define FILESAVE	                     2001

#define MSGBOXID	                     1001
#define OBJECTID	                     1002
/* Popup Menu ID */
#define POPUP_MENU                     999
/*мое сообщение*/
#define WM_MYINIT                      700
/* Menu item ids */
#define IDM_FILE			               1000
#define IDM_FILENEW			            1100
#define IDM_FILEOPEN			            1200
#define IDM_FILESAVE			            1300
#define IDM_FILESAVEAS                 1400
#define IDM_DIRECTION_START            1500
#define IDM_HIGHSCORES                 1600
#define IDM_FILEEXIT                   1700

#define IDM_SETTINGS                   2000
#define IDM_SOUND                      2100
#define IDM_SOUND_ON                   2101
#define IDM_SOUND_OFF                  2102
#define IDM_STYLE  			            2200
#define IDM_STYLE_2D			            2201
#define IDM_STYLE_3D			            2202
#define IDM_LEVEL   			            2300
#define IDM_LEVEL_0                    2301
#define IDM_LEVEL_1                    2302
#define IDM_LEVEL_2                    2303
#define IDM_LEVEL_3                    2304
#define IDM_LEVEL_4                    2305
#define IDM_LEVEL_5                    2306
#define IDM_LEVEL_6                    2307
#define IDM_LEVEL_7                    2308
#define IDM_LEVEL_8                    2309
#define IDM_LEVEL_9                    2310
#define IDM_LEVEL_10                   2311
#define IDM_LEVEL_11                   2312
#define IDM_SETTINGS_ALL               2400

#define IDM_HELP			               9000
#define IDM_HELPUSINGHELP		         9100
#define IDM_HELPGENERAL			         9200
#define IDM_HELPKEYS			            9300
#define IDM_HELPINDEX			         9400
#define IDM_HELPPRODUCTINFO		      9600
/* Dialog item ids */
#define ID_OK		                     1
#define ID_CANCEL	                     2
/* Stringtable ids */
#define IDS_FILEOPENEXT	               1
#define IDS_APPNAME                    2
#define IDS_HELPLIBRARYNAME	         3
#define IDS_OPEN		                  4
#define IDS_HELPWINDOWTITLE	         5
#define IDS_SAVE		                  6
#define IDS_UNTITLED		               7
#define IDS_TITLEBARSEPARATOR	         8
#define IDS_OBJECTCLASS		            9
/* Messagetable ids */
#define IDMSG_INITFAILED	            1
#define IDMSG_MAINWINCREATEFAILED      2
#define IDMSG_CANNOTOPENINPUTFILE      3
#define IDMSG_CANNOTRUNSETTINGS        8
#define IDMSG_CANNOTGETHPS		         9
#define IDMSG_HELPLOADERROR	         10
#define IDMSG_CANNOTLOADSTRING	      11
#define IDMSG_CONGRATULATIONS  	      12
#define IDMSG_OK                       13
#define IDMSG_SORRY                    14
#define IDMSG_SAVE                     15
#define IDMSG_HELPDISPLAYERROR	      16
#define IDMSG_CANNOTLOADEXITLIST       17
#define IDMSG_OVERWRITEFILE	         18
#define IDMSG_CANNOTGETFILEINFO	      19
#define IDMSG_CANNOTALLOCATEMEMORY     20
#define IDMSG_CANNOTREADFILE	         21
#define IDMSG_CANNOTWRITETOFILE	      22
#define IDMSG_CANNOTLOADSETTINGS       23
#define IDMSG_CANNOTLOADHSCORES        24
#define IDMSG_CANNOTWRITESETTINGS      25
#define IDMSG_BETWEENBMP               26
#define IDMSG_BETWEENCOL               27
#define IDMSG_BETWEENROW               28
#define IDMSG_MUSTDIFFERENT            29
#define IDMSG_YOURTUTORIAL	            74
/* Ids of messages used between threads */
#define TM_THREADINITFAILED            WM_USER+300
/* Other constants */
#define MESSAGELEN          120/* maximum length for messages */
#define TITLESEPARATORLEN   4
/* return values for initialization routines */
#define RETURN_SUCCESS	    0	/* successful return in DosExit */
#define RETURN_ERROR	       1 /* error return in DosExit */
#define BEEP_WARN_FREQ	    60/* frequency of warning beep */
#define BEEP_WARN_DUR	    100/* duration of warning beep */
/***************************  End of main.h  *****************/

