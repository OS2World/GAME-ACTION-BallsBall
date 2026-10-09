.* BallsBall help (de) - generated; texts per language, same panel ids
:userdoc.
:title.BallsBall Hilfe

.*--------------------------------------------------------------*\
.*  Main window extended help panel (PANEL_MAIN)
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.Info zu BallsBall
:i1 id=aboutMain.Info zu BallsBall
:p.BallsBall ist ein Presentation-Manager-Spiel. Mit dem Laeufer baust du neue Wege ueber das Feld, waehrend Baelle herumspringen und Jaeger die Wege abpatrouillieren.
:p.Dies ist eine modernisierte Version des Open-Source-Spiels. Sie wird mit Open Watcom gebaut, enthaelt Englisch, Niederlaendisch, Spanisch, Deutsch, Franzoesisch und Italienisch in einem einzigen Programm und skaliert das Spielfenster auf mindestens 1024x768, wenn der Desktop es zulaesst (die Zellen bleiben quadratisch).
:p.Waehle ein Thema&colon.
:ul compact.
:li.:link reftype=hd res=1.Spielregeln:elink.
:li.:link reftype=hd res=2.Lizenz:elink.
:li.:link reftype=hd res=3.Maus:elink.
:eul.

.*--------------------------------------------------------------*\
.*  Rules, license, mouse
.*--------------------------------------------------------------*/
:h1 res=1.Spielregeln
:i1 id=Rules.Spielregeln
:p.Die Regeln sind einfach. Mit dem Laeufer legst du neue Wege ueber das Feld an. Du steuerst ihn mit den :link reftype=hd res=2950.Pfeiltasten:elink. (links, rechts, hoch und runter) oder mit der :link reftype=hd res=3.Maus:elink.. Du erhaeltst einen Punkt fuer jede hinzugefuegte Zelle. Zellen werden hinzugefuegt, wenn der Laeufer zu einem alten Weg zurueckkehrt.
:p.Baelle bewegen sich ueber das Feld. Beruehrt ein Ball einen neuen Weg, bevor der Laeufer einen alten Weg erreicht hat, faellt der neue Weg weg. Du verlierst einen Punkt fuer jede zerstoerte Zelle und 50 Punkte bei einer Kollision.
:p.Schaffst du es, einen Ball anzuhalten, erhaeltst du 100 Punkte. Das ist schwierig, aber moeglich: Du kannst zum Beispiel sein Feld begrenzen. Unter bestimmten Bedingungen klemmt ein Ball auch fest. Unter welchen? Probier es aus!
:p.Jaeger bewegen sich auf den Wegen. Sie gehen nur vorwaerts; ist das nicht moeglich, drehen sie um, und bei einer Wahl waehlen sie eine zufaellige Richtung. Eine Kollision mit einem Jaeger kostet 50 Punkte.
:p.Das Spiel hat 11 Stufen. Die Anzahl der Baelle und Jaeger ist die Stufe plus 4. Sammelst du innerhalb von 3 Minuten 2/3 der Punkte auf dem Feld, kommst du in die naechste Stufe, sonst hast du verloren. Sammelst du 4/5 in weniger als 3 Minuten, kommst du frueher in die naechste Stufe. Bist du schon auf Stufe 11, hast du gewonnen.
:p.Die Textzeile zeigt deinen Punktestand. 4/5 sind 100%, 2/3 sind 84%.
:p.Erreichst du nach dem Spiel Platz 10 oder besser, wird dein Name in die Rekorde eingetragen.

:h1 res=2.Lizenz
:i1 id=License.Lizenz
:p.BallsBall ist freie Software, veroeffentlicht unter der GNU General Public License, Version 3 (siehe LICENSE.txt). Das Programm wird "wie es ist" ohne jede Gewaehrleistung bereitgestellt.
:p.Urspruengliches Spiel von Dmitry Ivanov.
:p.Bitte gib das Programm zusammen mit diesen Dateien weiter&colon.
:ul compact.
:li.LICENSE.txt
:li.readme.txt
:li.bbhelp_de.hlp
:eul.

:h1 res=3.Maus
:i1 id=Mouse.Maus
:p.Das Fensterinnere ist, vom Laeufer aus gesehen, in vier Teile geteilt&colon. links, rechts, oben und unten.
:artwork align=left name='mous.bmp'.
:p.Klicke in einen dieser Teile, und der Laeufer bewegt sich nach links, rechts, nach oben beziehungsweise nach unten.

