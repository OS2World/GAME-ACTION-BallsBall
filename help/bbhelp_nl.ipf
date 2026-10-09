.* BallsBall help (nl) - generated; texts per language, same panel ids
:userdoc.
:title.BallsBall Help

.*--------------------------------------------------------------*\
.*  Main window extended help panel (PANEL_MAIN)
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.Over BallsBall
:i1 id=aboutMain.Over BallsBall
:p.BallsBall is een Presentation Manager-spel. Met de loper bouw je nieuwe paden over het veld, terwijl ballen rondstuiteren en jagers over de paden patrouilleren.
:p.Dit is een gemoderniseerde versie van het open-sourcespel. Het is gebouwd met Open Watcom, bevat Engels, Nederlands, Spaans, Duits, Frans en Italiaans in een enkel programma en schaalt het spelvenster naar minstens 1024x768 als het bureaublad dat toelaat (de cellen blijven vierkant).
:p.Kies een onderwerp&colon.
:ul compact.
:li.:link reftype=hd res=1.Spelregels:elink.
:li.:link reftype=hd res=2.Licentie:elink.
:li.:link reftype=hd res=3.Muis:elink.
:eul.

.*--------------------------------------------------------------*\
.*  Rules, license, mouse
.*--------------------------------------------------------------*/
:h1 res=1.Spelregels
:i1 id=Rules.Spelregels
:p.De regels zijn eenvoudig. Met de loper maak je nieuwe paden over het veld. Je bestuurt hem met de :link reftype=hd res=2950.pijltjestoetsen:elink. (links, rechts, omhoog en omlaag) of met de :link reftype=hd res=3.muis:elink.. Je krijgt een punt voor elke toegevoegde cel. Cellen worden toegevoegd als de loper terugkeert op een oud pad.
:p.Ballen bewegen over het veld. Raakt een bal een nieuw pad voordat de loper een oud pad heeft bereikt, dan valt het nieuwe pad weg. Je verliest een punt voor elke vernietigde cel en 50 punten bij een botsing.
:p.Lukt het je een bal te stoppen, dan krijg je 100 punten. Dat is moeilijk maar mogelijk: je kunt bijvoorbeeld zijn veld beperken. Onder bepaalde omstandigheden loopt een bal ook vast. Welke? Probeer het maar!
:p.Jagers bewegen langs de paden. Ze gaan alleen vooruit; kan dat niet, dan keren ze om, en bij een keuze kiezen ze willekeurig een richting. Een botsing met een jager kost 50 punten.
:p.Het spel heeft 11 niveaus. Het aantal ballen en jagers is het niveau plus 4. Haal je binnen 3 minuten 2/3 van de punten op het veld, dan ga je naar het volgende niveau, anders heb je verloren. Haal je 4/5 in minder dan 3 minuten, dan ga je eerder naar het volgende niveau. Ben je al op niveau 11, dan heb je gewonnen.
:p.De tekstregel toont je score. 4/5 is 100%, 2/3 is 84%.
:p.Kom je na het spel op plaats 10 of hoger, dan komt je naam in de Eregalerij.

:h1 res=2.Licentie
:i1 id=License.Licentie
:p.BallsBall is vrije software, uitgegeven onder de GNU General Public License, versie 3 (zie LICENSE.txt). Het programma wordt geleverd "zoals het is", zonder enige garantie.
:p.Oorspronkelijk spel van Dmitry Ivanov.
:p.Verspreid het programma samen met deze bestanden&colon.
:ul compact.
:li.LICENSE.txt
:li.readme.txt
:li.bbhelp_nl.hlp
:eul.

:h1 res=3.Muis
:i1 id=Mouse.Muis
:p.Het venster is, vanuit de loper gezien, verdeeld in vier delen&colon. links, rechts, boven en onder.
:artwork align=left name='mous.bmp'.
:p.Klik in een van deze delen en de loper gaat respectievelijk naar links, naar rechts, omhoog of omlaag.

.*--------------------------------------------------------------*\
.*  Game menu
.*--------------------------------------------------------------*/
:h1 res=2210 name=PANEL_FILE.Menu Spel
:i1 id=File.Menu Spel
:p.Het menu :hp2.Spel:ehp2. bevat de opdrachten om spellen te starten, te laden en op te slaan, het spel te pauzeren, de eregalerij te tonen en BallsBall af te sluiten. De volgende opdrachten staan in het menu :hp2.Spel:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Nieuw
:pd.Start een nieuw naamloos spel.
:pt.Openen
:pd.Laadt een opgeslagen spel uit een bestand.
:pt.Opslaan
:pd.Slaat het spel op in het huidige bestand.
:pt.Opslaan als
:pd.Slaat het spel op in een bestand met een nieuwe naam.
:pt.Pauze Spel
:pd.Pauzeert het spel of zet het voort.
:pt.Eregalerij
:pd.Toont de eregalerij.
:pt.Afsluiten
:pd.Sluit BallsBall af.
:eparml.

