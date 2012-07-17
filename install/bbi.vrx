/*:VRX         Main
*/
/*  Main
*/
Main:
/*  Process the arguments.
    Get the parent window.
*/
    parse source . calledAs .
    parent = ""
    argCount = arg()
    argOff = 0
    if( calledAs \= "COMMAND" )then do
        if argCount >= 1 then do
            parent = arg(1)
            argCount = argCount - 1
            argOff = 1
        end
    end
    InitArgs.0 = argCount
    if( argCount > 0 )then do i = 1 to argCount
        InitArgs.i = arg( i + argOff )
    end
    drop calledAs argCount argOff

/*  Load the windows
*/
    call VRInit
    parse source . . spec
    _VREPrimaryWindowPath = ,
        VRParseFileName( spec, "dpn" ) || ".VRW"
    _VREPrimaryWindow = ,
        VRLoad( parent, _VREPrimaryWindowPath )
    drop parent spec
    if( _VREPrimaryWindow == "" )then do
        call VRMessage "", "Cannot load window:" VRError(), ,
            "Error!"
        _VREReturnValue = 32000
        signal _VRELeaveMain
    end

/*  Process events
*/
    call Init
    signal on halt
    do while( \ VRGet( _VREPrimaryWindow, "Shutdown" ) )
        _VREEvent = VREvent()
        interpret _VREEvent
    end
_VREHalt:
    _VREReturnValue = Fini()
    call VRDestroy _VREPrimaryWindow
_VRELeaveMain:
    call VRFini
exit _VREReturnValue

VRLoadSecondary: procedure
    name = arg( 1 )

    window = VRLoad( VRWindow(), VRWindowPath(), name )
    call VRMethod window, "CenterWindow"
    call VRSet window, "Visible", 1
    call VRMethod window, "Activate"
return window

/*:VRX         EF_1_KeyPress
*/
EF_1_KeyPress:
ks = VRGet( "EF_1", "KeyString" )
if ks = '{Newline}' then Call PB_1_Click
if ks = '{Esc}' then Call PB_2_Click

return

/*:VRX         Fini
*/
Fini:
    window = VRWindow()
    call VRSet window, "Visible", 0
    drop window
return 0

/*:VRX         Halt
*/
Halt:
    signal _VREHalt
return

/*:VRX         Init
*/
Init:
    window = VRWindow()
    call VRMethod window, "CenterWindow"
    call VRSet window, "Visible", 1
    call VRMethod window, "Activate"
    drop window
return

/*:VRX         PB_1_Click
*/
PB_1_Click:
call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs
buttons.0 = 1
buttons.1 = "OK"
/*чикаем нужные для инсталляции файлы*/
c=1
BBPATH = DIRECTORY()
BBEXE = BBPATH || '\bb.exe'
if VRFileExists( BBEXE )=0 then 
   do
   c=c+1
   message.c = BBEXE
   end
BBHLP = BBPATH || '\bbhelp.hlp'
if VRFileExists( BBHLP )=0 then 
   do
   c=c+1
   message.c = BBHLP
   end
BBL = BBPATH || '\LICENSE.TXT'
if VRFileExists( BBL )=0 then 
   do
   c=c+1
   message.c = BBL
   end
BBR = BBPATH || '\README.TXT'
if VRFileExists( BBR )=0 then 
   do
   c=c+1
   message.c = BBR
   end
set = VRGet( "CB_1", "Set" )
if set = 1 then
   do
   BBF = BBPATH || '\BBFOLDER.ICO'
   if VRFileExists( BBF )=0 then 
      do
      c=c+1
      message.c = BBF
      end
   BBFO = BBPATH || '\BBFOPEN.ICO'
   if VRFileExists( BBFO )=0 then
      do
      c=c+1
      message.c = BBFO
      end
   end
/*если что-то не нашли - ошибка*/
if c>1 then
   do
   c=c+1
   message.0 = c
   message.1 = 'Program cannot find follow files:'
   message.c = 'Check up thise files in package.'
   id = VRMessageStem( VRWindow(), 'message.', 'Error', 'Error', 'buttons.', 1, 1 )   
   return
   end
/*куда пишем*/
INDIR = VRGet( "EF_1", "Value" )
if INDIR = '' then 
   do
   INDIR = BBPATH
   c=0
   end
else
   do 
   c=1  
   if VRIsDir( INDIR )=0 then 
      if VRMkDir( INDIR )=0 then
         do
         id = VRMessage( VRWindow(), "Invalid directory", "Error", "Error", , ,  )
         return
         end   
   end
/*если надо копировать*/
if c = 1 then
   do
   c = 0;
   BBEXEC = INDIR || '\bb.exe'
   ok = VRCopyFile( BBEXE, BBEXEC )
   c = c + ok
   BBHLPC = INDIR || '\bbhelp.hlp'
   ok = VRCopyFile( BBHLP, BBHLPC )
   c = c + ok
   BBLC = INDIR || '\LICENSE.TXT'
   ok = VRCopyFile( BBL, BBLC )
   c = c + ok
   BBRC = INDIR || '\README.TXT'
   ok = VRCopyFile( BBR, BBRC )   
   c = c + ok
   end
if c < 4 then
   do
   id = VRMessage( VRWindow(), "Program cannot write files to disk", "Error", "Error", , ,  )
   ALLBBC = INDIR || '\*.*'
   ok = VRDeleteFile( ALLBBC )
   ok = VRRmDir( INDIR )
   return
   end
/*создание папки на десктопе*/
if set = 1 then
   do
   Call SysCreateObject 'WPFolder', 'BallsBall Game','<WP_DESKTOP>','ICONFILE='|| BBPATH ||'\BBFOLDER.ICO;ICONNFILE=1,'|| BBPATH ||'\BBFOPEN.ICO;OBJECTID=<WP_BBF_FOLD>','R'
   Call SysCreateObject 'WPProgram','BallsBall','<WP_BBF_FOLD>','EXENAME='||INDIR||'\BB.EXE','R'
   Call SysCreateObject 'WPShadow','Read me','<WP_BBF_FOLD>','SHADOWID='|| INDIR ||'\'readme.txt'','R'
   Call SysCreateObject 'WPShadow','License','<WP_BBF_FOLD>','SHADOWID='|| INDIR ||'\'license.txt'','R'
   end
id = VRMessage( VRWindow(), "Installation is successfully completed.", "Install", "None", , ,  )
call Quit
return

/*:VRX         PB_2_Click
*/
PB_2_Click:
    window = VRWindow()
    call VRSet window, "Shutdown", 1
    drop window
return

/*:VRX         Quit
*/
Quit:
    window = VRWindow()
    call VRSet window, "Shutdown", 1
    drop window
return

/*:VRX         Window1_Close
*/
Window1_Close:
    call Quit
return

/*:VRX         Window1_Create
*/
Window1_Create:
return

/*:VRX         Window1_KeyPress
*/
Window1_KeyPress:
ks = VRGet( "Window1", "KeyString" )
if ks = '{Newline}' then Call PB_1_Click
if ks = '{Esc}' then Call PB_2_Click
return