.*--------------------------------------------------------------*\
.*  Game menu
.*--------------------------------------------------------------*/
:h1 res=2210 name=PANEL_FILE.Menue Spiel
:i1 id=File.Menue Spiel
:p.Das Menue :hp2.Spiel:ehp2. enthaelt die Befehle zum Starten, Laden und Speichern von Spielen, zum Pausieren des Spiels, zum Anzeigen der Rekorde und zum Beenden von BallsBall. Folgende Befehle stehen im Menue :hp2.Spiel:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Neu
:pd.Startet ein neues unbenanntes Spiel.
:pt.Spiel laden
:pd.Laedt ein gespeichertes Spiel aus einer Datei.
:pt.Speichern
:pd.Speichert das Spiel in der aktuellen Datei.
:pt.Speichern unter
:pd.Speichert das Spiel in einer Datei mit neuem Namen.
:pt.Pause Spiel
:pd.Pausiert das Spiel oder setzt es fort.
:pt.Rekorde
:pd.Zeigt die Rekorde.
:pt.Beenden
:pd.Beendet BallsBall.
:eparml.

:h1 res=2220 name=PANEL_FILENEW.Neu
:i2 refid=File.Neu
:p.Mit :hp2.Neu:ehp2. startest du ein neues Spiel. Punktestand und Stufe werden auf null gesetzt, und die Titelleiste zeigt das Spiel als unbenannt.

:h1 res=2230 name=PANEL_FILEOPEN.Spiel laden
:i2 refid=File.Spiel laden
:p.Mit :hp2.Spiel laden:ehp2. laedst du ein gespeichertes Spiel aus einer Datei. Ein Dialog zeigt die Dateien mit der Endung .bbg im aktuellen Verzeichnis.

:h1 res=2240 name=PANEL_FILESAVE.Speichern
:i2 refid=File.Speichern
:p.Mit :hp2.Speichern:ehp2. speicherst du das Spiel in der aktuellen Datei. Hat das Spiel noch keinen Namen, erscheint zuerst der Dialog :hp2.Speichern unter:ehp2..

:h1 res=2250 name=PANEL_FILESAVEAS.Speichern unter
:i2 refid=File.Speichern unter
:p.Mit :hp2.Speichern unter:ehp2. gibst du dem Spiel einen Namen und speicherst es in einer neuen Datei. Ein Dialog fragt nach dem neuen Dateinamen.

:h1 res=2270 name=PANEL_DIRECTION_START.Pause Spiel
:i2 refid=File.Pause Spiel
:p.Mit :hp2.Pause Spiel:ehp2. startest du das Spiel oder haeltst es an, wenn es schon laeuft. Eingabe und Leertaste tun dasselbe.

:h1 res=2260 name=PANEL_HIGHSCORES.Rekorde
:i2 refid=File.Rekorde
:p.Mit :hp2.Rekorde:ehp2. zeigst du einen Dialog mit den aktuellen Rekorden.

:h1 res=2290 name=PANEL_FILEEXIT.Beenden
:i2 refid=File.Beenden
:p.Du beendest BallsBall mit :hp2.Beenden:ehp2. oder mit den Tasten Esc oder Alt+F4.

.*--------------------------------------------------------------*\
.*  Options menu
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Menue Einstellungen
:i1 id=Settings.Menue Einstellungen
:p.Das Menue :hp2.Einstellungen:ehp2. enthaelt die Befehle zum Aendern der Einstellungen von BallsBall. Folgende Befehle stehen im Menue :hp2.Einstellungen:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Ton
:pd.Schaltet den Ton ein oder aus.
:pt.Ansicht
:pd.Wechselt zwischen 2D- und 3D-Ansicht der Zellen.
:pt.Stufe
:pd.Stellt die gewuenschte Stufe von 0 bis 11 ein.
:pt.Visuelle Einstellungen
:pd.Zeigt einen Dialog mit allen visuellen Einstellungen.
:pt.Sprache
:pd.Waehlt die Sprache der Oberflaeche&colon. Englisch, Niederlaendisch, Spanisch, Deutsch, Franzoesisch oder Italienisch. Die Hilfe folgt der gewaehlten Sprache.
:pt.Hintergrundlauf
:pd.Laesst das Spiel weiterlaufen, waehrend sein Fenster nicht aktiv ist (Strg+B).
:pt.Rahmensteuerung
:pd.Blendet Titelleiste, Systemmenue und Menueleiste aus oder ein, sodass nur das Spielfeld bleibt (Strg+F).
:pt.Einstellungen beim Beenden speichern
:pd.Ist es markiert (Standard), werden die Einstellungen beim Beenden des Spiels gespeichert. Sonst werden geaenderte Einstellungen nicht gespeichert.
:eparml.

