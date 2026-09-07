Game-BallsBall
==================
BallsBall is a really simple and addictive game for OS/2. The game objective is to "jail" every ball that's on the loose. To do that you control the green ball to start making walls between the red balls.

![BallsBall ScreenShot](/doc/BallsBall.png)

VERSION 1.2
===========
BallsBall 1.2 is a modernized build of the open-source release 1.1
(2002).  What is new in this release:

- Build system: the game builds with Open Watcom from a plain
  `compile.cmd` (or `wmake -f makefile.wat`); the makefile has no
  hardcoded paths.  The old 2002 makefiles are kept under src/ for
  reference only.
- Languages: English, Dutch, Spanish, German and French are now all
  compiled into the single bb.exe executable (shifted resource
  namespaces).  The old separate-language sources (dlg.eng.c,
  dlg.dutch.c, pnt.eng.c, pnt.dutch.c, main.eng.rc, main.dutch.rc,
  dialogs.eng.dlg, dialogs.dutch.dlg) are kept under src/ for
  reference but are no longer used.
- Resolution: the game window now grows to at least 1024x768 when the
  desktop allows it (the cells stay square) and is never made larger
  than the desktop.
- Help: the English BBHELP.HLP pages are included; rebuilding them is
  optional and needs the IBM/ArcaOS IPF compiler.

LICENSE
========
GNU GPL V2

COMPILE TOOLS
=============
- Open Watcom (wcc386, wlink, wrc) - required to build the executable
- IBM/ArcaOS IPF compiler (ipfc.exe) - only needed for the help pages

BUILD (Open Watcom, on OS/2)
============================
Run:

    compile.cmd          (or: wmake -f makefile.wat)

If the WATCOM environment variable is set, it is used for the C include
path; otherwise the compilers use the headers from their own install.
The build produces bin-wat\bb.exe (plus bb.map). Run bb.exe from bin-wat
so the game can create/read its bb.ini and BBHELP.HLP next to itself.

The original 2002 makefiles (src\bb.mk1, src\bb.tgt, src\ballsball.mk)
hardcoded f:\ballsball paths and are kept for reference only; the new
makefile.wat has no hardcoded paths.

Optional help pages (BBHELP.HLP) are compiled from help\bbhelp.ipf and
copied to bin-wat. The game also runs without them (help is disabled):

    wmake -f makefile.wat help

RESOLUTION
==========
The field size follows the values in bb.ini (Bitmaps\Size, Columns,
Rows). At startup the cell size (Size) is automatically increased, if
needed, so the game window reaches at least 1024x768 when the desktop
allows it; the window is never made larger than the desktop and the
cells stay square.

LANGUAGES
=========
The interface is available in English, Dutch, Spanish, German and
French. Pick one from the Settings > Language menu, or set it in bb.ini:

    [Settings]
    Language=0    (0=English, 1=Nederlands, 2=Espanol, 3=Deutsch,
                    4=Francais)

All five languages are compiled into the single executable as shifted
resource namespaces (LANG_BASE_EN..LANG_BASE_FR in src/main.h). The
strings and dialogs live in src/lang_*.rc and src/dialogs.*.dlg; the
help pages (BBHELP.HLP) are English only.

AUTHORS
============
- Dmitry Ivanov
