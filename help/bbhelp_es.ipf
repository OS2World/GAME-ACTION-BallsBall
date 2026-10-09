.* BallsBall help (es) - generated; texts per language, same panel ids
:userdoc.
:title.Ayuda de BallsBall

.*--------------------------------------------------------------*\
.*  Main window extended help panel (PANEL_MAIN)
.*--------------------------------------------------------------*/
:h1 res=2100 name=PANEL_MAIN.Acerca de BallsBall
:i1 id=aboutMain.Acerca de BallsBall
:p.BallsBall es un juego de Presentation Manager. Con el corredor construyes nuevos caminos por el campo, mientras las bolas rebotan y los cazadores patrullan los caminos.
:p.Esta es una version modernizada del juego de codigo abierto. Esta compilada con Open Watcom, incluye ingles, holandes, espanol, aleman, frances e italiano en un solo ejecutable y escala la ventana del juego a por lo menos 1024x768 cuando el escritorio lo permite (las celdas siguen siendo cuadradas).
:p.Elija un tema&colon.
:ul compact.
:li.:link reftype=hd res=1.Reglas:elink.
:li.:link reftype=hd res=2.Licencia:elink.
:li.:link reftype=hd res=3.Raton:elink.
:eul.

.*--------------------------------------------------------------*\
.*  Rules, license, mouse
.*--------------------------------------------------------------*/
:h1 res=1.Reglas
:i1 id=Rules.Reglas
:p.Las reglas son sencillas. Con el corredor haces nuevos caminos por el campo. Lo diriges con las :link reftype=hd res=2950.teclas de flecha:elink. (izquierda, derecha, arriba y abajo) o con el :link reftype=hd res=3.raton:elink.. Recibes un punto por cada celda anadida. Las celdas se anaden cuando el corredor vuelve a un camino viejo.
:p.Las bolas se mueven por el campo. Si una bola toca un camino nuevo antes de que el corredor llegue a un camino viejo, el camino nuevo cae. Pierdes un punto por cada celda destruida y 50 puntos por una colision.
:p.Si logras detener una bola recibes 100 puntos. Es dificil pero posible: por ejemplo, puedes limitar su campo. En ciertas condiciones una bola tambien se atasca. Cuales? Pruebalo!
:p.Los cazadores se mueven por los caminos. Solo avanzan; si no pueden, dan la vuelta, y cuando hay una eleccion escogen una direccion al azar. Una colision con un cazador cuesta 50 puntos.
:p.El juego tiene 11 niveles. El numero de bolas y cazadores es el nivel mas 4. Si reunes 2/3 de los puntos del campo en 3 minutos pasas al siguiente nivel; si no, pierdes. Si reunes 4/5 en menos de 3 minutos pasas antes al siguiente nivel. Si ya estas en el nivel 11, has ganado.
:p.La linea de texto muestra tu puntuacion. 4/5 es el 100%, 2/3 es el 84%.
:p.Si despues del juego llegas al puesto 10 o mejor, tu nombre se anota en las Marcas.

:h1 res=2.Licencia
:i1 id=License.Licencia
:p.BallsBall es software libre, publicado bajo la Licencia Publica General de GNU, version 3 (vea LICENSE.txt). El programa se ofrece "tal cual", sin garantia de ningun tipo.
:p.Juego original de Dmitry Ivanov.
:p.Distribuya el programa junto con estos archivos&colon.
:ul compact.
:li.LICENSE.txt
:li.readme.txt
:li.bbhelp_es.hlp
:eul.

:h1 res=3.Raton
:i1 id=Mouse.Raton
:p.El interior de la ventana se divide, respecto al corredor, en cuatro partes&colon. izquierda, derecha, arriba y abajo.
:artwork align=left name='mous.bmp'.
:p.Haga clic en una de estas partes y el corredor se mueve a la izquierda, a la derecha, hacia arriba o hacia abajo respectivamente.

.*--------------------------------------------------------------*\
.*  Game menu
.*--------------------------------------------------------------*/
:h1 res=2210 name=PANEL_FILE.Menu Archivo
:i1 id=File.Menu Archivo
:p.El menu :hp2.Archivo:ehp2. contiene los comandos para iniciar, abrir y guardar juegos, pausar el juego, mostrar las marcas y salir de BallsBall. Los siguientes comandos aparecen en el menu :hp2.Archivo:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Nuevo Juego
:pd.Inicia un juego nuevo sin titulo.
:pt.Abrir
:pd.Abre un juego guardado desde un archivo.
:pt.Guardar
:pd.Guarda el juego en el archivo actual.
:pt.Guardar como
:pd.Guarda el juego en un archivo con un nombre nuevo.
:pt.Pausar Juego
:pd.Pausa o reanuda el juego.
:pt.Ver Marcas
:pd.Muestra las marcas.
:pt.Salir
:pd.Sale de BallsBall.
:eparml.

