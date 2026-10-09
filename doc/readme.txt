-------------------------------------------------------------------------------
BallsBall 1.4 - Source package readme
-------------------------------------------------------------------------------

This package is a modernized build of the open-source BallsBall /
Vangbal source.  It is the same game, rebuilt for OS/2 and with six
languages unified into one executable.

What is new in 1.4
------------------
  - Options menu reordered: Sound, Style, Level, Visual Settings...,
    Language, Background Run, Frame Controls, Save settings on exit.
  - New "Save settings on exit" option (on by default, kept in bb.ini).
  - Frame Controls (Ctrl+F) no longer leaves a white strip on top.
  - New shortcuts: Ctrl+N (New Game) and Ctrl+H (Show High Scores).
  - Help rewritten: one IPF source per language, built into
    bin\help\bbhelp_xx.hlp; the help follows the chosen language.
  - bb.ini and the help files are found next to the executable.
  - compile.cmd fixed (finds Open Watcom and the OS/2 Toolkit).

What is new in 1.3
------------------
  - Italian (Italiano) added to the Language menu; now six languages:
    English, Nederlands, Espanol, Deutsch, Francais, Italiano.
  - Menu bar renamed to [Game] [Options] [Help].
  - Ctrl+X and F3 exit the game.
  - Build flags switched from -od -d2 (debug) to -Oaxt -d0 (optimised
    release); stack raised to 65536 bytes.
  - compile.cmd auto-detects WATCOM installation, writes full build log
    to compile-wat.log, and exits non-zero on failure.
  - Output directory renamed from bin-wat to bin.
  - BLDLEVEL signature added.

What is new in 1.2
------------------
  - Open Watcom build (compile.cmd / makefile.wat) with no hardcoded
    paths; see README.md for instructions.
  - All five languages - English, Dutch, Spanish, German and French -
    compiled into the single bb.exe (shifted resource namespaces).
    The old separate-language sources are kept under src/ for
    reference only.
  - The game window now scales to at least 1024x768 when the desktop
    allows it; the cells stay square and the window is never made
    larger than the desktop.
  - One help file per language (bbhelp_en.hlp ... bbhelp_it.hlp), built from
    help\bbhelp_xx.ipf with wipfc; the help follows the chosen language.

Build
-----
Run `compile.cmd`; Open Watcom is auto-detected from C:\WATCOM or
D:\WATCOM.  The output is bin\bb.exe plus bb.map.  Run bb.exe from
bin\ so the game can create/read its bb.ini and the help\bbhelp_xx.hlp
files next to itself.

History
-------
-------------------------------------------------------------------------------
BallsBall 1.1 / Vangbal 1.1 Source Code

2002-04-07

NOTE: BallsBall 1.1 / Vangbal 1.1 had been made OpenSource on 2002-04-07.

This Game is now OpenSource under the GNU GPL licence, thanks to the Author Dmitry Ivanov

Martin Iturbide
martin@os2world.com

http://www.os2world.com
-------------------------------------------------------------------------------
