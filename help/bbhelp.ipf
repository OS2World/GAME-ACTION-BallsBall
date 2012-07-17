.*==============================================================*\
.*                                                              *
.* bbhelp.ipf - Information Tag Language file for the main      *
.*              sample application's help manager               *
.*                                                              *
.*==============================================================*/
:userdoc.

.*--------------------------------------------------------------*\
.*  Main window extended help panel                             *
.*      res = PANEL_MAIN                                        *
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.About BallsBall version 1.1
:i1 id=aboutMain. About BallsBall version 1.1
:p.The BallsBall Game is a sample Presentation Manager game.
I saw game like this some years ago on old big, but no good
computers with black-green screens. I not to remember name of
the game and authors of idea, but I played then without a
stop. Then the big and bad computers have disappeared, have
occurred small and bad and I have absolutly overlooked this
toy. But resently has recollected, and so was wanted again to
play, that has made it anew.
:p.And I have thought: let the people play too!
I have added some decorations, which so appeal to the public.
And here, look!

:ul.
:ul.
:li.:link reftype=hd res=1.Rules:elink.
:li.:link reftype=hd res=2.License:elink.
:eul.
:eul.

:p.If you have any suggestions or questions please
write me &colon.
:p.e-mail &colon. :hp4.d_ivanoff@mail.ru :ehp4.
:p.Please, write me on english or russian.



.*-- Import the File menu help file --*
.im file.ipf

.*-- Import the Settings menu help file --*
.im settings.ipf

.*-- Import the Help menu help file --*
.im help.ipf

.*-- Import the my information help file --*
.im myhelp.ipf

:euserdoc.