:h1 res=2220 name=PANEL_FILENEW.Nuevo Juego
:i2 refid=File.Nuevo Juego
:p.Use :hp2.Nuevo Juego:ehp2. para iniciar un juego nuevo. La puntuacion y el nivel vuelven a cero y la barra de titulo muestra el juego sin titulo.

:h1 res=2230 name=PANEL_FILEOPEN.Abrir
:i2 refid=File.Abrir
:p.Use :hp2.Abrir:ehp2. para abrir un juego guardado desde un archivo. Un dialogo muestra los archivos con la extension .bbg del directorio actual.

:h1 res=2240 name=PANEL_FILESAVE.Guardar
:i2 refid=File.Guardar
:p.Use :hp2.Guardar:ehp2. para guardar el juego en el archivo actual. Si el juego aun no tiene nombre, aparece primero el dialogo :hp2.Guardar como:ehp2..

:h1 res=2250 name=PANEL_FILESAVEAS.Guardar como
:i2 refid=File.Guardar como
:p.Use :hp2.Guardar como:ehp2. para dar nombre al juego y guardarlo en un archivo nuevo. Un dialogo le pide el nombre del archivo.

:h1 res=2270 name=PANEL_DIRECTION_START.Pausar Juego
:i2 refid=File.Pausar Juego
:p.Use :hp2.Pausar Juego:ehp2. para iniciar el juego o detenerlo si ya esta en marcha. Enter y Espacio hacen lo mismo.

:h1 res=2260 name=PANEL_HIGHSCORES.Ver Marcas
:i2 refid=File.Ver Marcas
:p.Use :hp2.Ver Marcas:ehp2. para mostrar un dialogo con las marcas actuales.

:h1 res=2290 name=PANEL_FILEEXIT.Salir
:i2 refid=File.Salir
:p.Sale de BallsBall con :hp2.Salir:ehp2., o pulsando Esc o Alt+F4.

.*--------------------------------------------------------------*\
.*  Options menu
.*--------------------------------------------------------------*/
:h1 res=2301 name=PANEL_SETTINGS.Menu Configuracion
:i1 id=Settings.Menu Configuracion
:p.El menu :hp2.Configuracion:ehp2. contiene los comandos para cambiar la configuracion de BallsBall. Los siguientes comandos aparecen en el menu :hp2.Configuracion:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Sonido
:pd.Activa o desactiva el sonido.
:pt.Estilo
:pd.Cambia entre el estilo 2D y 3D de las celdas.
:pt.Nivel
:pd.Establece el nivel deseado, de 0 a 11.
:pt.Ajustes visuales
:pd.Muestra un dialogo con todos los ajustes visuales.
:pt.Idioma
:pd.Selecciona el idioma de la interfaz&colon. ingles, holandes, espanol, aleman, frances o italiano. La ayuda sigue el idioma elegido.
:pt.Fondo Activo
:pd.Permite que el juego siga ejecutandose mientras su ventana no esta activa (Ctrl+B).
:pt.Marco
:pd.Oculta o muestra la barra de titulo, el menu del sistema y la barra de menus, dejando solo el area de juego (Ctrl+F).
:pt.Guardar ajustes al salir
:pd.Si esta marcado (por defecto), los ajustes se guardan al salir del juego. Si no, los ajustes cambiados no se guardan.
:eparml.

:h1 res=2305 name=PANEL_SOUND.Sonido
:i2 refid=Settings.Sonido
:p.Use los comandos de :hp2.Sonido:ehp2. para activar o desactivar el sonido.

:h1 res=2302 name=PANEL_STYLE.Estilo
:i2 refid=Settings.Estilo
:p.Use los comandos de :hp2.Estilo:ehp2., o la tecla F2, para cambiar el estilo de las celdas.

:h1 res=2308 name=PANEL_LEVEL.Nivel
:i2 refid=Settings.Nivel
:p.Use los comandos de :hp2.Nivel:ehp2. para establecer el nivel deseado, entre 0 y 11.

:h1 res=2314 name=PANEL_SETTINGS_ALL.Ajustes visuales
:i2 refid=Settings.Ajustes visuales
:p.Use :hp2.Ajustes visuales:ehp2. para abrir el dialogo de ajustes. Alli puede cambiar los colores de las bolas y de los distintos tipos de celdas, el tamano de las celdas y de la ventana, el estilo, el sonido y el modo de moverse tras una captura. Tambien puede restaurar los ajustes por defecto.
:p.La ventana del juego se agranda automaticamente, si el escritorio lo permite, para que el campo alcance por lo menos 1024x768. Las celdas siguen siendo cuadradas y la ventana nunca es mayor que el escritorio.

