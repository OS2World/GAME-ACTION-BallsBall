# OpenWatcom makefile for BallsBall (bb.exe)
#
# Tools: wcc386 (compile), wlink (link), wrc (resources)
# Output goes to bin-wat/
#
# Build on the OS/2 VM:
#   compile.cmd                (or: wmake -f makefile.wat)
#   wmake -f makefile.wat help (optional: compile BBHELP.HLP, needs ipfc)
#
# The original 2002 makefiles hardcoded f:\ballsball paths and are left
# untouched under src/ (bb.mk1, bb.tgt, ballsball.mk).  This makefile has
# no hardcoded paths.
#
# The ring of cells is 80 x 50 by default; init.c (InitPrf) now scales
# BmpSize up so the game window reaches at least 1024 x 768 when the
# desktop allows it (the window is never made larger than the desktop).

SRC = src
BIN = bin-wat

HEADERS = $(SRC)\game.h $(SRC)\main.h $(SRC)\dlg.h $(SRC)\help.h $(SRC)\xtrn.h

all : $(BIN)\bb.exe

$(BIN)\bb.exe : $(BIN)\dlg.obj $(BIN)\file.obj $(BIN)\help.obj $(BIN)\init.obj $(BIN)\main.obj $(BIN)\menu.obj $(BIN)\move.obj $(BIN)\pnt.obj $(BIN)\main.res
	cd $(BIN) && wlink system os2v2_pm debug all name bb op q op map op maxe=25 file { dlg.obj file.obj help.obj init.obj main.obj menu.obj move.obj pnt.obj }
	wrc -q $(BIN)\main.res $(BIN)\bb.exe

$(BIN)\dlg.obj : $(SRC)\dlg.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\dlg.c

$(BIN)\file.obj : $(SRC)\file.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\file.c

$(BIN)\help.obj : $(SRC)\help.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\help.c

$(BIN)\init.obj : $(SRC)\init.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\init.c

$(BIN)\main.obj : $(SRC)\main.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\main.c

$(BIN)\menu.obj : $(SRC)\menu.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\menu.c

$(BIN)\move.obj : $(SRC)\move.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\move.c

$(BIN)\pnt.obj : $(SRC)\pnt.c $(HEADERS)
	cd $(BIN) && wcc386 -bt=os2 -i=..\$(SRC) -w4 -e25 -zq -od -d2 -5r -mf ..\$(SRC)\pnt.c

$(BIN)\main.res : $(SRC)\main.rc $(SRC)\main.h $(SRC)\dlg.h $(SRC)\dialogs.dlg $(SRC)\dialogs.nl.dlg $(SRC)\dialogs.es.dlg $(SRC)\dialogs.de.dlg $(SRC)\dialogs.fr.dlg $(SRC)\lang_nl.rc $(SRC)\lang_es.rc $(SRC)\lang_de.rc $(SRC)\lang_fr.rc $(SRC)\help.rc $(SRC)\bbicon.ico help\prodinfo.bmp
	cd $(SRC) && wrc -r -i=..\help -fo=..\$(BIN)\main.res main.rc

help : $(BIN)\bbhelp.hlp

$(BIN)\bbhelp.hlp : help\bbhelp.ipf help\file.ipf help\settings.ipf help\help.ipf help\myhelp.ipf help\prodinfo.bmp help\mous.bmp help\moustemp.bmp
	-if exist help\bbhelp.hlp del help\bbhelp.hlp
	cd help && ipfc bbhelp.ipf /w3
	if exist help\bbhelp.hlp copy help\bbhelp.hlp $(BIN) /y

clean :
	-del /q $(BIN)\bb.exe $(BIN)\*.obj $(BIN)\main.res $(BIN)\bbhelp.hlp $(BIN)\bb.map $(BIN)\bb.sym 2>nul
	@if exist $(BIN) rmdir $(BIN)