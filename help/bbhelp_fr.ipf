.* BallsBall help (fr) - generated; texts per language, same panel ids
:userdoc.
:title.Aide de BallsBall

.*--------------------------------------------------------------*\
.*  Main window extended help panel (PANEL_MAIN)
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.A propos de BallsBall
:i1 id=aboutMain.A propos de BallsBall
:p.BallsBall est un jeu Presentation Manager. Avec le coureur, vous construisez de nouveaux chemins sur le terrain, pendant que des balles rebondissent et que des chasseurs patrouillent sur les chemins.
:p.Ceci est une version modernisee du jeu open source. Elle est compilee avec Open Watcom, contient l'anglais, le neerlandais, l'espagnol, l'allemand, le francais et l'italien dans un seul executable et agrandit la fenetre de jeu a au moins 1024x768 si le bureau le permet (les cases restent carrees).
:p.Choisissez un sujet&colon.
:ul compact.
:li.:link reftype=hd res=1.Regles:elink.
:li.:link reftype=hd res=2.Licence:elink.
:li.:link reftype=hd res=3.Souris:elink.
:eul.

.*--------------------------------------------------------------*\
.*  Rules, license, mouse
.*--------------------------------------------------------------*/
:h1 res=1.Regles
:i1 id=Rules.Regles
:p.Les regles sont simples. Avec le coureur, vous creez de nouveaux chemins sur le terrain. Vous le dirigez avec les :link reftype=hd res=2950.touches fleches:elink. (gauche, droite, haut et bas) ou avec la :link reftype=hd res=3.souris:elink.. Vous gagnez un point pour chaque case ajoutee. Les cases sont ajoutees quand le coureur revient sur un ancien chemin.
:p.Les balles se deplacent sur le terrain. Si une balle touche un nouveau chemin avant que le coureur ait atteint un ancien chemin, le nouveau chemin tombe. Vous perdez un point par case detruite et 50 points lors d'une collision.
:p.Si vous arrivez a arreter une balle, vous recevez 100 points. C'est difficile mais possible : vous pouvez par exemple limiter son terrain. Dans certaines conditions, une balle se coince aussi. Lesquelles ? Essayez !
:p.Les chasseurs se deplacent sur les chemins. Ils ne vont que vers l'avant ; si c'est impossible, ils font demi-tour, et quand il y a un choix, ils prennent une direction au hasard. Une collision avec un chasseur coute 50 points.
:p.Le jeu comporte 11 niveaux. Le nombre de balles et de chasseurs est le niveau plus 4. Si vous recueillez 2/3 des points du terrain en 3 minutes, vous passez au niveau suivant, sinon vous avez perdu. Si vous recueillez 4/5 en moins de 3 minutes, vous passez plus tot au niveau suivant. Si vous etes deja au niveau 11, vous avez gagne.
:p.La ligne de texte affiche votre score. 4/5 font 100 %, 2/3 font 84 %.
:p.Si vous atteignez la place 10 ou mieux apres la partie, votre nom est inscrit dans les Records.

:h1 res=2.Licence
:i1 id=License.Licence
:p.BallsBall est un logiciel libre, publie sous la Licence Publique Generale GNU, version 3 (voir LICENSE.txt). Le programme est fourni "tel quel", sans garantie d'aucune sorte.
:p.Jeu original de Dmitry Ivanov.
:p.Veuillez distribuer le programme avec ces fichiers&colon.
:ul compact.
:li.LICENSE.txt
:li.readme.txt
:li.bbhelp_fr.hlp
:eul.

:h1 res=3.Souris
:i1 id=Mouse.Souris
:p.L'interieur de la fenetre est divise, par rapport au coureur, en quatre parties&colon. gauche, droite, haut et bas.
:artwork align=left name='mous.bmp'.
:p.Cliquez dans l'une de ces parties et le coureur va respectivement vers la gauche, vers la droite, vers le haut ou vers le bas.

.*--------------------------------------------------------------*\
.*  Game menu
.*--------------------------------------------------------------*/
:h1 res=2210 name=PANEL_FILE.Menu Partie
:i1 id=File.Menu Partie
:p.Le menu :hp2.Partie:ehp2. contient les commandes pour demarrer, charger et enregistrer des parties, mettre le jeu en pause, afficher les records et quitter BallsBall. Les commandes suivantes figurent dans le menu :hp2.Partie:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Nouvelle partie
:pd.Demarre une nouvelle partie sans nom.
:pt.Charger
:pd.Charge une partie enregistree depuis un fichier.
:pt.Enregistrer
:pd.Enregistre la partie dans le fichier actuel.
:pt.Enregistrer sous
:pd.Enregistre la partie dans un fichier avec un nouveau nom.
:pt.Pause Jeu
:pd.Met le jeu en pause ou le reprend.
:pt.Records
:pd.Affiche les records.
:pt.Quitter
:pd.Quitte BallsBall.
:eparml.

