Game-BallsBall
==================
BallsBall is a really simple and addictive game for OS/2. The game objective is to "jail" every ball that's on the loose. To do that you control the green ball to start making walls between the red balls.

![BallsBall ScreenShot](/doc/BallsBall.png)

VERSION 1.5
===========
BallsBall 1.5 adds Key Mapping and joystick support:

- New Options - Key Mapping... window (Keyboard and Joystick tabs), translated
  in all six languages.
- Keyboard: map the four directions and Start / Pause to any key (click a
  box and press the key). Enter always starts / pauses; any other character key
  still stops the runner. The default keys are the ones used before.
- Joystick (GAME$ driver): Enable Joystick, Joystick A / B and Calibrate A /
  Calibrate B; every action (the four directions, Start / Pause and Stop
  runner) can be a joystick button or a stick direction. What is held when
  the game starts is only taken as the starting state, and a change has to be
  seen twice, so a stick that does not rest in the centre cannot start or
  pause the game by itself.
- The mappings are saved in bb.ini (section Keys).
- The white strip on the left of the Key Mapping pages is gone.
- Menu shortcuts: Exit shows Ctrl+X (was F3 / Esc) and Ctrl+S toggles between the
  2D and 3D style (shown on the Style menu); the F2 / F3 labels are gone from
  the style items (the F2 / F3 keys themselves still work).
- BLDLEVEL and About box show version 1.5.


VERSION 1.4
===========
BallsBall 1.4 reorganizes the menus and the help:

- Options menu reordered: Sound, Style, Level, Visual Settings..., Language,
  Background Run, Frame Controls, Save settings on exit.
- New "Save settings on exit" option (on by default, kept in bb.ini).
- Frame Controls (Ctrl+F) no longer leaves a white strip on top; the
  window shrinks and grows around the game area.
- New shortcuts: Ctrl+N (New Game) and Ctrl+H (Show High Scores).
- Help rewritten: one IPF source per language (help\bbhelp_xx.ipf) built into
  bin\help\bbhelp_xx.hlp; the help follows the chosen language. The old
  multi-file English source is kept in legacy\help.
- bb.ini and the help files are found next to the executable, whatever the
  working directory.
- compile.cmd fixed: it now finds Open Watcom (binp) and the OS/2 Toolkit.


VERSION 1.3
===========
BallsBall 1.3 adds Italian and standardizes the build:

- Italian (Italiano) added; now six languages: English, Nederlands,
  Espanol, Deutsch, Francais, Italiano.
- Menu bar renamed: [~Game] [~Options] [~Help] (was [~File] [S~ettings]).
- Ctrl+X and F3 exit the game.
- Build flags: -Oaxt -d0 (optimised release), replacing -od -d2 (debug).
- Stack raised to 65536 bytes.
- compile.cmd auto-detects WATCOM (C:\\WATCOM or D:\\WATCOM), logs to
  compile-wat.log, exits non-zero on failure.
- Output directory is now bin\\ (was bin-wat\\).
- BLDLEVEL signature added (static const char in main.c).


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
- Help: one help file per language (bbhelp_en.hlp, bbhelp_nl.hlp, bbhelp_es.hlp,
  bbhelp_de.hlp, bbhelp_fr.hlp, bbhelp_it.hlp), built from help\bbhelp_xx.ipf.
  The help follows the language chosen in Options.

LICENSE
========
GNU GPLv3 or later

COMPILE TOOLS
=============
- Open Watcom (wcc386, wlink, wrc) - required to build the executable
- Open Watcom IPF compiler (wipfc) - builds the help files

BUILD (Open Watcom, on OS/2)
============================
Open Watcom is auto-detected (C:\WATCOM or D:\WATCOM). Run:

    compile.cmd

This logs to compile-wat.log and produces bin\bb.exe (plus bb.map).
Run bb.exe from bin\ so the game can create/read its bb.ini and
the bbhelp_xx.hlp files in its help folder.

The help files are compiled from help\bbhelp_xx.ipf by the same build
(or on their own with `wmake -f makefile.wat help`).

RESOLUTION
==========
The field size follows the values in bb.ini (Bitmaps\Size, Columns,
Rows). At startup the cell size (Size) is automatically increased, if
needed, so the game window reaches at least 1024x768 when the desktop
allows it; the window is never made larger than the desktop and the
cells stay square.

LANGUAGES
=========
The interface is available in English, Nederlands, Espanol, Deutsch,
Francais and Italiano. Pick one from the Options > Language menu, or
set it in bb.ini:

    [Settings]
    Language=0    (0=English, 1=Nederlands, 2=Espanol, 3=Deutsch,
                    4=Francais, 5=Italiano)

All six languages are compiled into the single executable as shifted
resource namespaces (LANG_BASE_EN..LANG_BASE_IT in src/main.h). The
strings and dialogs live in src/lang_*.rc and src/dialogs.*.dlg; the
help pages are one file per language: help\bbhelp_xx.ipf -> bin\help\bbhelp_xx.hlp.
The old multi-file English help source is kept in legacy\help.

AUTHORS
============
- Dmitry Ivanov
- Martin Iturbide (Update 2026)

## LINKS
* https://github.com/OS2World/GAME-ACTION-BallsBall
