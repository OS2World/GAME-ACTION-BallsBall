.* BallsBall help (en) - generated; texts per language, same panel ids
:userdoc.
:title.BallsBall Help

.*--------------------------------------------------------------*\
.*  Main window extended help panel (PANEL_MAIN)
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.About BallsBall
:i1 id=aboutMain.About BallsBall
:p.BallsBall is a Presentation Manager game. With the runner you build new paths across the field, while balls bounce around and hunters patrol the paths.
:p.This is a modernized build of the open-source game. It is built with Open Watcom, carries English, Dutch, Spanish, German, French and Italian in one executable, and scales the game window to at least 1024x768 when the desktop allows it (the cells stay square).
:p.Choose a topic&colon.
:ul compact.
:li.:link reftype=hd res=1.Rules:elink.
:li.:link reftype=hd res=2.License:elink.
:li.:link reftype=hd res=3.Mouse:elink.
:eul.

.*--------------------------------------------------------------*\
.*  Rules, license, mouse
.*--------------------------------------------------------------*/
:h1 res=1.Rules
:i1 id=Rules.Rules
:p.The rules are simple. With the runner you make new paths across the field. Steer him with the arrow :link reftype=hd res=2950.keys:elink. (left, right, up and down) or with the :link reftype=hd res=3.mouse:elink.. You get one point for each cell you add. Cells are added when the runner returns to an old path.
:p.Balls move over the field. If a ball touches a new path before the runner has reached an old path, the new path falls. You lose one point for each destroyed cell and 50 points for a collision.
:p.If you manage to stop a ball you get 100 points. This is difficult but possible: for example, you can limit its field. Under some conditions a ball also jams. Which conditions? Try it!
:p.Hunters move along the paths. They only move ahead; if that is impossible they turn around, and when there is a choice they pick a direction at random. A collision with a hunter costs 50 points.
:p.The game has 11 levels. The number of balls and hunters is the level plus 4. If you collect 2/3 of the points available on the field within 3 minutes you pass to the next level, otherwise you lose. If you collect 4/5 in less than 3 minutes you pass to the next level earlier. If you are already on level 11, you have won.
:p.The text line shows your score. 4/5 is 100%, 2/3 is 84%.
:p.If after the game you reach place 10 or higher, your name is entered in the High Scores.

:h1 res=2.License
:i1 id=License.License
:p.BallsBall is free software, released under the GNU General Public License, version 3 (see LICENSE.txt). The program is provided "as is", without warranty of any kind.
:p.Original game by Dmitry Ivanov.
:p.Please distribute the program together with these files&colon.
:ul compact.
:li.LICENSE.txt
:li.readme.txt
:li.bbhelp_en.hlp
:eul.

:h1 res=3.Mouse
:i1 id=Mouse.Mouse
:p.The window interior is divided, relative to the runner, into four parts&colon. left, right, top and bottom.
:artwork align=left name='mous.bmp'.
:p.Click in one of these parts and the runner moves to the left, to the right, upwards or downwards respectively.

.*--------------------------------------------------------------*\
.*  Game menu
.*--------------------------------------------------------------*/
:h1 res=2210 name=PANEL_FILE.Game Menu
:i1 id=File.Game Menu
:p.The :hp2.Game:ehp2. menu contains the commands to start, load and save games, to pause the game, to show the high scores and to exit BallsBall. The following commands appear in the :hp2.Game:ehp2. menu&colon.
:parml tsize=25 break=none.
:pt.New Game
:pd.Starts a new untitled game.
:pt.Load Game
:pd.Loads a saved game from a file.
:pt.Save Game
:pd.Saves the game to the current file.
:pt.Save Game as
:pd.Saves the game in a file with a new name.
:pt.Pause Game
:pd.Pauses or resumes the game.
:pt.Show High Scores
:pd.Shows the high scores.
:pt.Exit
:pd.Quits BallsBall.
:eparml.

