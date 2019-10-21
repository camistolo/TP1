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

![Mesaje de la consola una vez compilado el proyecto.](https://github.com/camistolo/TP1/blob/master/Imagenes/im1.jpeg?raw=true)

<!-- blank line -->
-----
<!-- blank line -->

## Configuración del Debug:

1. Hacer click derecho en Workspace → Debug As → Debug Configurations.
2. Clickear dos veces GDB OpenOCD Debugging.
3. Seleccionar el archivo out/lpc4337_m4/gpio_02_blinky.axf en Search Project o en Browser.
Estos tres pasos se muestran a continuación:

![Debug Configurations 1](https://github.com/camistolo/TP1/blob/master/Imagenes/im2.jpeg?raw=true)
*Primeros pasos de la configuración del Debug*

4. En la pestaña Debugger, en la sección OpenOCD Setup, hacer click en Browse para ir a la carpeta de instalación de OpenOCD, luego a bin y por último a openocd.exe.
5. En la opción Config options ingresar el siguiente texto: -f etc/openocd/lpc4337.cfg.
6. En la sección GDB Client Setup, en el campo Executable, escribir: arm-none-eabi-gdb.
7. Conectar la placa EDU-CIAA-NXP a la PC a través de la interfaz Debug.
8. Clickear en Apply, luego en Debug, y allí debería comenzar la sesión de Debug con un breakpoint en la primer línea de la función main().
Todos estos pasos se observan en la siguiente imagen:

![Debug Configurations 2](https://github.com/camistolo/TP1/blob/master/Imagenes/im3.jpeg?raw=true)
*Últimos pasos de la configuración del Debug*

9. MCUXpresso ha abierto su vista Debug, donde se ejectuará gpio_02_blinky.

Cada vez que uno quiera volver a debugear el archivo, podrá hacer el paso 1 y presionar el botón Debug As (si desea cambiar algún aspecto de la configuración, e debe presionar primero Apply y luego Debug As). Otra forma de realizar esto es simplemente presionando el botón que se muestra en la siguiente figura (encuadrado con violeta) y que se encuentra en la parte superior del programa:

![Cucaracha](https://github.com/camistolo/TP1/blob/master/Imagenes/im7.jpeg?raw=true)
*Botón para debugear el proyecto*

## Migración del proyecto

Para migrar el proyecto sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_02_blinky (parpadeo de LEDs c/sAPI) a projects/TP1 primero se debe crear la carpeta TP1 dentro de projects. Luego, copiar el proyecti gpio_02_blinky y pegarla en la carpeta recién creada (projects/TP1).

## Algunos comandos útiles

### Resume, Suspend y Terminate

Luego de debugear el proyecto, puede ocurrir que queremos pausar la depuración. Para esto, se presiona el botón de Suspend All Debug Sessions (en la siguiente imagen, está recuadrado con verde). Luego, para seguir debugeando se deberá presionar el botón Resume All Debug Sessions (en la figura, está recuadrado con negro). Para abandonar Debug con el fin de editar o compilar algún archivo, se debe presionar el botón Terminate All Debug Sessions (recuadrado en la imagen con violeta):

![](https://github.com/camistolo/TP1/blob/master/Imagenes/terminate.jpg?raw=true)

### Step into, Step over, Step return

Cuando se comienza a debugear, los siguientes botones permiten pasar de línea en línea (con Step over, recuadrado con verde en la imagen), entrar a una función específica cuando se llega a ella (con Step into, recuadrado con negro) y salir de esa función (con Step return, recuadrado con violeta en la siguiente figura):

![](https://github.com/camistolo/TP1/blob/master/Imagenes/step.jpg?raw=true)


### Breakpoints

Cuando se depura un programa, a veces se desea que haya una parada intencional y controlada en un punto específico del código. Para esto, se utilizan los breakpoints. Si se quiere colocar un breakpoint, se debe colocar el cursor sobre el punto donde se desea la pausa y entrar a Run → Toggle Breakpoint (o Ctrl+Shift+B) y del lado izquierdo del código aparecerá una señalizacióm, como la que se observa en la figura siguiente, dentro del círculo rojo:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/toggle.jpg?raw=true)


## Análisis del proyecto blinky_02_gpio

### Función principal

En primer lugar, se observa en la siguiente imagen que la función principal es un loop que prende y apaga un LED con un delay sin parar:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/im4.jpeg?raw=true)


### gpioWrite

Cuando se ingresa a la función gpioWrite, se inicializan las variables correspondientes a la configuración del puerto y el pin donde se encuentra conectado el LEDB. Luego, se realiza la configuración con la función gpioObtainPinConfig y una vez terminado esto, se setea el pin con el estado que se le pasó a la función gpioWrite mediante la función Chip_GPIO_SetPinState. Todo esto se observa en la imagen a continuación:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/im5.jpeg?raw=true)


### gpioObtainPinConfig

Dentro de la función a analizar, se configuran el puerto y el pin correspondientes al led que se quiere encender (LEDB), como se muestra en la siguiente figura:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/im6.jpeg?raw=true)


### Chip_GPIO_SetPinState

Una vez configurados el puerto y pin en cuestión, se envían las posiciones a la función Chip_GPIO_SetPinState junto con el estado deseado (pin encendido (ON) o apagado (OFF)). Esto se muestra a continuación:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/im8.jpeg?raw=true)


La matriz B contiene la dirección de cada pin perteneciente a cada puerto. A través de ella se puede acceder al pin y puerto que el programador desee. A continuación se muestra su inicialización:


![](https://github.com/camistolo/TP1/blob/master/Imagenes/im9.jpeg?raw=true)


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
Cada vez que se quiera trabajar con el proyecto, se debe copiar el repositorio de la web en el local. Cada vez que se quiera traer el repositorio web al local, se escribirá sólo la siguiente línea:
    
    git pull

Una vez modificados los archivos localmente, para poder subirlos a la web se deberán escribir las líneas de comando escritas a continuación:

    git add --all
    git commit -m "Comentario del commit"
    git push origin master


## Análisis del proyecto gpio_01_switches_leds

### Función principal

En la siguiente imagen, se puede observar el codigo principal, que se encarga de prender un LED dependiendo de que pulsador sea precionado.

![](https://github.com/camistolo/TP1/blob/master/Imagenes/sl0.JPG?raw=true)

En primer lugar, se configuran los pines como entrada o salida a traves de la función gpioConfig. Esta función recibe la macro de la dirección de cada pin y en que estado va a estar (entrada o salida). 

![](https://github.com/camistolo/TP1/blob/master/Imagenes/sl1.jpeg?raw=true)
![](https://github.com/camistolo/TP1/blob/master/Imagenes/sl2.jpeg?raw=true)
![](https://github.com/camistolo/TP1/blob/master/Imagenes/sl3.jpeg?raw=true)

Una vez realizada la configuración, el programa entra en el loop principal. Aquí, se lee el valor de cada entrada atraves de la función gpioRead y es guardado en la variable valor. Las macros TEC1, TEC2, TEC3 y TEC4 corresponden a la dirección de memoria de los pulsadores respectivamente.

![](https://github.com/camistolo/TP1/blob/master/Imagenes/sl4.jpeg?raw=true)

Por medio de la función gpioWrite, se setea la salida respecto al estado de la entrada correspondiente. La función mencionada con anterioridad recibe el nombre del pin (donde se escribirá el valor) y el estado de este (prendido o apagado).

![](https://github.com/camistolo/TP1/blob/master/Imagenes/sl5.jpeg?raw=true)





## Análisis de TickHooks

En tickHooks lo primero que se hace es inicializar la placa con boardConfig().

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture10_tickHook_main.PNG)

Luego se llama a tickConfig a la cual se le pasa el parametro TICKRATE_MS. tickConfig es una macro: #define tickConfig tickInit. Por lo tanto cuando se llama a tickConfig en definitiva se esta llamando a tickInit. 

tickInit es la funcion que se llama pasandole TICKRATE_MS, un tipo tick_t, y devuelve un booleano (se encuentra en sapi_tick.h y .c).

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture1_tickInit.PNG?raw=true)

El tipo tick_t esta definido como un uint64_t, un entero muy grande. 

Metiendose en tickInit, primero valida que el TICKRATE no sea cero. Si es cero, llama a tickPowerSet pasandole un OFF. Esto lo que hace es deshabilitar el clock y la energia de los perifericos.

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture2_tickPowerSet.PNG)

Luego de q valida esto, ve si TICKRATE esta entre 1 y 50 (valores validos). Si esta entre 1 y 50, copia el valor de TICKRATE a tickRateMS, una variable volatil del tipo tick_t y luego llama a SysTick_Config.

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture3_llamada_SysTick_Config.PNG)

A SysTick_Config se le pasa una variable tipo uint32_t resultante de multiplicar el SystemCoreClock de la placa por el TICKRATE que se le paso, y luego dividir todo por 1000 (a esta variable en la funcion se la llama "ticks").

Entrando a SysTick_Config, lo primero que hace es validar que ticks-1 sea mayor a SysTic_LOAD_RELOAD_Msk.

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture8_SysTick_LOAD_RELOAD.PNG)

Luego se ve que se llena SysTick, una estructura definida como ((SysTick_Type* ) SysTick_BASE)

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture4_SysTick_estructura.PNG)

en donde SysTick_Type es una estructura con 4 uint32_t, CTRL, LOAD, VAL y CALIB

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture5_SysTick_Type_estructura.PNG)

y SysTick_BASE es la address.

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture6_SysTick_BASE.PNG)

 SysTick_BASE es SCS_BASE + 0x0010UL, una direccion que desconozco.

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture7_SCS_BASE.PNG)

