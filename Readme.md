# Repositorio del TP1 - Bernardo Turquieto

## Descarga de firmware_v2.git:

Luego de descargar todos los programas necesarios, se conecta la placa EDU-CIAA-NXP y se copia el archivo en el repositorio creado con las siguientes líneas:

    project.mk.template llamada project.mk:
    git clone https://github.com/ciaa/firmware_v2.git
    cd firmware_v2
    git status -s
    git checkout master
    cp project.mk.template project.mk

Para configurar el proyecto (PROJECT), el procesador (TARGET) y la placa (BOARD), se deberá modificar el archivo project.mk.

Para abrir el archivo firmware_v2, se deberán seguir los siguientes pasos:

    1. Ir a File → New → Other → C/C++ → Makefile Project with Existing Code
    2. En Existing Code Location Browse, busacr la carpeta firmware_v2 clonada anteriormente.
    3. Destildar C++.
    4. Seleccionar NXP MCU Tools

A continuación, hacer click derecho en el archivo firmware_v2 y presionar Build Project, que lo compilará y mostrará el siguiente mensaje por la consola:

![Mesaje de la consola una vez compilado el proyecto.](https://github.com/DonSatur/TP1/blob/master/Imagenes/im1.jpeg?raw=true)

<!-- blank line -->
-----
<!-- blank line -->

## Configuración del Debug:

1. Hacer click derecho en Workspace → Debug As → Debug Configurations.
2. Clickear dos veces GDB OpenOCD Debugging.
3. Seleccionar el archivo out/lpc4337_m4/gpio_02_blinky.axf en Search Project o en Browser.
Estos tres pasos se muestran a continuación:

![Debug Configurations 1](https://github.com/DonSatur/TP1/blob/master/Imagenes/im2.jpeg?raw=true)
*Primeros pasos de la configuración del Debug*

4. En la pestaña Debugger, en la sección OpenOCD Setup, hacer click en Browse para ir a la carpeta de instalación de OpenOCD, luego a bin y por último a openocd.exe.
5. En la opción Config options ingresar el siguiente texto: -f etc/openocd/lpc4337.cfg.
6. En la sección GDB Client Setup, en el campo Executable, escribir: arm-none-eabi-gdb.
7. Conectar la placa EDU-CIAA-NXP a la PC a través de la interfaz Debug.
8. Clickear en Apply, luego en Debug, y allí debería comenzar la sesión de Debug con un breakpoint en la primer línea de la función main().
Todos estos pasos se observan en la siguiente imagen:

![Debug Configurations 2](https://github.com/DonSatur/TP1/blob/master/Imagenes/im3.jpeg?raw=true)
*Últimos pasos de la configuración del Debug*

9. MCUXpresso ha abierto su vista Debug, donde se ejectuará gpio_02_blinky.

Cada vez que uno quiera volver a debugear el archivo, podrá hacer el paso 1 y presionar el botón Debug As (si desea cambiar algún aspecto de la configuración, e debe presionar primero Apply y luego Debug As). Otra forma de realizar esto es simplemente presionando el botón que se muestra en la siguiente figura (encuadrado con violeta) y que se encuentra en la parte superior del programa:

![Cucaracha](https://github.com/DonSatur/TP1/blob/master/Imagenes/im7.jpeg?raw=true)
*Botón para debugear el proyecto*

## Migración del proyecto

Para migrar el proyecto sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_02_blinky (parpadeo de LEDs c/sAPI) a projects/TP1 primero se debe crear la carpeta TP1 dentro de projects. Luego, copiar el proyecti gpio_02_blinky y pegarla en la carpeta recién creada (projects/TP1).

## Algunos comandos útiles

### Resume, Suspend y Terminate

Luego de debugear el proyecto, puede ocurrir que queremos pausar la depuración. Para esto, se presiona el botón de Suspend All Debug Sessions (en la siguiente imagen, está recuadrado con verde). Luego, para seguir debugeando se deberá presionar el botón Resume All Debug Sessions (en la figura, está recuadrado con negro). Para abandonar Debug con el fin de editar o compilar algún archivo, se debe presionar el botón Terminate All Debug Sessions (recuadrado en la imagen con violeta):

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/terminate.jpg?raw=true)

### Step into, Step over, Step return

Cuando se comienza a debugear, los siguientes botones permiten pasar de línea en línea (con Step over, recuadrado con verde en la imagen), entrar a una función específica cuando se llega a ella (con Step into, recuadrado con negro) y salir de esa función (con Step return, recuadrado con violeta en la siguiente figura):

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/step.jpg?raw=true)


### Breakpoints

Cuando se depura un programa, a veces se desea que haya una parada intencional y controlada en un punto específico del código. Para esto, se utilizan los breakpoints. Si se quiere colocar un breakpoint, se debe colocar el cursor sobre el punto donde se desea la pausa y entrar a Run → Toggle Breakpoint (o Ctrl+Shift+B) y del lado izquierdo del código aparecerá una señalizacióm, como la que se observa en la figura siguiente, dentro del círculo rojo:

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/toggle.jpg?raw=true)


## Análisis del proyecto blinky_02_gpio

### Función principal

En primer lugar, se observa en la siguiente imagen que la función principal es un loop que prende y apaga un LED con un delay sin parar:

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/im4.jpeg?raw=true)


