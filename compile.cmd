@echo off
set LOGFILE=compile-wat.log
echo Build started: %DATE% %TIME% > %LOGFILE%
if "%WATCOM%"=="" (
    if exist C:\WATCOM\binp\wcc386.exe set WATCOM=C:\WATCOM
    if exist D:\WATCOM\binp\wcc386.exe set WATCOM=D:\WATCOM
)
if "%WATCOM%"=="" (
    echo ERROR: Open Watcom not found. Set WATCOM environment variable. >> %LOGFILE%
    echo ERROR: Open Watcom not found. Set WATCOM environment variable.
    exit /b 1
)
if "%OS2TK%"=="" set OS2TK=C:\OS2TK45
set PATH=%WATCOM%\binp;%WATCOM%\binw;%PATH%
set BEGINLIBPATH=%WATCOM%\binp\dll
set INCLUDE=%WATCOM%\h;%WATCOM%\h\os2;%OS2TK%\h;%INCLUDE%
set LIB=%WATCOM%\lib386;%WATCOM%\lib386\os2;%OS2TK%\lib;%LIB%
echo Using WATCOM=%WATCOM% >> %LOGFILE%
wmake -f makefile.wat clean >> %LOGFILE% 2>&1
if not exist bin md bin
wmake -f makefile.wat all >> %LOGFILE% 2>&1
if errorlevel 1 goto :failed
if not exist bin\bb.exe goto :failed
echo Build OK >> %LOGFILE%
echo Build OK
goto :end
:failed
echo BUILD FAILED - see %LOGFILE%
type %LOGFILE%
exit /b 1
:end
REM Optional: compile the help pages (needs the IBM/ArcaOS ipfc.exe):
REM   wmake -f makefile.wat help