:h1 res=2220 name=PANEL_FILENEW.New Game
:i2 refid=File.New Game
:p.Use the :hp2.New Game:ehp2. command to start a new game. Score and level are set to zero and the title bar shows the game as untitled.

:h1 res=2230 name=PANEL_FILEOPEN.Load Game
:i2 refid=File.Load Game
:p.Use the :hp2.Load Game:ehp2. command to load a saved game from a file. A dialog shows the files with the extension .bbg in the current directory.

:h1 res=2240 name=PANEL_FILESAVE.Save Game
:i2 refid=File.Save Game
:p.Use the :hp2.Save Game:ehp2. command to save the game to the current file. If the game has no name yet, the :hp2.Save Game as:ehp2. dialog appears first.

:h1 res=2250 name=PANEL_FILESAVEAS.Save Game as
:i2 refid=File.Save Game as
:p.Use the :hp2.Save Game as:ehp2. command to name and save the game in a new file. A dialog prompts you for the new file name.

:h1 res=2270 name=PANEL_DIRECTION_START.Pause Game
:i2 refid=File.Pause Game
:p.Use the :hp2.Pause Game:ehp2. command to run the game, or to stop it if it is already running. Enter and Space do the same.

:h1 res=2260 name=PANEL_HIGHSCORES.Show High Scores
:i2 refid=File.Show High Scores
:p.Use the :hp2.Show High Scores:ehp2. command to show a dialog with the current high scores.

:h1 res=2290 name=PANEL_FILEEXIT.Exit
:i2 refid=File.Exit
:p.You quit BallsBall with the :hp2.Exit:ehp2. command, or by pressing Esc or Alt+F4.

.*--------------------------------------------------------------*\
.*  Options menu
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Options Menu
:i1 id=Settings.Options Menu
:p.The :hp2.Options:ehp2. menu contains the commands you use to change the settings of BallsBall. The following commands appear in the :hp2.Options:ehp2. menu&colon.
:parml tsize=25 break=none.
:pt.Sound
:pd.Switches the sound on or off.
:pt.Style
:pd.Switches between the 2D and the 3D style of the cells.
:pt.Level
:pd.Sets the level you like, from 0 to 11.
:pt.Visual Settings
:pd.Shows a dialog with all visual settings.
:pt.Language
:pd.Selects the interface language&colon. English, Dutch, Spanish, German, French or Italian. The help follows the chosen language.
:pt.Background Run
:pd.Lets the game keep running while its window is not active (Ctrl+B).
:pt.Frame Controls
:pd.Hides or shows the title bar, system menu and menu bar, leaving only the game area (Ctrl+F).
:pt.Save settings on exit
:pd.When checked (the default), the settings are saved when you exit the game. When unchecked, changed settings are not saved.
:eparml.

:h1 res=2305 name=PANEL_SOUND.Sound
:i2 refid=Settings.Sound
:p.Use the :hp2.Sound:ehp2. commands to switch the sound on or off.

:h1 res=2302 name=PANEL_STYLE.Style
:i2 refid=Settings.Style
:p.Use the :hp2.Style:ehp2. commands, or the F2 key, to change the style of the cells.

:h1 res=2308 name=PANEL_LEVEL.Level
:i2 refid=Settings.Level
:p.Use the :hp2.Level:ehp2. commands to set the level you like, between 0 and 11.

:h1 res=2314 name=PANEL_SETTINGS_ALL.Visual Settings
:i2 refid=Settings.Visual Settings
:p.Use the :hp2.Visual Settings:ehp2. command to open the settings dialog. In it you can change the colors of the balls and of the different types of cells, the size of the cells and of the window, the style, the sound and the way of moving after a capture. You can also restore the default settings.
:p.The game window is enlarged automatically, if the desktop allows it, so that the field reaches at least 1024x768. The cells stay square and the window is never made larger than the desktop.