Se le carga el LOAD de SysTick como ticks-1, VAL como 0 (es el valor del contador), se setea la prioridad del SysTick_Interrupt mediante la funcion NVIC_SetPriority (ver captura 9)

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture9_NVIC_SetPriority.PNG)

y por ultimo se habilita mediante CTRL haciendo una "or" de tres mascaras.

Sale de SysTick_Config devolviendo cero.

Volviendo a tickInit, ya se tiene configurado las interrupts de SysTick. Luego se llama a tickPowerSet pasandole ON, prendiendo el clock y la energia a los perifericos.
Sale de tickInit con un 1 de satisfactorio.

Volviendo al main de tickHook, luego del tickConfig se llama indefinidamente a tickCallbackSet, la cual se encarga de ejecutar una funcion nombrada myTickHook siempre q haya un interrupt. tickCallbackSet recibe un puntero a funcion de tipo callBackFuncPtr_t, que sera la funcion que querramos ejecutar (myTickHook, explicada despues) y recibe los parametros de la funcion que le pasamos (ver captura 11).

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture11_tickCallbackSet.PNG)

MyTickHook es la funcion definida en tickHook.c y la que la pasamos a tickCallbackSet como puntero a funcion (ver captura 12). Resumiendo, prende y apaga un led q le pasemos.