:h1 res=2220 name=PANEL_FILENEW.Nouvelle partie
:i2 refid=File.Nouvelle partie
:p.Utilisez :hp2.Nouvelle partie:ehp2. pour demarrer une nouvelle partie. Le score et le niveau sont remis a zero et la barre de titre affiche la partie sans nom.

:h1 res=2230 name=PANEL_FILEOPEN.Charger
:i2 refid=File.Charger
:p.Utilisez :hp2.Charger:ehp2. pour charger une partie enregistree depuis un fichier. Une boite de dialogue affiche les fichiers d'extension .bbg du repertoire actuel.

:h1 res=2240 name=PANEL_FILESAVE.Enregistrer
:i2 refid=File.Enregistrer
:p.Utilisez :hp2.Enregistrer:ehp2. pour enregistrer la partie dans le fichier actuel. Si la partie n'a pas encore de nom, la boite :hp2.Enregistrer sous:ehp2. apparait d'abord.

:h1 res=2250 name=PANEL_FILESAVEAS.Enregistrer sous
:i2 refid=File.Enregistrer sous
:p.Utilisez :hp2.Enregistrer sous:ehp2. pour nommer la partie et l'enregistrer dans un nouveau fichier. Une boite de dialogue demande le nouveau nom de fichier.

:h1 res=2270 name=PANEL_DIRECTION_START.Pause Jeu
:i2 refid=File.Pause Jeu
:p.Utilisez :hp2.Pause Jeu:ehp2. pour lancer le jeu, ou l'arreter s'il tourne deja. Entree et Espace font la meme chose.

:h1 res=2260 name=PANEL_HIGHSCORES.Records
:i2 refid=File.Records
:p.Utilisez :hp2.Records:ehp2. pour afficher une boite de dialogue avec les records actuels.

:h1 res=2290 name=PANEL_FILEEXIT.Quitter
:i2 refid=File.Quitter
:p.Vous quittez BallsBall avec :hp2.Quitter:ehp2., ou en appuyant sur Echap ou Alt+F4.

.*--------------------------------------------------------------*\
.*  Options menu
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Menu Options
:i1 id=Settings.Menu Options
:p.Le menu :hp2.Options:ehp2. contient les commandes pour modifier les parametres de BallsBall. Les commandes suivantes figurent dans le menu :hp2.Options:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Son
:pd.Active ou desactive le son.
:pt.Style
:pd.Bascule entre le style 2D et 3D des cases.
:pt.Niveau
:pd.Definit le niveau souhaite, de 0 a 11.
:pt.Parametres visuels
:pd.Affiche une boite de dialogue avec tous les parametres visuels.
:pt.Langue
:pd.Choisit la langue de l'interface&colon. anglais, neerlandais, espagnol, allemand, francais ou italien. L'aide suit la langue choisie.
:pt.Arriere-plan Actif
:pd.Laisse le jeu continuer pendant que sa fenetre n'est pas active (Ctrl+B).
:pt.Cadre
:pd.Masque ou affiche la barre de titre, le menu systeme et la barre de menus, ne laissant que la zone de jeu (Ctrl+F).
:pt.Enregistrer les parametres en quittant
:pd.Si coche (par defaut), les parametres sont enregistres a la sortie du jeu. Sinon, les parametres modifies ne sont pas enregistres.
:eparml.

:h1 res=2305 name=PANEL_SOUND.Son
:i2 refid=Settings.Son
:p.Utilisez les commandes de :hp2.Son:ehp2. pour activer ou desactiver le son.

:h1 res=2302 name=PANEL_STYLE.Style
:i2 refid=Settings.Style
:p.Utilisez les commandes de :hp2.Style:ehp2., ou la touche F2, pour changer le style des cases.

:h1 res=2308 name=PANEL_LEVEL.Niveau
:i2 refid=Settings.Niveau
:p.Utilisez les commandes de :hp2.Niveau:ehp2. pour definir le niveau souhaite, entre 0 et 11.

:h1 res=2314 name=PANEL_SETTINGS_ALL.Parametres visuels
:i2 refid=Settings.Parametres visuels
:p.Utilisez :hp2.Parametres visuels:ehp2. pour ouvrir la boite de dialogue des parametres. Vous y changez les couleurs des balles et des differents types de cases, la taille des cases et de la fenetre, le style, le son et le mode de deplacement apres une capture. Vous pouvez aussi restaurer les parametres par defaut.
:p.La fenetre de jeu est agrandie automatiquement, si le bureau le permet, pour que le terrain atteigne au moins 1024x768. Les cases restent carrees et la fenetre n'est jamais plus grande que le bureau.

