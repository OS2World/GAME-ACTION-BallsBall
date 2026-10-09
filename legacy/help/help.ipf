.*==============================================================*\
.*                                                              *
.* Help.ipf - Information Tag Language file for the Help menu   *
.*              help panels.                                    *
.*                                                              *
.*==============================================================*/

.*--------------------------------------------------------------*\
.*  Main Help menu                                              *
.*      res = PANEL_HELP                                        *
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Help Menu
:i1 id=Help.Help Menu
:p.The Help menu contains commands that you use to call of Help.
The following commands appear in the Help menu&colon.
:parml tsize=25 break=none.
:pt.Help index
:pd.Shows information about Menu items.
:pt.General help
:pd.General information about game, rules and license.
:pt.Using help
:pd.Call system help.
:pt.Keys help
:pd.Shows information about hot keys.
:pt.Product information
:pd.Shows sample dialog with information about game
:eparml.

.*--------------------------------------------------------------*\
.*  Help menu Save As command help panel                        *
.*      res = PANEL_HELPINDEX                                   *
.*--------------------------------------------------------------*/
:h1 res=2920 name=PANEL_HELPINDEX.Index
:i2 refid=Help.Index
:p.List of all help items is here placed. You choose any
to shows information about help item you want.

.*--------------------------------------------------------------*\
.*  Help menu General help help panel                           *
.*      res = PANEL_HELPGENERAL                                 *
.*--------------------------------------------------------------*/
:h1 res=2930 name=PANEL_HELPGENERAL.General help
:i2 refid=Help.General
:p.It is General Help window with main help information.
.*--------------------------------------------------------------*\
.*  Help menu Using help help panel                             *
.*      res = PANEL_HELPUSINGHELP                               *
.*--------------------------------------------------------------*/
:h1 res=2940 name=PANEL_HELPUSINGHELP.Using Help
:i2 refid=Help.Using
:p.Here placed system information about Using Help.


.*--------------------------------------------------------------*\
.*  Help menu Save command help panel                           *
.*      res = PANEL_HELPKEYS                                    *
.*--------------------------------------------------------------*/
:h1 res=2950 name=PANEL_HELPKEYS.Keys
:i2 refid=Help.Keys

:p.You can use follow hot keys &colon.

:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.call help.
:pt.:hp8.F2:ehp8.
:pd.set 2D-style of cells.
:pt.:hp8.F3:ehp8.
:pd.set 3D-style of cells.
:pt.:hp8.Enter:ehp8.
:pd.run game or stop if already running.
:pt.:hp8.Space:ehp8.
:pd.run game or stop if already running (dupliates previous key).
:pt.:hp8.Left arrow:ehp8.
:pd.runner goes on left.
:pt.:hp8.Right arrow:ehp8.
:pd.runner goes on right.
:pt.:hp8.Up arrow:ehp8.
:pd.runner goes on upwards.
:pt.:hp8.Down arrow:ehp8.
:pd.runner goes on downwards.
:pt.:hp8.Any symbol key:ehp8.
:pd.runner stays.
:pt.:hp8.Esc:ehp8.
:pd.quits the BallsBall Game.
:pt.:hp8.Alt+F4:ehp8.
:pd.quits the BallsBall Game (dupliates previous key).
:eparml.

.*--------------------------------------------------------------*\
.*  Help menu Product information help panel                    *
.*      res = PANEL_HELPPRODUCTINFO                             *
.*--------------------------------------------------------------*/
:h1 res=2970 name=PANEL_HELPPRODUCTINFO.Product information
:i2 refid=Help.Product information
:p.This dialog displays information about the game, such as
version number,copyright notice, my e-mail and beautiful
picture.
