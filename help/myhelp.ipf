.*==============================================================*\
.*                                                              *
.* Myhelp.ipf - Information Tag Language file for the screens   *
.*              for help on application defined menu items.     *
.*                                                              *
.*==============================================================*/

.**************************************************************

:h1 res=1.Rules
:i1 id=Rules.Rules
:p.The rules are very simple. You should make new ways on
a field. You do it through the runner. You operate him with the
help of arrow

:link reftype=hd res=2950.keys:elink.

(to left, right, top and down) or

:link reftype=hd res=3.mouse.:elink.

For each added
cell you receive one point. The cells are added when runner
comes back on a old way.
:p.On a field balls go. If one of them touches a new way and
the runner had no time reach a old way, the new way falls.
You lose on a point for each destroyed cell and minuses of
50 points for collision.
:p.If to you will manage to stop a ball, you receive for it
100 points. It very difficultly, but probably. For example, you
can limit his field. Also under some conditions he jams. I
do not inform, which this condition. Try it!
:p.On ways hunters go. They move only ahead. If ahead to move is
impossible, they turn ago. If there is choice, they choose a
direction of movement casually. For collision with a hunter you
lose 50 points.
:p.The game has 11 levels. Quantity of balls and hunters equally
a level + 4. If for 3 minutes you have typed 2/3 points from
all existing on field, you pass to a next level. Otherwise you
have lost. If you have typed 4/5 points from all existing on
field less than for 3 minutes, you pass to a next level before.
If you already on 11 level, you have won.
:p.You can supervise for your score in text line.
4/5 is 100%, 2/3 is 84%.
:p.In any case, if you after the termination of game have got
on 10 place or higher, your name is introduced to the High
Scores.

.**************************************************************

:h1 res=2.License
:i1 id=License.License
:p. This is a shareware. The program is provided "as is" without
warranty of any kind. You may distribute the program only with
follow files &colon.

:lm margin=5.
.br
license.txt
.br
readme.txt
.br
bbhelp.hlp
:lm margin=1.

:p.If you enjoy the game, please execute following &colon.
:ol.
:li.Send me $5. If the business will go, there will be the
following version. Else the russian crisis will eat me and my
computer.
:li.If you not have $5 then drink beer for my health.
:li.If you not have even beer, though prayed for me.
:eol.
Note &colon. Fulfillment of all items is desirable.
:p.So, $5. You can send to me them or check to the
post-address&colon.
:lm margin=5. :hp8.
.br
Russia,Tver,170002,
.br
pr.Tchaykovskogo 37-201.
.br
Dmitry Ivanov :ehp8.

:p. or (it is one)
:hp8.
:p.Ost-West Handelsbank AG,
Frankfurt/Main,Germany acc.0103860417
SWIFT OWHB DE FF
:p.JOINT-STOCK COMMERCIAL BANK "MENATEP St.Peterburg"
 1, Nevskiy Av., St.Peterburg, RUSSIA
:p.TVER BRANCH OF JS COMMERCIAL BANK "MENATEP St.Peterburg"
 52, Radistcheva Str., 170000 Tver, RUSSIA
:p.30301.840.1.00009990027
:p.Private money order in favour of Ivanov Dmitri Urievich,
passport: VII-OH #679727 is issued by Centralniy ROVD,
Kalinin, Russia.
:p.Address: 37-201,pr.Tchaykovskogo, 170002, Tver, Russia
:ehp8.

.**************************************************************

:h1 res=3.Mouse

:p. The Window Interior is divided concerning a runner on four
parts - left, right, top and bottom.

:artwork align=left name='mous.bmp'.

:p. At clicking on these parts runner move to left, to right,
upwards or downwards respectively.

.**************************************************************