:h1 res=2220 name=PANEL_FILENEW.Nieuw
:i2 refid=File.Nieuw
:p.Gebruik :hp2.Nieuw:ehp2. om een nieuw spel te starten. Score en niveau worden op nul gezet en de titelbalk toont het spel als naamloos.

:h1 res=2230 name=PANEL_FILEOPEN.Openen
:i2 refid=File.Openen
:p.Gebruik :hp2.Openen:ehp2. om een opgeslagen spel uit een bestand te laden. Een dialoogvenster toont de bestanden met de extensie .bbg in de huidige map.

:h1 res=2240 name=PANEL_FILESAVE.Opslaan
:i2 refid=File.Opslaan
:p.Gebruik :hp2.Opslaan:ehp2. om het spel op te slaan in het huidige bestand. Heeft het spel nog geen naam, dan verschijnt eerst het dialoogvenster :hp2.Opslaan als:ehp2..

:h1 res=2250 name=PANEL_FILESAVEAS.Opslaan als
:i2 refid=File.Opslaan als
:p.Gebruik :hp2.Opslaan als:ehp2. om het spel een naam te geven en in een nieuw bestand op te slaan. Een dialoogvenster vraagt om de nieuwe bestandsnaam.

:h1 res=2270 name=PANEL_DIRECTION_START.Pauze Spel
:i2 refid=File.Pauze Spel
:p.Gebruik :hp2.Pauze Spel:ehp2. om het spel te starten, of te stoppen als het al loopt. Enter en spatie doen hetzelfde.

:h1 res=2260 name=PANEL_HIGHSCORES.Eregalerij
:i2 refid=File.Eregalerij
:p.Gebruik :hp2.Eregalerij:ehp2. om een dialoogvenster met de huidige eregalerij te tonen.

:h1 res=2290 name=PANEL_FILEEXIT.Afsluiten
:i2 refid=File.Afsluiten
:p.Je sluit BallsBall af met :hp2.Afsluiten:ehp2., of met de toetsen Esc of Alt+F4.

.*--------------------------------------------------------------*\
.*  Options menu
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Menu Instellingen
:i1 id=Settings.Menu Instellingen
:p.Het menu :hp2.Instellingen:ehp2. bevat de opdrachten om de instellingen van BallsBall te wijzigen. De volgende opdrachten staan in het menu :hp2.Instellingen:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Geluid
:pd.Zet het geluid aan of uit.
:pt.Weergave
:pd.Schakelt tussen de 2D- en 3D-weergave van de cellen.
:pt.Niveau
:pd.Stelt het gewenste niveau in, van 0 tot 11.
:pt.Visuele instellingen
:pd.Toont een dialoogvenster met alle visuele instellingen.
:pt.Taal
:pd.Kiest de taal van de interface&colon. Engels, Nederlands, Spaans, Duits, Frans of Italiaans. De help volgt de gekozen taal.
:pt.Achtergrond
:pd.Laat het spel doorlopen terwijl het venster niet actief is (Ctrl+B).
:pt.Frame besturing
:pd.Verbergt of toont titelbalk, systeemmenu en menubalk, zodat alleen het speelveld overblijft (Ctrl+F).
:pt.Instellingen bewaren bij afsluiten
:pd.Indien aangevinkt (standaard) worden de instellingen bewaard bij het afsluiten. Indien niet aangevinkt worden gewijzigde instellingen niet bewaard.
:eparml.

:h1 res=2305 name=PANEL_SOUND.Geluid
:i2 refid=Settings.Geluid
:p.Gebruik de opdrachten van :hp2.Geluid:ehp2. om het geluid aan of uit te zetten.

:h1 res=2302 name=PANEL_STYLE.Weergave
:i2 refid=Settings.Weergave
:p.Gebruik de opdrachten van :hp2.Weergave:ehp2., of de toets F2, om de weergave van de cellen te wijzigen.

:h1 res=2308 name=PANEL_LEVEL.Niveau
:i2 refid=Settings.Niveau
:p.Gebruik de opdrachten van :hp2.Niveau:ehp2. om het gewenste niveau tussen 0 en 11 in te stellen.

:h1 res=2314 name=PANEL_SETTINGS_ALL.Visuele instellingen
:i2 refid=Settings.Visuele instellingen
:p.Gebruik :hp2.Visuele instellingen:ehp2. om het instellingenvenster te openen. Daarin wijzig je de kleuren van de ballen en van de verschillende soorten cellen, de grootte van de cellen en het venster, de weergave, het geluid en de manier van bewegen na een vangst. Je kunt ook de standaardinstellingen herstellen.
:p.Het spelvenster wordt automatisch vergroot, als het bureaublad dat toelaat, zodat het veld minstens 1024x768 bereikt. De cellen blijven vierkant en het venster wordt nooit groter dan het bureaublad.