.*--------------------------------------------------------------*\
.*  Help menu
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Help Menu
:i1 id=Help.Help Menu
:p.The :hp2.Help:ehp2. menu contains the commands you use to call the help. The following commands appear in the :hp2.Help:ehp2. menu&colon.
:parml tsize=25 break=none.
:pt.Help index
:pd.Shows the list of all help topics.
:pt.General help
:pd.General information about the game, the rules and the license.
:pt.Using help
:pd.Shows the system help about using help.
:pt.Keys help
:pd.Shows the hot keys.
:pt.About
:pd.Shows the version and copyright of the game.
:eparml.

:h1 res=2920 name=PANEL_HELPINDEX.Help index
:i2 refid=Help.Help index
:p.The list of all help topics is placed here. Choose a topic to see information about it.

:h1 res=2930 name=PANEL_HELPGENERAL.General help
:i2 refid=Help.General help
:p.This is the General help window, with the main help information.

:h1 res=2940 name=PANEL_HELPUSINGHELP.Using help
:i2 refid=Help.Using help
:p.Here the system information about using help is placed.

:h1 res=2950 name=PANEL_HELPKEYS.Keys
:i2 refid=Help.Keys
:p.You can use the following hot keys&colon.
:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.shows the help.
:pt.:hp8.F2:ehp8.
:pd.sets the 2D style of the cells.
:pt.:hp8.F3:ehp8.
:pd.quits the game.
:pt.:hp8.Enter:ehp8.
:pd.runs the game, or stops it if it is already running.
:pt.:hp8.Space:ehp8.
:pd.the same as Enter.
:pt.:hp8.Left arrow:ehp8.
:pd.the runner goes left.
:pt.:hp8.Right arrow:ehp8.
:pd.the runner goes right.
:pt.:hp8.Up arrow:ehp8.
:pd.the runner goes up.
:pt.:hp8.Down arrow:ehp8.
:pd.the runner goes down.
:pt.:hp8.Any other key:ehp8.
:pd.the runner stops.
:pt.:hp8.Esc:ehp8.
:pd.quits the game.
:pt.:hp8.Alt+F4:ehp8.
:pd.quits the game.
:pt.:hp8.Ctrl+N:ehp8.
:pd.starts a new game.
:pt.:hp8.Ctrl+H:ehp8.
:pd.shows the high scores.
:pt.:hp8.Ctrl+P:ehp8.
:pd.pauses or resumes the game.
:pt.:hp8.Ctrl+B:ehp8.
:pd.switches Background Run on or off.
:pt.:hp8.Ctrl+F:ehp8.
:pd.hides or shows the frame controls.
:eparml.

:h1 res=2970 name=PANEL_HELPPRODUCTINFO.About
:i2 refid=Help.About
:p.This dialog displays information about the game, such as the version number, the copyright notice and a picture.

:h1 hide res=3100 name=PANEL_PRODUCTINFODLG.About
:p.This dialog displays information about the game, such as the version number, the copyright notice and a picture.

.*--------------------------------------------------------------*\
.*  load dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4163 scroll=none titlebar=yes nosearch.Load Game
:ol compact.
:li.Select the down arrow to the right of the Drive list to display all the drives on your system.
:li.Select a drive from the Drive list.
:li.Select a directory from the Directory list.
:li.Select a file name from the File list, or type in a file name, and select the :hp2.Load Game:ehp2. pushbutton.
:eol.
:p.For specific help, select a topic below.
:dl compact tsize=22.
:dt.:link reftype=hd res=20501.File name:elink.
:dd.
:dt.:link reftype=hd res=20502.Type of file:elink.
:dd.
:dt.:link reftype=hd res=20503.Drive:elink.
:dd.
:dt.:link reftype=hd res=20504.File:elink.
:dd.
:dt.:link reftype=hd res=20505.Directory:elink.
:dd.
:dt.:link reftype=hd res=20506.Load Game:elink.
:dd.
:edl.