:h1 res=2305 name=PANEL_SOUND.Ton
:i2 refid=Settings.Ton
:p.Mit den Befehlen von :hp2.Ton:ehp2. schaltest du den Ton ein oder aus.

:h1 res=2302 name=PANEL_STYLE.Ansicht
:i2 refid=Settings.Ansicht
:p.Mit den Befehlen von :hp2.Ansicht:ehp2. oder der Taste F2 aenderst du die Ansicht der Zellen.

:h1 res=2308 name=PANEL_LEVEL.Stufe
:i2 refid=Settings.Stufe
:p.Mit den Befehlen von :hp2.Stufe:ehp2. stellst du die gewuenschte Stufe zwischen 0 und 11 ein.

:h1 res=2314 name=PANEL_SETTINGS_ALL.Visuelle Einstellungen
:i2 refid=Settings.Visuelle Einstellungen
:p.Mit :hp2.Visuelle Einstellungen:ehp2. oeffnest du den Einstellungsdialog. Dort aenderst du die Farben der Baelle und der verschiedenen Zellenarten, die Groesse der Zellen und des Fensters, die Ansicht, den Ton und die Bewegungsart nach einem Fang. Du kannst auch die Standardeinstellungen wiederherstellen.
:p.Das Spielfenster wird automatisch vergroessert, wenn der Desktop es zulaesst, sodass das Feld mindestens 1024x768 erreicht. Die Zellen bleiben quadratisch, und das Fenster wird nie groesser als der Desktop.

.*--------------------------------------------------------------*\
.*  Help menu
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Menue Hilfe
:i1 id=Help.Menue Hilfe
:p.Das Menue :hp2.Hilfe:ehp2. enthaelt die Befehle zum Aufrufen der Hilfe. Folgende Befehle stehen im Menue :hp2.Hilfe:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Hilfeindex
:pd.Zeigt die Liste aller Hilfethemen.
:pt.Allgemeine Hilfe
:pd.Allgemeine Informationen zum Spiel, zu den Regeln und zur Lizenz.
:pt.Hilfe benutzen
:pd.Zeigt die Systemhilfe zur Benutzung der Hilfe.
:pt.Tasten
:pd.Zeigt die Tastenkombinationen.
:pt.About
:pd.Zeigt Version und Copyright des Spiels.
:eparml.

:h1 res=2920 name=PANEL_HELPINDEX.Hilfeindex
:i2 refid=Help.Hilfeindex
:p.Hier steht die Liste aller Hilfethemen. Waehle ein Thema, um Informationen dazu zu sehen.

:h1 res=2930 name=PANEL_HELPGENERAL.Allgemeine Hilfe
:i2 refid=Help.Allgemeine Hilfe
:p.Dies ist das Fenster Allgemeine Hilfe mit den wichtigsten Informationen.

:h1 res=2940 name=PANEL_HELPUSINGHELP.Hilfe benutzen
:i2 refid=Help.Hilfe benutzen
:p.Hier stehen die Systeminformationen zur Benutzung der Hilfe.