.*--------------------------------------------------------------*\
.*  Help menu
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Menu Help
:i1 id=Help.Menu Help
:p.Het menu :hp2.Help:ehp2. bevat de opdrachten om de help op te roepen. De volgende opdrachten staan in het menu :hp2.Help:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Help-index
:pd.Toont de lijst met alle helponderwerpen.
:pt.Help
:pd.Algemene informatie over het spel, de regels en de licentie.
:pt.Help gebruiken
:pd.Toont de systeemhelp over het gebruik van help.
:pt.Help bij toetsen
:pd.Toont de sneltoetsen.
:pt.About
:pd.Toont de versie en het copyright van het spel.
:eparml.

:h1 res=2920 name=PANEL_HELPINDEX.Help-index
:i2 refid=Help.Help-index
:p.Hier staat de lijst met alle helponderwerpen. Kies een onderwerp om er informatie over te zien.

:h1 res=2930 name=PANEL_HELPGENERAL.Help
:i2 refid=Help.Help
:p.Dit is het venster Algemene help, met de belangrijkste helpinformatie.

:h1 res=2940 name=PANEL_HELPUSINGHELP.Help gebruiken
:i2 refid=Help.Help gebruiken
:p.Hier staat de systeeminformatie over het gebruik van help.

:h1 res=2950 name=PANEL_HELPKEYS.Toetsen
:i2 refid=Help.Toetsen
:p.Je kunt de volgende sneltoetsen gebruiken&colon.
:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.toont de help.
:pt.:hp8.F2:ehp8.
:pd.zet de 2D-weergave van de cellen.
:pt.:hp8.F3:ehp8.
:pd.sluit het spel af.
:pt.:hp8.Enter:ehp8.
:pd.start het spel, of stopt het als het al loopt.
:pt.:hp8.Space:ehp8.
:pd.hetzelfde als Enter.
:pt.:hp8.Left arrow:ehp8.
:pd.de loper gaat naar links.
:pt.:hp8.Right arrow:ehp8.
:pd.de loper gaat naar rechts.
:pt.:hp8.Up arrow:ehp8.
:pd.de loper gaat omhoog.
:pt.:hp8.Down arrow:ehp8.
:pd.de loper gaat omlaag.
:pt.:hp8.Elke andere toets:ehp8.
:pd.de loper blijft staan.
:pt.:hp8.Esc:ehp8.
:pd.sluit het spel af.
:pt.:hp8.Alt+F4:ehp8.
:pd.sluit het spel af.
:pt.:hp8.Ctrl+N:ehp8.
:pd.start een nieuw spel.
:pt.:hp8.Ctrl+H:ehp8.
:pd.toont de eregalerij.
:pt.:hp8.Ctrl+P:ehp8.
:pd.pauzeert het spel of zet het voort.
:pt.:hp8.Ctrl+B:ehp8.
:pd.zet Achtergrond aan of uit.
:pt.:hp8.Ctrl+F:ehp8.
:pd.verbergt of toont de framebesturing.
:eparml.

:h1 res=2970 name=PANEL_HELPPRODUCTINFO.About
:i2 refid=Help.About
:p.Dit dialoogvenster toont informatie over het spel, zoals het versienummer, de copyrightmelding en een afbeelding.

:h1 hide res=3100 name=PANEL_PRODUCTINFODLG.About
:p.Dit dialoogvenster toont informatie over het spel, zoals het versienummer, de copyrightmelding en een afbeelding.

.*--------------------------------------------------------------*\
.*  load dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4163 scroll=none titlebar=yes nosearch.Openen
:ol compact.
:li.Kies de pijl omlaag rechts van de lijst Station om alle stations van je systeem te tonen.
:li.Kies een station in de lijst Station.
:li.Kies een map in de lijst Map.
:li.Kies een bestandsnaam in de lijst Bestand, of typ een bestandsnaam, en kies de knop :hp2.Openen:ehp2..
:eol.
:p.Kies hieronder een onderwerp voor specifieke help.
:dl compact tsize=22.
:dt.:link reftype=hd res=20501.Bestandsnaam:elink.
:dd.
:dt.:link reftype=hd res=20502.Bestandstype:elink.
:dd.
:dt.:link reftype=hd res=20503.Station:elink.
:dd.
:dt.:link reftype=hd res=20504.Bestand:elink.
:dd.
:dt.:link reftype=hd res=20505.Map:elink.
:dd.
:dt.:link reftype=hd res=20506.Openen:elink.
:dd.
:edl.

