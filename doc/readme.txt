-------------------------------------------------------------------------------
BallsBall 1.2 - Source package readme
-------------------------------------------------------------------------------

This package is a modernized build of the open-source BallsBall /
Vangbal source.  It is the same game, rebuilt for OS/2 and with the
five languages unified into one executable.

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
  - Optional BBHELP.HLP rebuild: `wmake -f makefile.wat help` (needs
    the IPF compiler, ipfc).

Build
-----
Run `compile.cmd` (or `wmake -f makefile.wat`); the output is
bin-wat\bb.exe plus bb.map.  Run bb.exe from bin-wat so the game can
create/read its bb.ini and BBHELP.HLP next to itself.

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