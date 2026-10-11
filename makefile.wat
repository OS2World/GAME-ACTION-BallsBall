# OpenWatcom makefile for BallsBall (bb.exe)
#
# Tools: wcc386 (compile), wlink (link), wrc (resources)
# Output goes to bin/
#
# Build on the OS/2 VM:
#   compile.cmd                (or: wmake -f makefile.wat)
#   wmake -f makefile.wat help (compile bin\help\bbhelp_xx.hlp from help\bbhelp_xx.ipf, needs wipfc)
#
# The original 2002 makefiles hardcoded f:\ballsball paths and are left
# untouched under src/ (bb.mk1, bb.tgt, ballsball.mk).  This makefile has
# no hardcoded paths.
#
# The ring of cells is 80 x 50 by default; init.c (InitPrf) now scales
# BmpSize up so the game window reaches at least 1024 x 768 when the
# desktop allows it (the window is never made larger than the desktop).

SRC = src
BIN = bin

!ifndef WATCOM
WATCOM = C:\WATCOM
!endif
!ifndef WIPFC
WIPFC = $(WATCOM)\wipfc
!endif

HELPS = $(BIN)\help\bbhelp_en.hlp $(BIN)\help\bbhelp_nl.hlp $(BIN)\help\bbhelp_es.hlp $(BIN)\help\bbhelp_de.hlp $(BIN)\help\bbhelp_fr.hlp $(BIN)\help\bbhelp_it.hlp

CFLAGS = -bt=os2 -5r -mf -Oaxt -d0 -zq -w4 -e25 -i=$(SRC)

HEADERS = $(SRC)\game.h $(SRC)\main.h $(SRC)\dlg.h $(SRC)\help.h $(SRC)\xtrn.h $(SRC)\keymap.h $(SRC)\joyos2.h

all : $(BIN)\bb.exe $(HELPS)

$(BIN)\bb.exe : $(BIN)\dlg.obj $(BIN)\file.obj $(BIN)\help.obj $(BIN)\init.obj $(BIN)\keymap.obj $(BIN)\main.obj $(BIN)\menu.obj $(BIN)\move.obj $(BIN)\pnt.obj $(BIN)\main.res
	wlink system os2v2_pm name $(BIN)\bb op q op map op maxe=25 op stack=65536 op heap=4096 file $(BIN)\dlg.obj, $(BIN)\file.obj, $(BIN)\help.obj, $(BIN)\init.obj, $(BIN)\keymap.obj, $(BIN)\main.obj, $(BIN)\menu.obj, $(BIN)\move.obj, $(BIN)\pnt.obj
	wrc -q $(BIN)\main.res $(BIN)\bb.exe

$(BIN)\dlg.obj : $(SRC)\dlg.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\dlg.obj $(SRC)\dlg.c

$(BIN)\file.obj : $(SRC)\file.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\file.obj $(SRC)\file.c

$(BIN)\help.obj : $(SRC)\help.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\help.obj $(SRC)\help.c

$(BIN)\init.obj : $(SRC)\init.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\init.obj $(SRC)\init.c

$(BIN)\keymap.obj : $(SRC)\keymap.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\keymap.obj $(SRC)\keymap.c

$(BIN)\main.obj : $(SRC)\main.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\main.obj $(SRC)\main.c

$(BIN)\menu.obj : $(SRC)\menu.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\menu.obj $(SRC)\menu.c

$(BIN)\move.obj : $(SRC)\move.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\move.obj $(SRC)\move.c

$(BIN)\pnt.obj : $(SRC)\pnt.c $(HEADERS)
	wcc386 $(CFLAGS) -fo=$(BIN)\pnt.obj $(SRC)\pnt.c

$(BIN)\main.res : $(SRC)\main.rc $(SRC)\main.h $(SRC)\dlg.h $(SRC)\dialogs.dlg $(SRC)\keymap.dlg $(SRC)\dialogs.nl.dlg $(SRC)\dialogs.es.dlg $(SRC)\dialogs.de.dlg $(SRC)\dialogs.fr.dlg $(SRC)\dialogs.it.dlg $(SRC)\lang_nl.rc $(SRC)\lang_es.rc $(SRC)\lang_de.rc $(SRC)\lang_fr.rc $(SRC)\lang_it.rc $(SRC)\help.rc $(SRC)\bbicon.ico
	wrc -r -i=$(SRC) -i=help -fo=$(BIN)\main.res $(SRC)\main.rc

help : $(HELPS) .SYMBOLIC

$(BIN)\help\bbhelp_en.hlp : help\bbhelp_en.ipf help\mous.bmp
	@if not exist $(BIN)\help mkdir $(BIN)\help
	@set WIPFC=$(WIPFC)
	cd help && wipfc -l en_US -o ..\$(BIN)\help\bbhelp_en.hlp bbhelp_en.ipf

$(BIN)\help\bbhelp_nl.hlp : help\bbhelp_nl.ipf help\mous.bmp
	@if not exist $(BIN)\help mkdir $(BIN)\help
	@set WIPFC=$(WIPFC)
	cd help && wipfc -l en_US -o ..\$(BIN)\help\bbhelp_nl.hlp bbhelp_nl.ipf

$(BIN)\help\bbhelp_es.hlp : help\bbhelp_es.ipf help\mous.bmp
	@if not exist $(BIN)\help mkdir $(BIN)\help
	@set WIPFC=$(WIPFC)
	cd help && wipfc -l en_US -o ..\$(BIN)\help\bbhelp_es.hlp bbhelp_es.ipf

$(BIN)\help\bbhelp_de.hlp : help\bbhelp_de.ipf help\mous.bmp
	@if not exist $(BIN)\help mkdir $(BIN)\help
	@set WIPFC=$(WIPFC)
	cd help && wipfc -l en_US -o ..\$(BIN)\help\bbhelp_de.hlp bbhelp_de.ipf

$(BIN)\help\bbhelp_fr.hlp : help\bbhelp_fr.ipf help\mous.bmp
	@if not exist $(BIN)\help mkdir $(BIN)\help
	@set WIPFC=$(WIPFC)
	cd help && wipfc -l en_US -o ..\$(BIN)\help\bbhelp_fr.hlp bbhelp_fr.ipf

$(BIN)\help\bbhelp_it.hlp : help\bbhelp_it.ipf help\mous.bmp
	@if not exist $(BIN)\help mkdir $(BIN)\help
	@set WIPFC=$(WIPFC)
	cd help && wipfc -l en_US -o ..\$(BIN)\help\bbhelp_it.hlp bbhelp_it.ipf

clean :
	-del /q $(BIN)\bb.exe $(BIN)\*.obj $(BIN)\main.res $(BIN)\help\bbhelp_*.hlp $(BIN)\bb.map $(BIN)\bb.sym 2>nul
	@if exist $(BIN)\help rmdir $(BIN)\help
	@if exist $(BIN) rmdir $(BIN)
