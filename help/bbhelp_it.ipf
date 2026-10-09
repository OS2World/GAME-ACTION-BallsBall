.* BallsBall help (it) - generated; texts per language, same panel ids
:userdoc.
:title.Aiuto di BallsBall

.*--------------------------------------------------------------*\
.*  Main window extended help panel (PANEL_MAIN)
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.Informazioni su BallsBall
:i1 id=aboutMain.Informazioni su BallsBall
:p.BallsBall e un gioco per Presentation Manager. Con il corridore costruisci nuovi percorsi sul campo, mentre le palle rimbalzano e i cacciatori pattugliano i percorsi.
:p.Questa e una versione modernizzata del gioco open source. E compilata con Open Watcom, contiene inglese, olandese, spagnolo, tedesco, francese e italiano in un unico eseguibile e ingrandisce la finestra di gioco ad almeno 1024x768 se il desktop lo permette (le celle restano quadrate).
:p.Scegli un argomento&colon.
:ul compact.
:li.:link reftype=hd res=1.Regole:elink.
:li.:link reftype=hd res=2.Licenza:elink.
:li.:link reftype=hd res=3.Mouse:elink.
:eul.

.*--------------------------------------------------------------*\
.*  Rules, license, mouse
.*--------------------------------------------------------------*/
:h1 res=1.Regole
:i1 id=Rules.Regole
:p.Le regole sono semplici. Con il corridore crei nuovi percorsi sul campo. Lo guidi con i :link reftype=hd res=2950.tasti freccia:elink. (sinistra, destra, su e giu) o con il :link reftype=hd res=3.mouse:elink.. Ricevi un punto per ogni cella aggiunta. Le celle vengono aggiunte quando il corridore torna su un vecchio percorso.
:p.Le palle si muovono sul campo. Se una palla tocca un nuovo percorso prima che il corridore abbia raggiunto un vecchio percorso, il nuovo percorso cade. Perdi un punto per ogni cella distrutta e 50 punti per una collisione.
:p.Se riesci a fermare una palla ricevi 100 punti. E difficile ma possibile: per esempio puoi limitarne il campo. In certe condizioni una palla si incastra anche. Quali? Prova!
:p.I cacciatori si muovono sui percorsi. Vanno solo avanti; se non e possibile fanno dietrofront, e quando c'e una scelta prendono una direzione a caso. Una collisione con un cacciatore costa 50 punti.
:p.Il gioco ha 11 livelli. Il numero di palle e cacciatori e il livello piu 4. Se raccogli 2/3 dei punti del campo entro 3 minuti passi al livello successivo, altrimenti hai perso. Se raccogli 4/5 in meno di 3 minuti passi prima al livello successivo. Se sei gia al livello 11, hai vinto.
:p.La riga di testo mostra il tuo punteggio. 4/5 e il 100%, 2/3 e l'84%.
:p.Se dopo la partita arrivi al 10 posto o meglio, il tuo nome viene inserito nei Record.

:h1 res=2.Licenza
:i1 id=License.Licenza
:p.BallsBall e software libero, rilasciato sotto la GNU General Public License, versione 3 (vedi LICENSE.txt). Il programma e fornito "cosi com'e", senza garanzie di alcun tipo.
:p.Gioco originale di Dmitry Ivanov.
:p.Distribuisci il programma insieme a questi file&colon.
:ul compact.
:li.LICENSE.txt
:li.readme.txt
:li.bbhelp_it.hlp
:eul.

:h1 res=3.Mouse
:i1 id=Mouse.Mouse
:p.L'interno della finestra e diviso, rispetto al corridore, in quattro parti&colon. sinistra, destra, alto e basso.
:artwork align=left name='mous.bmp'.
:p.Fai clic in una di queste parti e il corridore si muove rispettivamente a sinistra, a destra, in alto o in basso.

.*--------------------------------------------------------------*\
.*  Game menu
.*--------------------------------------------------------------*/
:h1 res=2210 name=PANEL_FILE.Menu Gioco
:i1 id=File.Menu Gioco
:p.Il menu :hp2.Gioco:ehp2. contiene i comandi per avviare, aprire e salvare partite, mettere in pausa il gioco, mostrare i record e uscire da BallsBall. I comandi seguenti compaiono nel menu :hp2.Gioco:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Nuova partita
:pd.Avvia una nuova partita senza nome.
:pt.Apri
:pd.Apre una partita salvata da un file.
:pt.Salva
:pd.Salva la partita nel file corrente.
:pt.Salva come
:pd.Salva la partita in un file con un nuovo nome.
:pt.Pausa Gioco
:pd.Mette in pausa il gioco o lo riprende.
:pt.Record
:pd.Mostra i record.
:pt.Esci
:pd.Esce da BallsBall.
:eparml.