### gpioWrite

Cuando se ingresa a la función gpioWrite, se inicializan las variables correspondientes a la configuración del puerto y el pin donde se encuentra conectado el LEDB. Luego, se realiza la configuración con la función gpioObtainPinConfig y una vez terminado esto, se setea el pin con el estado que se le pasó a la función gpioWrite mediante la función Chip_GPIO_SetPinState. Todo esto se observa en la imagen a continuación:

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/im5.jpeg?raw=true)


### gpioObtainPinConfig

Dentro de la función a analizar, se configuran el puerto y el pin correspondientes al led que se quiere encender (LEDB), como se muestra en la siguiente figura:

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/im6.jpeg?raw=true)


### Chip_GPIO_SetPinState

Una vez configurados el puerto y pin en cuestión, se envían las posiciones a la función Chip_GPIO_SetPinState junto con el estado deseado (pin encendido (ON) o apagado (OFF)). Esto se muestra a continuación:

![](https://github.com/DonSatur/TP1/blob/master/Imagenes/im8.jpeg?raw=true)


La matriz B contiene la dirección de cada pin perteneciente a cada puerto. A través de ella se puede acceder al pin y puerto que el programador desee. A continuación se muestra su inicialización:


![](https://github.com/DonSatur/TP1/blob/master/Imagenes/im9.jpeg?raw=true)


## Github

Para trabajar con Github, se debe crear una cuenta y luego, un repositorio. Esto se puede realizar desde la web, yendo al ícono de la cuenta que se encuentra arriba a la derecha y presionando Your Repositories. Allí, presionar New y crearlo.
Luego, se hará la conexión con el repositorio local. Inicialmente, se irá a la carpeta donde se desea tener el repositorio y se presionará el click derecho, eligiendo la opción de Git Bash Here (para esto, se debe tener el Git Bash previamente instalado). A continuación, colocar las siguientes líneas de comando:

    git init
    git remote add origin [url del repositorio]
    git status #muestra el estado actual del repositorio
    git add - - all
    git status
    git commit –m ”commit inicial”
    git push -u origin master

Esto copiará el repositorio local al que se encuentra en la web.

### Push y Pull
Cada vez que se quiera trabajar con el proyecto, se debe copiar el repositorio de la web en el local. La primera vez se deberá clonar el repositorio con la siguiente línea de comando, escrita en el Bash (llamado desde la carpeta del repositorio):

    git clone [url del repositorio]

Luego de esto, y cada vez que se quiera traer el repositorio web al local, se escribirá sólo la siguiente línea:
    
    git pull

Una vez modificados los archivos localmente, para poder subirlos a la web se deberán escribir las líneas de comando escritas a continuación:

    git add --all
    git commit -m "Comentario del commit"
    git push origin master