.*--------------------------------------------------------------*\
.*  Help menu
.*--------------------------------------------------------------*/
:h1 res=2910 name=PANEL_HELP.Menu Ayuda
:i1 id=Help.Menu Ayuda
:p.El menu :hp2.Ayuda:ehp2. contiene los comandos para llamar a la ayuda. Los siguientes comandos aparecen en el menu :hp2.Ayuda:ehp2.&colon.
:parml tsize=25 break=none.
:pt.Ayuda al indice
:pd.Muestra la lista de todos los temas de ayuda.
:pt.Ayuda general
:pd.Informacion general sobre el juego, las reglas y la licencia.
:pt.Usar la Ayuda
:pd.Muestra la ayuda del sistema sobre el uso de la ayuda.
:pt.Ayuda de teclas
:pd.Muestra las teclas rapidas.
:pt.About
:pd.Muestra la version y el copyright del juego.
:eparml.

:h1 res=2920 name=PANEL_HELPINDEX.Ayuda al indice
:i2 refid=Help.Ayuda al indice
:p.Aqui se coloca la lista de todos los temas de ayuda. Elija un tema para ver su informacion.

:h1 res=2930 name=PANEL_HELPGENERAL.Ayuda general
:i2 refid=Help.Ayuda general
:p.Esta es la ventana de Ayuda general, con la informacion principal.

:h1 res=2940 name=PANEL_HELPUSINGHELP.Usar la Ayuda
:i2 refid=Help.Usar la Ayuda
:p.Aqui se coloca la informacion del sistema sobre el uso de la ayuda.

:h1 res=2950 name=PANEL_HELPKEYS.Teclas
:i2 refid=Help.Teclas
:p.Puede usar las siguientes teclas rapidas&colon.
:parml tsize=20 break=none.
:pt.:hp8.F1:ehp8.
:pd.muestra la ayuda.
:pt.:hp8.F2:ehp8.
:pd.establece el estilo 2D de las celdas.
:pt.:hp8.F3:ehp8.
:pd.sale del juego.
:pt.:hp8.Enter:ehp8.
:pd.inicia el juego, o lo detiene si ya esta en marcha.
:pt.:hp8.Space:ehp8.
:pd.igual que Enter.
:pt.:hp8.Left arrow:ehp8.
:pd.el corredor va a la izquierda.
:pt.:hp8.Right arrow:ehp8.
:pd.el corredor va a la derecha.
:pt.:hp8.Up arrow:ehp8.
:pd.el corredor va hacia arriba.
:pt.:hp8.Down arrow:ehp8.
:pd.el corredor va hacia abajo.
:pt.:hp8.Cualquier otra tecla:ehp8.
:pd.el corredor se detiene.
:pt.:hp8.Esc:ehp8.
:pd.sale del juego.
:pt.:hp8.Alt+F4:ehp8.
:pd.sale del juego.
:pt.:hp8.Ctrl+N:ehp8.
:pd.inicia un juego nuevo.
:pt.:hp8.Ctrl+H:ehp8.
:pd.muestra las marcas.
:pt.:hp8.Ctrl+P:ehp8.
:pd.pausa o reanuda el juego.
:pt.:hp8.Ctrl+B:ehp8.
:pd.activa o desactiva Fondo Activo.
:pt.:hp8.Ctrl+F:ehp8.
:pd.oculta o muestra los controles del marco.
:eparml.

:h1 res=2970 name=PANEL_HELPPRODUCTINFO.About
:i2 refid=Help.About
:p.Este dialogo muestra informacion sobre el juego, como el numero de version, el aviso de copyright y una imagen.

:h1 hide res=3100 name=PANEL_PRODUCTINFODLG.About
:p.Este dialogo muestra informacion sobre el juego, como el numero de version, el aviso de copyright y una imagen.

.*--------------------------------------------------------------*\
.*  load dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4163 scroll=none titlebar=yes nosearch.Abrir
:ol compact.
:li.Pulse la flecha hacia abajo a la derecha de la lista Unidad para mostrar todas las unidades de su sistema.
:li.Elija una unidad de la lista Unidad.
:li.Elija un directorio de la lista Directorio.
:li.Elija un nombre de la lista Archivo, o escriba un nombre de archivo, y pulse el boton :hp2.Abrir:ehp2..
:eol.
:p.Para ayuda especifica, elija un tema abajo.
:dl compact tsize=22.
:dt.:link reftype=hd res=20501.Nombre de archivo:elink.
:dd.
:dt.:link reftype=hd res=20502.Tipo de archivo:elink.
:dd.
:dt.:link reftype=hd res=20503.Unidad:elink.
:dd.
:dt.:link reftype=hd res=20504.Archivo:elink.
:dd.
:dt.:link reftype=hd res=20505.Directorio:elink.
:dd.
:dt.:link reftype=hd res=20506.Abrir:elink.
:dd.
:edl.