:h1 res=2220 name=PANEL_FILENEW.Nuova partita
:i2 refid=File.Nuova partita
:p.Usa :hp2.Nuova partita:ehp2. per avviare una nuova partita. Punteggio e livello tornano a zero e la barra del titolo mostra la partita senza nome.

:h1 res=2230 name=PANEL_FILEOPEN.Apri
:i2 refid=File.Apri
:p.Usa :hp2.Apri:ehp2. per aprire una partita salvata da un file. Una finestra di dialogo mostra i file con estensione .bbg nella directory corrente.

:h1 res=2240 name=PANEL_FILESAVE.Salva
:i2 refid=File.Salva
:p.Usa :hp2.Salva:ehp2. per salvare la partita nel file corrente. Se la partita non ha ancora un nome, compare prima la finestra :hp2.Salva come:ehp2..

:h1 res=2250 name=PANEL_FILESAVEAS.Salva come
:i2 refid=File.Salva come
:p.Usa :hp2.Salva come:ehp2. per dare un nome alla partita e salvarla in un nuovo file. Una finestra di dialogo chiede il nuovo nome del file.

:h1 res=2270 name=PANEL_DIRECTION_START.Pausa Gioco
:i2 refid=File.Pausa Gioco
:p.Usa :hp2.Pausa Gioco:ehp2. per avviare il gioco o fermarlo se e gia in corso. Invio e Spazio fanno lo stesso.

:h1 res=2260 name=PANEL_HIGHSCORES.Record
:i2 refid=File.Record
:p.Usa :hp2.Record:ehp2. per mostrare una finestra con i record attuali.

:h1 res=2290 name=PANEL_FILEEXIT.Esci
:i2 refid=File.Esci
:p.Esci da BallsBall con :hp2.Esci:ehp2., o premendo Esc o Alt+F4.

.*--------------------------------------------------------------*\
.*  Options menu
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Menu Opzioni
:i1 id=Settings.Menu Opzioni
:p.Il menu :hp2.Opzioni:ehp2. contiene i comandi per modificare le impostazioni di BallsBall. I comandi seguenti compaiono nel menu :hp2.Opzioni:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Suono
:pd.Attiva o disattiva il suono.
:pt.Stile
:pd.Passa tra lo stile 2D e 3D delle celle.
:pt.Livello
:pd.Imposta il livello desiderato, da 0 a 11.
:pt.Impostazioni visive
:pd.Mostra una finestra con tutte le impostazioni visive.
:pt.Lingua
:pd.Seleziona la lingua dell'interfaccia&colon. inglese, olandese, spagnolo, tedesco, francese o italiano. L'aiuto segue la lingua scelta.
:pt.Sfondo Attivo
:pd.Lascia proseguire il gioco mentre la sua finestra non e attiva (Ctrl+B).
:pt.Controlli Cornice
:pd.Nasconde o mostra la barra del titolo, il menu di sistema e la barra dei menu, lasciando solo l'area di gioco (Ctrl+F).
:pt.Salva impostazioni all'uscita
:pd.Se selezionato (predefinito), le impostazioni vengono salvate all'uscita dal gioco. Altrimenti le impostazioni modificate non vengono salvate.
:eparml.

:h1 res=2305 name=PANEL_SOUND.Suono
:i2 refid=Settings.Suono
:p.Usa i comandi di :hp2.Suono:ehp2. per attivare o disattivare il suono.

:h1 res=2302 name=PANEL_STYLE.Stile
:i2 refid=Settings.Stile
:p.Usa i comandi di :hp2.Stile:ehp2., o il tasto F2, per cambiare lo stile delle celle.

:h1 res=2308 name=PANEL_LEVEL.Livello
:i2 refid=Settings.Livello
:p.Usa i comandi di :hp2.Livello:ehp2. per impostare il livello desiderato, tra 0 e 11.

:h1 res=2314 name=PANEL_SETTINGS_ALL.Impostazioni visive
:i2 refid=Settings.Impostazioni visive
:p.Usa :hp2.Impostazioni visive:ehp2. per aprire la finestra delle impostazioni. Qui puoi cambiare i colori delle palle e dei diversi tipi di celle, la dimensione delle celle e della finestra, lo stile, il suono e il modo di muoversi dopo una cattura. Puoi anche ripristinare le impostazioni predefinite.
:p.La finestra di gioco viene ingrandita automaticamente, se il desktop lo permette, in modo che il campo raggiunga almeno 1024x768. Le celle restano quadrate e la finestra non e mai piu grande del desktop.