:h1 res=2950 name=PANEL_HELPKEYS.Tasten
:i2 refid=Help.Tasten
:p.Du kannst folgende Tasten verwenden&colon.
:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.zeigt die Hilfe.
:pt.:hp8.F2:ehp8.
:pd.stellt die 2D-Ansicht der Zellen ein.
:pt.:hp8.F3:ehp8.
:pd.beendet das Spiel.
:pt.:hp8.Enter:ehp8.
:pd.startet das Spiel oder haelt es an, wenn es schon laeuft.
:pt.:hp8.Space:ehp8.
:pd.wie Eingabe.
:pt.:hp8.Left arrow:ehp8.
:pd.der Laeufer geht nach links.
:pt.:hp8.Right arrow:ehp8.
:pd.der Laeufer geht nach rechts.
:pt.:hp8.Up arrow:ehp8.
:pd.der Laeufer geht nach oben.
:pt.:hp8.Down arrow:ehp8.
:pd.der Laeufer geht nach unten.
:pt.:hp8.Jede andere Taste:ehp8.
:pd.der Laeufer bleibt stehen.
:pt.:hp8.Esc:ehp8.
:pd.beendet das Spiel.
:pt.:hp8.Alt+F4:ehp8.
:pd.beendet das Spiel.
:pt.:hp8.Ctrl+N:ehp8.
:pd.startet ein neues Spiel.
:pt.:hp8.Ctrl+H:ehp8.
:pd.zeigt die Rekorde.
:pt.:hp8.Ctrl+P:ehp8.
:pd.pausiert das Spiel oder setzt es fort.
:pt.:hp8.Ctrl+B:ehp8.
:pd.schaltet Hintergrundlauf ein oder aus.
:pt.:hp8.Ctrl+F:ehp8.
:pd.blendet die Rahmensteuerung aus oder ein.
:eparml.

:h1 res=2970 name=PANEL_HELPPRODUCTINFO.About
:i2 refid=Help.About
:p.Dieser Dialog zeigt Informationen zum Spiel, wie die Versionsnummer, den Copyright-Hinweis und ein Bild.

:h1 hide res=3100 name=PANEL_PRODUCTINFODLG.About
:p.Dieser Dialog zeigt Informationen zum Spiel, wie die Versionsnummer, den Copyright-Hinweis und ein Bild.

.*--------------------------------------------------------------*\
.*  load dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4163 scroll=none titlebar=yes nosearch.Spiel laden
:ol compact.
:li.Waehle den Pfeil nach unten rechts neben der Liste Laufwerk, um alle Laufwerke deines Systems anzuzeigen.
:li.Waehle ein Laufwerk aus der Liste Laufwerk.
:li.Waehle ein Verzeichnis aus der Liste Verzeichnis.
:li.Waehle einen Dateinamen aus der Liste Datei oder tippe einen Dateinamen ein, und waehle die Schaltflaeche :hp2.Oeffnen:ehp2..
:eol.
:p.Fuer spezielle Hilfe waehle unten ein Thema.
:dl compact tsize=22.
:dt.:link reftype=hd res=20501.Dateiname:elink.
:dd.
:dt.:link reftype=hd res=20502.Dateityp:elink.
:dd.
:dt.:link reftype=hd res=20503.Laufwerk:elink.
:dd.
:dt.:link reftype=hd res=20504.Datei:elink.
:dd.
:dt.:link reftype=hd res=20505.Verzeichnis:elink.
:dd.
:dt.:link reftype=hd res=20506.Oeffnen:elink.
:dd.
:edl.

:h1 hide res=20501 nosearch.Dateiname
:p.Tippe den Namen der zu ladenden Datei in das Feld Dateiname und waehle die Schaltflaeche :hp2.Oeffnen:ehp2..
:p.:link reftype=hd res=4163.Allgemeine Hilfe:elink.

:h1 hide res=20502 nosearch.Dateityp
:p.Waehle den Pfeil nach unten rechts neben dem Feld Dateityp, um die verfuegbaren Dateitypen anzuzeigen.
:p.:link reftype=hd res=4163.Allgemeine Hilfe:elink.

:h1 hide res=20503 nosearch.Laufwerk
:p.Die Liste Laufwerk zeigt die Laufwerke deines Systems. Waehle das Laufwerk, das die Datei enthaelt.
:p.:link reftype=hd res=4163.Allgemeine Hilfe:elink.

:h1 hide res=20504 nosearch.Datei
:p.Die Liste Datei zeigt alle Dateien mit der Endung .bbg im Verzeichnis, das du in der Liste Verzeichnis gewaehlt hast. Waehle die Datei, die du laden willst.
:p.:link reftype=hd res=4163.Allgemeine Hilfe:elink.