:h1 hide res=20501 nosearch.Bestandsnaam
:p.Typ de naam van het bestand dat je wilt laden in het veld Bestandsnaam en kies de knop :hp2.Openen:ehp2..
:p.:link reftype=hd res=4163.Algemene help:elink.

:h1 hide res=20502 nosearch.Bestandstype
:p.Kies de pijl omlaag rechts van het veld Bestandstype om de beschikbare bestandstypen te tonen.
:p.:link reftype=hd res=4163.Algemene help:elink.

:h1 hide res=20503 nosearch.Station
:p.De lijst Station toont de stations van je systeem. Kies het station dat het bestand bevat.
:p.:link reftype=hd res=4163.Algemene help:elink.

:h1 hide res=20504 nosearch.Bestand
:p.De lijst Bestand toont alle bestanden met de extensie .bbg in de map die je in de lijst Map hebt gekozen. Kies het bestand dat je wilt laden.
:p.:link reftype=hd res=4163.Algemene help:elink.

:h1 hide res=20505 nosearch.Map
:p.De lijst Map toont de mappen op het gekozen station. Kies een map om de bestanden daarvan in de lijst Bestand te tonen.
:p.:link reftype=hd res=4163.Algemene help:elink.

:h1 hide res=20506 nosearch.Openen
:p.Kies de knop :hp2.Openen:ehp2. om het spel uit het bestand te laden.
:p.:link reftype=hd res=4163.Algemene help:elink.

.*--------------------------------------------------------------*\
.*  save dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4210 scroll=none titlebar=yes nosearch.Opslaan als
:ol compact.
:li.Kies de pijl omlaag rechts van de lijst Station om alle stations van je systeem te tonen.
:li.Kies een station in de lijst Station.
:li.Kies een map in de lijst Map.
:li.Typ de naam van het bestand dat je wilt opslaan in het veld Bestandsnaam en kies de knop :hp2.Opslaan:ehp2..
:eol.
:p.Kies hieronder een onderwerp voor specifieke help.
:dl compact tsize=22.
:dt.:link reftype=hd res=26501.Bestandsnaam:elink.
:dd.
:dt.:link reftype=hd res=26502.Bestandstype:elink.
:dd.
:dt.:link reftype=hd res=26503.Station:elink.
:dd.
:dt.:link reftype=hd res=26504.Bestand:elink.
:dd.
:dt.:link reftype=hd res=26505.Map:elink.
:dd.
:dt.:link reftype=hd res=26506.Opslaan:elink.
:dd.
:edl.

:h1 hide res=26501 nosearch.Bestandsnaam
:p.Typ de naam van het bestand dat je wilt opslaan in het veld Bestandsnaam en kies de knop :hp2.Opslaan:ehp2..
:p.:link reftype=hd res=4210.Algemene help:elink.

:h1 hide res=26502 nosearch.Bestandstype
:p.Kies de pijl omlaag rechts van het veld Bestandstype om de beschikbare bestandstypen te tonen.
:p.:link reftype=hd res=4210.Algemene help:elink.

:h1 hide res=26503 nosearch.Station
:p.De lijst Station toont de stations van je systeem. Kies het station waarop je het bestand wilt opslaan.
:p.:link reftype=hd res=4210.Algemene help:elink.

:h1 hide res=26504 nosearch.Bestand
:p.De lijst Bestand toont alle bestanden in de map die je in de lijst Map hebt gekozen. Kies een bestand om de naam opnieuw te gebruiken.
:p.:link reftype=hd res=4210.Algemene help:elink.

:h1 hide res=26505 nosearch.Map
:p.De lijst Map toont de mappen op het gekozen station. Kies een map om de bestanden daarvan in de lijst Bestand te tonen.
:p.:link reftype=hd res=4210.Algemene help:elink.

:h1 hide res=26506 nosearch.Opslaan
:p.Kies de knop :hp2.Opslaan:ehp2. om het spel op te slaan in het bestand, op het gekozen station en in de gekozen map, met de opgegeven bestandsnaam.
:p.:link reftype=hd res=4210.Algemene help:elink.

.*--------------------------------------------------------------*\
.*  Pull-down help for the save choices
.*--------------------------------------------------------------*/
:h1 hide res=4192 id=A4192 nosearch.Opslaan
:p.Gebruik :hp2.Opslaan:ehp2. om het spel dat je speelt op te slaan. Nadat het spel in een bestand is opgeslagen, wordt de bestandsnaam in de venstertitel getoond.

:h1 hide res=4208 id=A4208 nosearch.Opslaan als
:p.Gebruik :hp2.Opslaan als:ehp2. om een nieuw spel een naam te geven en op te slaan, of om een spel onder een andere naam, in een andere map of op een andere schijf op te slaan.

:euserdoc.
