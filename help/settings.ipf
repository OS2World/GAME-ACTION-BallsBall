.*==============================================================*\
.*                                                              *
.* Settings.ipf - Information Tag Language file for the Edit    *
.*               menu help panels.                              *
.*                                                              *
.*==============================================================*/

.*--------------------------------------------------------------*\
.*  Main Settings menu                                              *
.*      res = PANEL_SETTINGS                                    *
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Settings Menu
:i1 id=Settings.Settings Menu
:p.The Settings menu contains commands that you use to change any
avialable settings of BallsBall Game. The following commands
appear in the Settings menu&colon.
:parml tsize=25 break=none.
:pt.Sound
:pd.Switches on or off sound
:pt.Style
:pd.Switches 2D or 3D styles of the cells
:pt.Level
:pd.You can set Level you like
:pt.All Settings
:pd.Shows Dialog with all avialable settings.
:eparml.

.*--------------------------------------------------------------*\
.*  Edit menu Sound command help panel                          *
.*      res = PANEL_SOUND                                       *
.*--------------------------------------------------------------*/
:h1 res=2305 name=PANEL_SOUND.Sound
:i2 refid=Settings.Sound
:p. You can switch on or off sound by using the Sounds
commands.

.*--------------------------------------------------------------*\
.*  Edit menu Style command help panel                          *
.*      res = PANEL_STYLE                                       *
.*--------------------------------------------------------------*/
:h1 res=2302 name=PANEL_STYLE.Style
:i2 refid=Settings.Style
:p. You can change a style of the cells by using the Style
commands, or F2 and F3 keys.

.*--------------------------------------------------------------*\
.*  Edit menu Level command help panel                          *
.*      res = PANEL_LEVEL                                       *
.*--------------------------------------------------------------*/
:h1 res=2308 name=PANEL_LEVEL.Level
:i2 refid=Settings.Level
:p. You can set Level you like between 0 and 11 by using the Level
commands.

.*--------------------------------------------------------------*\
.*  Edit menu Level command help panel                          *
.*      res = PANEL_SETTINGS_ALL                                *
.*--------------------------------------------------------------*/
:h1 res=2314 name=PANEL_SETTINGS_ALL.All Settings
:i2 refid=Settings.All Settings
:p. You can run Settins Dialog by using the All Settings command.
:p. In this Dialog you can change colors of the Balls and Cells
of different types, size of Cells and Window, set style, sound
and mode of moving after capture. Also you can set default
settings.