:h1 hide res=20505 nosearch.Verzeichnis
:p.Die Liste Verzeichnis zeigt die Verzeichnisse des gewaehlten Laufwerks. Waehle ein Verzeichnis, um seine Dateien in der Liste Datei anzuzeigen.
:p.:link reftype=hd res=4163.Allgemeine Hilfe:elink.

:h1 hide res=20506 nosearch.Oeffnen
:p.Waehle die Schaltflaeche :hp2.Oeffnen:ehp2., um das Spiel aus der Datei zu laden.
:p.:link reftype=hd res=4163.Allgemeine Hilfe:elink.

.*--------------------------------------------------------------*\
.*  save dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4210 scroll=none titlebar=yes nosearch.Speichern unter
:ol compact.
:li.Waehle den Pfeil nach unten rechts neben der Liste Laufwerk, um alle Laufwerke deines Systems anzuzeigen.
:li.Waehle ein Laufwerk aus der Liste Laufwerk.
:li.Waehle ein Verzeichnis aus der Liste Verzeichnis.
:li.Tippe den Namen der zu speichernden Datei in das Feld Dateiname und waehle die Schaltflaeche :hp2.Speichern:ehp2..
:eol.
:p.Fuer spezielle Hilfe waehle unten ein Thema.
:dl compact tsize=22.
:dt.:link reftype=hd res=26501.Dateiname:elink.
:dd.
:dt.:link reftype=hd res=26502.Dateityp:elink.
:dd.
:dt.:link reftype=hd res=26503.Laufwerk:elink.
:dd.
:dt.:link reftype=hd res=26504.Datei:elink.
:dd.
:dt.:link reftype=hd res=26505.Verzeichnis:elink.
:dd.
:dt.:link reftype=hd res=26506.Speichern:elink.
:dd.
:edl.

:h1 hide res=26501 nosearch.Dateiname
:p.Tippe den Namen der zu speichernden Datei in das Feld Dateiname und waehle die Schaltflaeche :hp2.Speichern:ehp2..
:p.:link reftype=hd res=4210.Allgemeine Hilfe:elink.

:h1 hide res=26502 nosearch.Dateityp
:p.Waehle den Pfeil nach unten rechts neben dem Feld Dateityp, um die verfuegbaren Dateitypen anzuzeigen.
:p.:link reftype=hd res=4210.Allgemeine Hilfe:elink.

:h1 hide res=26503 nosearch.Laufwerk
:p.Die Liste Laufwerk zeigt die Laufwerke deines Systems. Waehle das Laufwerk, auf dem du die Datei speichern willst.
:p.:link reftype=hd res=4210.Allgemeine Hilfe:elink.

:h1 hide res=26504 nosearch.Datei
:p.Die Liste Datei zeigt alle Dateien im Verzeichnis, das du in der Liste Verzeichnis gewaehlt hast. Waehle eine Datei, um ihren Namen wiederzuverwenden.
:p.:link reftype=hd res=4210.Allgemeine Hilfe:elink.

:h1 hide res=26505 nosearch.Verzeichnis
:p.Die Liste Verzeichnis zeigt die Verzeichnisse des gewaehlten Laufwerks. Waehle ein Verzeichnis, um seine Dateien in der Liste Datei anzuzeigen.
:p.:link reftype=hd res=4210.Allgemeine Hilfe:elink.

:h1 hide res=26506 nosearch.Speichern
:p.Waehle die Schaltflaeche :hp2.Speichern:ehp2., um das Spiel in der Datei auf dem gewaehlten Laufwerk und im gewaehlten Verzeichnis unter dem angegebenen Dateinamen zu speichern.
:p.:link reftype=hd res=4210.Allgemeine Hilfe:elink.

.*--------------------------------------------------------------*\
.*  Pull-down help for the save choices
.*--------------------------------------------------------------*/
:h1 hide res=4192 id=A4192 nosearch.Speichern
:p.Mit :hp2.Speichern:ehp2. speicherst du das laufende Spiel. Nachdem das Spiel in einer Datei gespeichert ist, steht der Dateiname im Fenstertitel.

:h1 hide res=4208 id=A4208 nosearch.Speichern unter
:p.Mit :hp2.Speichern unter:ehp2. gibst du einem neuen Spiel einen Namen und speicherst es, oder du speicherst ein Spiel unter anderem Namen, in einem anderen Verzeichnis oder auf einem anderen Datentraeger.

:euserdoc.