:h1 hide res=20501 nosearch.File name
:p.Type the name of the file you want to load in the File name field and select the :hp2.Load Game:ehp2. pushbutton.
:p.:link reftype=hd res=4163.General help:elink.

:h1 hide res=20502 nosearch.Type of file
:p.Select the down arrow to the right of the Type of file field to display the available file types.
:p.:link reftype=hd res=4163.General help:elink.

:h1 hide res=20503 nosearch.Drive
:p.The Drive list displays the drives on your system. Select the drive that contains the file.
:p.:link reftype=hd res=4163.General help:elink.

:h1 hide res=20504 nosearch.File
:p.The File list displays all the files with the extension .bbg in the directory you selected from the Directory list. Select the file you want to load.
:p.:link reftype=hd res=4163.General help:elink.

:h1 hide res=20505 nosearch.Directory
:p.The Directory list displays the directories on the selected drive. Select a directory to display the files from that directory in the File list.
:p.:link reftype=hd res=4163.General help:elink.

:h1 hide res=20506 nosearch.Load Game
:p.Select the :hp2.Load Game:ehp2. pushbutton to load the game from the file.
:p.:link reftype=hd res=4163.General help:elink.

.*--------------------------------------------------------------*\
.*  save dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4210 scroll=none titlebar=yes nosearch.Save Game as
:ol compact.
:li.Select the down arrow to the right of the Drive list to display all the drives on your system.
:li.Select a drive from the Drive list.
:li.Select a directory from the Directory list.
:li.Type the name of the file you want to save in the File name field and select the :hp2.Save Game:ehp2. pushbutton.
:eol.
:p.For specific help, select a topic below.
:dl compact tsize=22.
:dt.:link reftype=hd res=26501.File name:elink.
:dd.
:dt.:link reftype=hd res=26502.Type of file:elink.
:dd.
:dt.:link reftype=hd res=26503.Drive:elink.
:dd.
:dt.:link reftype=hd res=26504.File:elink.
:dd.
:dt.:link reftype=hd res=26505.Directory:elink.
:dd.
:dt.:link reftype=hd res=26506.Save Game:elink.
:dd.
:edl.

:h1 hide res=26501 nosearch.File name
:p.Type the name of the file you want to save in the File name field and select the :hp2.Save Game:ehp2. pushbutton.
:p.:link reftype=hd res=4210.General help:elink.

:h1 hide res=26502 nosearch.Type of file
:p.Select the down arrow to the right of the Type of file field to display the available file types.
:p.:link reftype=hd res=4210.General help:elink.

:h1 hide res=26503 nosearch.Drive
:p.The Drive list displays the drives on your system. Select the drive on which you want to save the file.
:p.:link reftype=hd res=4210.General help:elink.

:h1 hide res=26504 nosearch.File
:p.The File list displays all the files in the directory you selected from the Directory list. Select a file to reuse its name.
:p.:link reftype=hd res=4210.General help:elink.

:h1 hide res=26505 nosearch.Directory
:p.The Directory list displays the directories on the selected drive. Select a directory to display the files from that directory in the File list.
:p.:link reftype=hd res=4210.General help:elink.

:h1 hide res=26506 nosearch.Save Game
:p.Select the :hp2.Save Game:ehp2. pushbutton to save the game in the file, in the drive and directory you selected, with the file name you specified.
:p.:link reftype=hd res=4210.General help:elink.

.*--------------------------------------------------------------*\
.*  Pull-down help for the save choices
.*--------------------------------------------------------------*/
:h1 hide res=4192 id=A4192 nosearch.Save Game
:p.Use :hp2.Save Game:ehp2. to store the game you play. After the game is saved in a file, the name of the file is shown in the window title.

:h1 hide res=4208 id=A4208 nosearch.Save Game as
:p.Use :hp2.Save Game as:ehp2. to name and save a new game, or to save a game under a different name, in a different directory or on a different disk.

:euserdoc.