.*--------------------------------------------------------------*\
.*  Help menu
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Menu Aiuto
:i1 id=Help.Menu Aiuto
:p.Il menu :hp2.Aiuto:ehp2. contiene i comandi per richiamare l'aiuto. I comandi seguenti compaiono nel menu :hp2.Aiuto:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Indice aiuto
:pd.Mostra l'elenco di tutti gli argomenti di aiuto.
:pt.Aiuto generale
:pd.Informazioni generali sul gioco, sulle regole e sulla licenza.
:pt.Usare l'aiuto
:pd.Mostra l'aiuto di sistema sull'uso dell'aiuto.
:pt.Aiuto tasti
:pd.Mostra i tasti di scelta rapida.
:pt.About
:pd.Mostra la versione e il copyright del gioco.
:eparml.

:h1 res=2920 name=PANEL_HELPINDEX.Indice aiuto
:i2 refid=Help.Indice aiuto
:p.Qui e posto l'elenco di tutti gli argomenti di aiuto. Scegli un argomento per vederne le informazioni.

:h1 res=2930 name=PANEL_HELPGENERAL.Aiuto generale
:i2 refid=Help.Aiuto generale
:p.Questa e la finestra dell'Aiuto generale, con le informazioni principali.

:h1 res=2940 name=PANEL_HELPUSINGHELP.Usare l'aiuto
:i2 refid=Help.Usare l'aiuto
:p.Qui sono poste le informazioni di sistema sull'uso dell'aiuto.

:h1 res=2950 name=PANEL_HELPKEYS.Tasti
:i2 refid=Help.Tasti
:p.Puoi usare i seguenti tasti di scelta rapida&colon.
:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.mostra l'aiuto.
:pt.:hp8.F2:ehp8.
:pd.imposta lo stile 2D delle celle.
:pt.:hp8.F3:ehp8.
:pd.esce dal gioco.
:pt.:hp8.Enter:ehp8.
:pd.avvia il gioco, o lo ferma se e gia in corso.
:pt.:hp8.Space:ehp8.
:pd.come Invio.
:pt.:hp8.Left arrow:ehp8.
:pd.il corridore va a sinistra.
:pt.:hp8.Right arrow:ehp8.
:pd.il corridore va a destra.
:pt.:hp8.Up arrow:ehp8.
:pd.il corridore va in alto.
:pt.:hp8.Down arrow:ehp8.
:pd.il corridore va in basso.
:pt.:hp8.Qualsiasi altro tasto:ehp8.
:pd.il corridore si ferma.
:pt.:hp8.Esc:ehp8.
:pd.esce dal gioco.
:pt.:hp8.Alt+F4:ehp8.
:pd.esce dal gioco.
:pt.:hp8.Ctrl+N:ehp8.
:pd.avvia una nuova partita.
:pt.:hp8.Ctrl+H:ehp8.
:pd.mostra i record.
:pt.:hp8.Ctrl+P:ehp8.
:pd.mette in pausa il gioco o lo riprende.
:pt.:hp8.Ctrl+B:ehp8.
:pd.attiva o disattiva Sfondo Attivo.
:pt.:hp8.Ctrl+F:ehp8.
:pd.nasconde o mostra i controlli della cornice.
:eparml.

:h1 res=2970 name=PANEL_HELPPRODUCTINFO.About
:i2 refid=Help.About
:p.Questa finestra mostra informazioni sul gioco, come il numero di versione, l'avviso di copyright e un'immagine.

:h1 hide res=3100 name=PANEL_PRODUCTINFODLG.About
:p.Questa finestra mostra informazioni sul gioco, come il numero di versione, l'avviso di copyright e un'immagine.

.*--------------------------------------------------------------*\
.*  load dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4163 scroll=none titlebar=yes nosearch.Apri
:ol compact.
:li.Seleziona la freccia in basso a destra dell'elenco Unita per mostrare tutte le unita del sistema.
:li.Scegli un'unita dall'elenco Unita.
:li.Scegli una directory dall'elenco Directory.
:li.Scegli un nome dall'elenco File, o digita un nome di file, e seleziona il pulsante :hp2.Apri:ehp2..
:eol.
:p.Per un aiuto specifico, scegli un argomento qui sotto.
:dl compact tsize=22.
:dt.:link reftype=hd res=20501.Nome file:elink.
:dd.
:dt.:link reftype=hd res=20502.Tipo di file:elink.
:dd.
:dt.:link reftype=hd res=20503.Unita:elink.
:dd.
:dt.:link reftype=hd res=20504.File:elink.
:dd.
:dt.:link reftype=hd res=20505.Directory:elink.
:dd.
:dt.:link reftype=hd res=20506.Apri:elink.
:dd.
:edl.