.*--------------------------------------------------------------*\
.*  Help menu
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Menu Aide
:i1 id=Help.Menu Aide
:p.Le menu :hp2.Aide:ehp2. contient les commandes pour appeler l'aide. Les commandes suivantes figurent dans le menu :hp2.Aide:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Index de l'aide
:pd.Affiche la liste de tous les sujets d'aide.
:pt.Aide generale
:pd.Informations generales sur le jeu, les regles et la licence.
:pt.Utiliser l'aide
:pd.Affiche l'aide systeme sur l'utilisation de l'aide.
:pt.Touches
:pd.Affiche les touches de raccourci.
:pt.About
:pd.Affiche la version et le copyright du jeu.
:eparml.

:h1 res=2920 name=PANEL_HELPINDEX.Index de l'aide
:i2 refid=Help.Index de l'aide
:p.La liste de tous les sujets d'aide est placee ici. Choisissez un sujet pour voir ses informations.

:h1 res=2930 name=PANEL_HELPGENERAL.Aide generale
:i2 refid=Help.Aide generale
:p.Ceci est la fenetre d'Aide generale, avec les informations principales.

:h1 res=2940 name=PANEL_HELPUSINGHELP.Utiliser l'aide
:i2 refid=Help.Utiliser l'aide
:p.Les informations systeme sur l'utilisation de l'aide sont placees ici.

:h1 res=2950 name=PANEL_HELPKEYS.Touches
:i2 refid=Help.Touches
:p.Vous pouvez utiliser les touches de raccourci suivantes&colon.
:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.affiche l'aide.
:pt.:hp8.F2:ehp8.
:pd.definit le style 2D des cases.
:pt.:hp8.F3:ehp8.
:pd.quitte le jeu.
:pt.:hp8.Enter:ehp8.
:pd.lance le jeu, ou l'arrete s'il tourne deja.
:pt.:hp8.Space:ehp8.
:pd.comme Entree.
:pt.:hp8.Left arrow:ehp8.
:pd.le coureur va a gauche.
:pt.:hp8.Right arrow:ehp8.
:pd.le coureur va a droite.
:pt.:hp8.Up arrow:ehp8.
:pd.le coureur va vers le haut.
:pt.:hp8.Down arrow:ehp8.
:pd.le coureur va vers le bas.
:pt.:hp8.Toute autre touche:ehp8.
:pd.le coureur s'arrete.
:pt.:hp8.Esc:ehp8.
:pd.quitte le jeu.
:pt.:hp8.Alt+F4:ehp8.
:pd.quitte le jeu.
:pt.:hp8.Ctrl+N:ehp8.
:pd.demarre une nouvelle partie.
:pt.:hp8.Ctrl+H:ehp8.
:pd.affiche les records.
:pt.:hp8.Ctrl+P:ehp8.
:pd.met le jeu en pause ou le reprend.
:pt.:hp8.Ctrl+B:ehp8.
:pd.active ou desactive Arriere-plan Actif.
:pt.:hp8.Ctrl+F:ehp8.
:pd.masque ou affiche les controles du cadre.
:eparml.

:h1 res=2970 name=PANEL_HELPPRODUCTINFO.About
:i2 refid=Help.About
:p.Cette boite de dialogue affiche des informations sur le jeu, comme le numero de version, la mention de copyright et une image.

:h1 hide res=3100 name=PANEL_PRODUCTINFODLG.About
:p.Cette boite de dialogue affiche des informations sur le jeu, comme le numero de version, la mention de copyright et une image.

.*--------------------------------------------------------------*\
.*  load dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4163 scroll=none titlebar=yes nosearch.Charger
:ol compact.
:li.Cliquez sur la fleche vers le bas a droite de la liste Lecteur pour afficher tous les lecteurs de votre systeme.
:li.Choisissez un lecteur dans la liste Lecteur.
:li.Choisissez un repertoire dans la liste Repertoire.
:li.Choisissez un nom dans la liste Fichier, ou tapez un nom de fichier, puis choisissez le bouton :hp2.Charger:ehp2..
:eol.
:p.Pour une aide specifique, choisissez un sujet ci-dessous.
:dl compact tsize=22.
:dt.:link reftype=hd res=20501.Nom de fichier:elink.
:dd.
:dt.:link reftype=hd res=20502.Type de fichier:elink.
:dd.
:dt.:link reftype=hd res=20503.Lecteur:elink.
:dd.
:dt.:link reftype=hd res=20504.Fichier:elink.
:dd.
:dt.:link reftype=hd res=20505.Repertoire:elink.
:dd.
:dt.:link reftype=hd res=20506.Charger:elink.
:dd.
:edl.

:h1 hide res=20501 nosearch.Nom de fichier
:p.Tapez le nom du fichier a charger dans le champ Nom de fichier et choisissez le bouton :hp2.Charger:ehp2..
:p.:link reftype=hd res=4163.Aide generale:elink.