:h1 hide res=20501 nosearch.Nombre de archivo
:p.Escriba el nombre del archivo que quiere abrir en el campo Nombre de archivo y pulse el boton :hp2.Abrir:ehp2..
:p.:link reftype=hd res=4163.Ayuda general:elink.

:h1 hide res=20502 nosearch.Tipo de archivo
:p.Pulse la flecha hacia abajo a la derecha del campo Tipo de archivo para mostrar los tipos disponibles.
:p.:link reftype=hd res=4163.Ayuda general:elink.

:h1 hide res=20503 nosearch.Unidad
:p.La lista Unidad muestra las unidades de su sistema. Elija la unidad que contiene el archivo.
:p.:link reftype=hd res=4163.Ayuda general:elink.

:h1 hide res=20504 nosearch.Archivo
:p.La lista Archivo muestra todos los archivos con la extension .bbg del directorio elegido en la lista Directorio. Elija el archivo que quiere abrir.
:p.:link reftype=hd res=4163.Ayuda general:elink.

:h1 hide res=20505 nosearch.Directorio
:p.La lista Directorio muestra los directorios de la unidad elegida. Elija un directorio para mostrar sus archivos en la lista Archivo.
:p.:link reftype=hd res=4163.Ayuda general:elink.

:h1 hide res=20506 nosearch.Abrir
:p.Pulse el boton :hp2.Abrir:ehp2. para abrir el juego desde el archivo.
:p.:link reftype=hd res=4163.Ayuda general:elink.

.*--------------------------------------------------------------*\
.*  save dialog help
.*--------------------------------------------------------------*/
:h1 hide res=4210 scroll=none titlebar=yes nosearch.Guardar como
:ol compact.
:li.Pulse la flecha hacia abajo a la derecha de la lista Unidad para mostrar todas las unidades de su sistema.
:li.Elija una unidad de la lista Unidad.
:li.Elija un directorio de la lista Directorio.
:li.Escriba el nombre del archivo que quiere guardar en el campo Nombre de archivo y pulse el boton :hp2.Guardar:ehp2..
:eol.
:p.Para ayuda especifica, elija un tema abajo.
:dl compact tsize=22.
:dt.:link reftype=hd res=26501.Nombre de archivo:elink.
:dd.
:dt.:link reftype=hd res=26502.Tipo de archivo:elink.
:dd.
:dt.:link reftype=hd res=26503.Unidad:elink.
:dd.
:dt.:link reftype=hd res=26504.Archivo:elink.
:dd.
:dt.:link reftype=hd res=26505.Directorio:elink.
:dd.
:dt.:link reftype=hd res=26506.Guardar:elink.
:dd.
:edl.

:h1 hide res=26501 nosearch.Nombre de archivo
:p.Escriba el nombre del archivo que quiere guardar en el campo Nombre de archivo y pulse el boton :hp2.Guardar:ehp2..
:p.:link reftype=hd res=4210.Ayuda general:elink.

:h1 hide res=26502 nosearch.Tipo de archivo
:p.Pulse la flecha hacia abajo a la derecha del campo Tipo de archivo para mostrar los tipos disponibles.
:p.:link reftype=hd res=4210.Ayuda general:elink.

:h1 hide res=26503 nosearch.Unidad
:p.La lista Unidad muestra las unidades de su sistema. Elija la unidad en la que quiere guardar el archivo.
:p.:link reftype=hd res=4210.Ayuda general:elink.

:h1 hide res=26504 nosearch.Archivo
:p.La lista Archivo muestra todos los archivos del directorio elegido en la lista Directorio. Elija un archivo para reutilizar su nombre.
:p.:link reftype=hd res=4210.Ayuda general:elink.

:h1 hide res=26505 nosearch.Directorio
:p.La lista Directorio muestra los directorios de la unidad elegida. Elija un directorio para mostrar sus archivos en la lista Archivo.
:p.:link reftype=hd res=4210.Ayuda general:elink.

:h1 hide res=26506 nosearch.Guardar
:p.Pulse el boton :hp2.Guardar:ehp2. para guardar el juego en el archivo, en la unidad y el directorio elegidos, con el nombre indicado.
:p.:link reftype=hd res=4210.Ayuda general:elink.

.*--------------------------------------------------------------*\
.*  Pull-down help for the save choices
.*--------------------------------------------------------------*/
:h1 hide res=4192 id=A4192 nosearch.Guardar
:p.Use :hp2.Guardar:ehp2. para guardar el juego en curso. Tras guardar el juego en un archivo, el nombre del archivo se muestra en el titulo de la ventana.

:h1 hide res=4208 id=A4208 nosearch.Guardar como
:p.Use :hp2.Guardar como:ehp2. para dar nombre a un juego nuevo y guardarlo, o para guardar un juego con otro nombre, en otro directorio o en otro disco.

:euserdoc.
