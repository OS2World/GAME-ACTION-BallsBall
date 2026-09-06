@echo off
set EMXOMFLD_TYPE=WLINK
set EMXOMFLD_LINKER=wl.exe
set EMXOMFLD_PRELINK=0
make -f makefile.wat clean
REM compile.cmd - build BallsBall (bb.exe) with Open Watcom.
REM Run from this directory on OS/2.  Output goes to bin-wat\.
REM If the WATCOM environment variable points at the Open Watcom
REM installation it is used for the C include path; otherwise the
REM compilers fall back to the headers next to their own location.
if "%WATCOM%"=="" goto skipinc
set INCLUDE=%WATCOM%\h;%WATCOM%\h\os2
:skipinc
if not exist bin-wat md bin-wat
wmake -f makefile.wat 2>&1 | tee make_wat.out

REM Optional: compile the help pages (needs the IBM/ArcaOS ipfc.exe):
REM   wmake -f makefile.wat help