![ALT](https://github.com/camistolo/TP1/blob/master/Imagenes/Capture12_myTickHook.PNG)









## Análisis del envío de mensajes de depuración por puerto serie c/sAPI

### Inicializaciones

En primer lugar, se observa que se hacen las inicializaciones y configuraciones correspondientes. Se utiliza la función anterior de ticks y por ende, se configura el TICKRATE mediante tickConfig y la interrupción, mediante tickCallbackSet. Previamente, se configura la placa (al igual que en cada código) y se configura el puerto serie.

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps3.PNG?raw=true)


### debugPrintConfigUart

Se configura la dirección del puerto serie y el baudrate que se le envía.

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps4.PNG?raw=true)

 El puerto serie que se elige es el UART_USB, que se observa declarado a continuación:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps5.PNG?raw=true)

Se enumeran todos los puertos series posibles y se aclara a que pines corresponden, con lo cual se puede ver en la placa donde podría conectarse para funcionar como puerto serie.

### debugPrintString

DeLa función printString escribe la cadena que se le pasa como parámetro, con lo cual, se puede corroborar previo a realizar la función principal del código si el puerto serie funciona correctamente o no.
![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps6.PNG?raw=true)

#### uartWriteString

La función uartWriteString escribe la función byte por byte, hasta que se escribieron todos los caracteres de la cadena.


