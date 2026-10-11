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
//�����䨪���� ⠩��஢
#define IDT_MOVE                       2000
#define IDT_GAME                       2001
/* Standard Dialog box ids */
#define FILEOPEN                       2000
#define FILESAVE	                     2001

#define MSGBOXID	                     1001
#define OBJECTID	                     1002
/* Popup Menu ID */
#define POPUP_MENU                     999
/*��� ᮮ�饭��*/
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
#define IDM_STYLE_TOGGLE               2203
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
#define IDM_LANGUAGE                   2500
#define IDM_LANGUAGE_EN                2501
#define IDM_LANGUAGE_NL                2502
#define IDM_LANGUAGE_ES                2503
#define IDM_LANGUAGE_DE                2504
#define IDM_LANGUAGE_FR                2505
#define IDM_LANGUAGE_IT                2506
#define IDM_BACKGRND                   2600
#define IDM_FRAME_CTRL                 2700
#define IDM_SAVEONEXIT                 2800
#define IDM_KEYMAPPING                 2900

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
/* Menu text ids (loaded at runtime for the selected language) */
#define IDS_MEN_FILE                   20
#define IDS_MEN_NEW                    21
#define IDS_MEN_LOAD                   22
#define IDS_MEN_SAVE                   23
#define IDS_MEN_SAVEAS                 24
#define IDS_MEN_START                  25
#define IDS_MEN_HSCORES                26
#define IDS_MEN_EXIT                   27
#define IDS_MEN_SETTINGS               28
#define IDS_MEN_SOUND                  29
#define IDS_MEN_SOUNDON                30
#define IDS_MEN_SOUNDOFF               31
#define IDS_MEN_STYLE                  32
#define IDS_MEN_STYLE2D                33
#define IDS_MEN_STYLE3D                34
#define IDS_MEN_LEVEL                  35
#define IDS_MEN_LANGUAGE               36
#define IDS_MEN_LANG_EN                37
#define IDS_MEN_LANG_NL                38
#define IDS_MEN_LANG_ES                39
#define IDS_MEN_SETTINGS_ALL           40
#define IDS_MEN_HELP                   41
#define IDS_MEN_HELPGENERAL            42
#define IDS_MEN_HELPINDEX              43
#define IDS_MEN_HELPUSING              44
#define IDS_MEN_HELPKEYS               45
#define IDS_MEN_HELPPROD               46
#define IDS_MEN_LANG_DE                47
#define IDS_MEN_LANG_FR                48
#define IDS_MEN_LANG_IT                49
/* Painted status line and misc strings */
#define IDS_FMT_TIME                   50
#define IDS_FMT_LEVEL                  51
#define IDS_FMT_SCORE                  52
#define IDS_PREV_TIME                  53
#define IDS_NONAME                     54
#define IDS_WINNER                     55
#define IDS_TITLE_WARNING              56
#define IDS_MEN_BACKGRND               57
#define IDS_MEN_FRAME                  58
#define IDS_MEN_SAVEONEXIT             59
/* Key Mapping menu text and dialog texts */
#define IDS_MEN_KEYMAPPING              60
#define IDS_KM_TITLE                    61
#define IDS_KM_TAB_KBD                  62
#define IDS_KM_TAB_JOY                  63
#define IDS_KM_A_LEFT                   64
#define IDS_KM_A_RIGHT                  65
#define IDS_KM_A_UP                     66
#define IDS_KM_A_DOWN                   67
#define IDS_KM_A_START                  68
#define IDS_KM_A_STOP                   69
#define IDS_KM_KBD_H1                   70
#define IDS_KM_KBD_H2                   71
#define IDS_KM_JOY_H1                   72
#define IDS_KM_JOY_H2                   73
#define IDS_KM_JOY_EN                   74
#define IDS_KM_JOY_A                    75
#define IDS_KM_JOY_B                    76
#define IDS_KM_CAL_A                    77
#define IDS_KM_CAL_B                    78
#define IDS_KM_OK                       79
#define IDS_KM_CANCEL                   80
#define IDS_KM_CAL_MSG                  81
#define IDS_KM_CAL_TITLE                82
#define IDS_KM_NONE                     83
#define IDS_KM_AXL                      84
#define IDS_KM_AXR                      85
#define IDS_KM_AXU                      86
#define IDS_KM_AXD                      87
#define IDS_KM_BTN                      88
/* Language resource namespaces (single exe, shifted resource ids) */
#define LANG_BASE_EN                   0
#define LANG_BASE_NL                   10000
#define LANG_BASE_ES                   20000
#define LANG_BASE_DE                   30000
#define LANG_BASE_FR                   40000
#define LANG_BASE_IT                   50000
#define LANG_EN                        0
#define LANG_NL                        1
#define LANG_ES                        2
#define LANG_DE                        3
#define LANG_FR                        4
#define LANG_IT                        5
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