:h1 hide res=20502 nosearch.Type de fichier
:p.Cliquez sur la fleche vers le bas a droite du champ Type de fichier pour afficher les types de fichier disponibles.
:p.:link reftype=hd res=4163.Aide generale:elink.

:h1 hide res=20503 nosearch.Lecteur
:p.La liste Lecteur affiche les lecteurs de votre systeme. Choisissez le lecteur qui contient le fichier.
:p.:link reftype=hd res=4163.Aide generale:elink.

:h1 hide res=20504 nosearch.Fichier
:p.La liste Fichier affiche tous les fichiers d'extension .bbg du repertoire choisi dans la liste Repertoire. Choisissez le fichier a charger.
:p.:link reftype=hd res=4163.Aide generale:elink.

:h1 hide res=20505 nosearch.Repertoire
:p.La liste Repertoire affiche les repertoires du lecteur choisi. Choisissez un repertoire pour afficher ses fichiers dans la liste Fichier.
:p.:link reftype=hd res=4163.Aide generale:elink.

:h1 hide res=20506 nosearch.Charger
:p.Choisissez le bouton :hp2.Charger:ehp2. pour charger la partie depuis le fichier.
:p.:link reftype=hd res=4163.Aide generale:elink.

.*--------------------------------------------------------------*\
.*  save dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4210 scroll=none titlebar=yes nosearch.Enregistrer sous
:ol compact.
:li.Cliquez sur la fleche vers le bas a droite de la liste Lecteur pour afficher tous les lecteurs de votre systeme.
:li.Choisissez un lecteur dans la liste Lecteur.
:li.Choisissez un repertoire dans la liste Repertoire.
:li.Tapez le nom du fichier a enregistrer dans le champ Nom de fichier et choisissez le bouton :hp2.Enregistrer:ehp2..
:eol.
:p.Pour une aide specifique, choisissez un sujet ci-dessous.
:dl compact tsize=22.
:dt.:link reftype=hd res=26501.Nom de fichier:elink.
:dd.
:dt.:link reftype=hd res=26502.Type de fichier:elink.
:dd.
:dt.:link reftype=hd res=26503.Lecteur:elink.
:dd.
:dt.:link reftype=hd res=26504.Fichier:elink.
:dd.
:dt.:link reftype=hd res=26505.Repertoire:elink.
:dd.
:dt.:link reftype=hd res=26506.Enregistrer:elink.
:dd.
:edl.

:h1 hide res=26501 nosearch.Nom de fichier
:p.Tapez le nom du fichier a enregistrer dans le champ Nom de fichier et choisissez le bouton :hp2.Enregistrer:ehp2..
:p.:link reftype=hd res=4210.Aide generale:elink.

:h1 hide res=26502 nosearch.Type de fichier
:p.Cliquez sur la fleche vers le bas a droite du champ Type de fichier pour afficher les types de fichier disponibles.
:p.:link reftype=hd res=4210.Aide generale:elink.

:h1 hide res=26503 nosearch.Lecteur
:p.La liste Lecteur affiche les lecteurs de votre systeme. Choisissez le lecteur sur lequel enregistrer le fichier.
:p.:link reftype=hd res=4210.Aide generale:elink.

:h1 hide res=26504 nosearch.Fichier
:p.La liste Fichier affiche tous les fichiers du repertoire choisi dans la liste Repertoire. Choisissez un fichier pour reutiliser son nom.
:p.:link reftype=hd res=4210.Aide generale:elink.

:h1 hide res=26505 nosearch.Repertoire
:p.La liste Repertoire affiche les repertoires du lecteur choisi. Choisissez un repertoire pour afficher ses fichiers dans la liste Fichier.
:p.:link reftype=hd res=4210.Aide generale:elink.

:h1 hide res=26506 nosearch.Enregistrer
:p.Choisissez le bouton :hp2.Enregistrer:ehp2. pour enregistrer la partie dans le fichier, sur le lecteur et dans le repertoire choisis, avec le nom indique.
:p.:link reftype=hd res=4210.Aide generale:elink.

.*--------------------------------------------------------------*\
.*  Pull-down help for the save choices
.*--------------------------------------------------------------*/
:h1 hide res=4192 id=A4192 nosearch.Enregistrer
:p.Utilisez :hp2.Enregistrer:ehp2. pour enregistrer la partie en cours. Une fois la partie enregistree dans un fichier, le nom du fichier s'affiche dans le titre de la fenetre.

:h1 hide res=4208 id=A4208 nosearch.Enregistrer sous
:p.Utilisez :hp2.Enregistrer sous:ehp2. pour nommer et enregistrer une nouvelle partie, ou pour enregistrer une partie sous un autre nom, dans un autre repertoire ou sur un autre disque.

:euserdoc.