![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps9.PNG?raw=true)

#### uartWriteByte

La función uartWriteByte envía los bytes que le pasan como parámetro siempre y cuando el pin de transmisión esté disponible. Esto se chequea con la función uartTxReady.


![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps10.PNG?raw=true)

#### uartTxReady

Si hay espacio en el pin de transmisión Tx, la función uartTxReady envía un valor booleano seteado en TRUE. 

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps11.PNG?raw=true)

#### uartTxWrite

Luego de chequear que el pin de transmisión está disponible, se escribe el byte en aquel pin, mediante la función Chip_UART_SendByte, que recibe la dirección del pin de transmisión correspondiente y el byte quq se desea enviar en ese momento 

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps12.PNG?raw=true)


### Loop principal

Una vez configurado todo, se ingresa al loop principal, donde se chequea en principio, si se llevó a cabo la interrupción, que coloca al Flag en TRUE (esta se expliacará luego).

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps7.PNG?raw=true)

Si se interrumpe el programa (el Flag se pone en True), se vuelve a poner en False para desactivarlo y se cambia el estado del led (en este caso, es el LED3) mediante la función gpioToggle:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps8.PNG?raw=true)

Esta función escribe en el pin correspondiente (LED3) lo contrario a lo que lee. Por ende, si el led está prendido, lo apagará. De forma contraria, si el led está apagado, lo prenderá.

 Cuando cambia el valor del led al opuesto, también se imprime la cadena "LED Toggle". Esto se observa a continuación:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps1.PNG?raw=true)


#### myTickHook

La diferencia de este caso con el resto de los códigos es que la interrupción simplemente cambia el valor de un Flag. Esto permite que el código sea portable y que en caso de querer cambiar lo que hace la interupción, simplemente se debe cambiar el código principal y no la interrupción en sí. El Flag LED_Time_Flag se declara volatile ya que se modifica en una interrupción y por eso, se desea que el compilador no optimice su valor, ya que si no, no podría modificarse allí. Esto se observa en la imagen a continuación:

![](https://github.com/camistolo/TP1/blob/master/Imagenes/ps2.PNG?raw=true)




## Sensado de Push Buttons c/sAPI

### Inicializaciones

En primer lugar se declaran los Flags que serán modificados en las interrupciones y por esa razón son declarados como volatile.

![](https://github.com/camistolo/TP1/blob/master/Imagenes/6_1.PNG?raw=true)

Por otro lado, también se declara la función myTickHook, que es la que se ejecuta cada vez que se produce una interrupción. Esta función se encarga de cambiar los Flags correspondientes, uno encargado de notificar que se ejecuta un tick y el otro si el pulsador se encuentra presionado.

### Configuraciones

En segundo lugar se configura tanto la placa, como el puerto serie y la función que genera los ticks al igual que en los casos anteriores.

![](https://github.com/camistolo/TP1/blob/master/Imagenes/6_2.PNG?raw=true)

### Loop

Se encuentra la función__WFI() que espera una interrupción. Luego si el Flag BUTTON_Time_Flag es verdadero, se pregunta si el Flag BUTTON_Status_Flag es verdadero (es decir que el pulsador se encontraba presionado). Si esto es asi se fija si el contador de ticks es cero. Si se cumple, se resetea el contador, se prende un led luego se cambia el led y por puerto serie se envia "LED Toggle\n"; si no es asi se decrementa el pulsador.


![](https://github.com/camistolo/TP1/blob/master/Imagenes/6_3.PNG?raw=true)


## Hoja de corrección

![](https://github.com/camistolo/TP1/blob/master/Imagenes/hoja_de_ruta.jpeg)