:h1 hide res=20501 nosearch.Nome file
:p.Digita il nome del file da aprire nel campo Nome file e seleziona il pulsante :hp2.Apri:ehp2..
:p.:link reftype=hd res=4163.Aiuto generale:elink.

:h1 hide res=20502 nosearch.Tipo di file
:p.Seleziona la freccia in basso a destra del campo Tipo di file per mostrare i tipi di file disponibili.
:p.:link reftype=hd res=4163.Aiuto generale:elink.

:h1 hide res=20503 nosearch.Unita
:p.L'elenco Unita mostra le unita del sistema. Scegli l'unita che contiene il file.
:p.:link reftype=hd res=4163.Aiuto generale:elink.

:h1 hide res=20504 nosearch.File
:p.L'elenco File mostra tutti i file con estensione .bbg nella directory scelta nell'elenco Directory. Scegli il file da aprire.
:p.:link reftype=hd res=4163.Aiuto generale:elink.

:h1 hide res=20505 nosearch.Directory
:p.L'elenco Directory mostra le directory dell'unita scelta. Scegli una directory per mostrarne i file nell'elenco File.
:p.:link reftype=hd res=4163.Aiuto generale:elink.

:h1 hide res=20506 nosearch.Apri
:p.Seleziona il pulsante :hp2.Apri:ehp2. per aprire la partita dal file.
:p.:link reftype=hd res=4163.Aiuto generale:elink.

.*--------------------------------------------------------------*\
.*  save dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4210 scroll=none titlebar=yes nosearch.Salva come
:ol compact.
:li.Seleziona la freccia in basso a destra dell'elenco Unita per mostrare tutte le unita del sistema.
:li.Scegli un'unita dall'elenco Unita.
:li.Scegli una directory dall'elenco Directory.
:li.Digita il nome del file da salvare nel campo Nome file e seleziona il pulsante :hp2.Salva:ehp2..
:eol.
:p.Per un aiuto specifico, scegli un argomento qui sotto.
:dl compact tsize=22.
:dt.:link reftype=hd res=26501.Nome file:elink.
:dd.
:dt.:link reftype=hd res=26502.Tipo di file:elink.
:dd.
:dt.:link reftype=hd res=26503.Unita:elink.
:dd.
:dt.:link reftype=hd res=26504.File:elink.
:dd.
:dt.:link reftype=hd res=26505.Directory:elink.
:dd.
:dt.:link reftype=hd res=26506.Salva:elink.
:dd.
:edl.

:h1 hide res=26501 nosearch.Nome file
:p.Digita il nome del file da salvare nel campo Nome file e seleziona il pulsante :hp2.Salva:ehp2..
:p.:link reftype=hd res=4210.Aiuto generale:elink.

:h1 hide res=26502 nosearch.Tipo di file
:p.Seleziona la freccia in basso a destra del campo Tipo di file per mostrare i tipi di file disponibili.
:p.:link reftype=hd res=4210.Aiuto generale:elink.

:h1 hide res=26503 nosearch.Unita
:p.L'elenco Unita mostra le unita del sistema. Scegli l'unita su cui salvare il file.
:p.:link reftype=hd res=4210.Aiuto generale:elink.

:h1 hide res=26504 nosearch.File
:p.L'elenco File mostra tutti i file nella directory scelta nell'elenco Directory. Scegli un file per riutilizzarne il nome.
:p.:link reftype=hd res=4210.Aiuto generale:elink.

:h1 hide res=26505 nosearch.Directory
:p.L'elenco Directory mostra le directory dell'unita scelta. Scegli una directory per mostrarne i file nell'elenco File.
:p.:link reftype=hd res=4210.Aiuto generale:elink.

:h1 hide res=26506 nosearch.Salva
:p.Seleziona il pulsante :hp2.Salva:ehp2. per salvare la partita nel file, nell'unita e nella directory scelte, con il nome indicato.
:p.:link reftype=hd res=4210.Aiuto generale:elink.

.*--------------------------------------------------------------*\
.*  Pull-down help for the save choices
.*--------------------------------------------------------------*/
:h1 hide res=4192 id=A4192 nosearch.Salva
:p.Usa :hp2.Salva:ehp2. per salvare la partita in corso. Dopo che la partita e salvata in un file, il nome del file compare nel titolo della finestra.

:h1 hide res=4208 id=A4208 nosearch.Salva come
:p.Usa :hp2.Salva come:ehp2. per dare un nome a una nuova partita e salvarla, o per salvare una partita con un altro nome, in un'altra directory o su un altro disco.

:euserdoc.
