/* Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * Date: 2016-04-26
 */



/*==================[inclusions]=============================================*/

//#include "blinky.h"   // <= own header (optional)
#include "sapi.h"       // <= sAPI header
/* The DEBUG* functions are sAPI debug print functions.
   Code that uses the DEBUG* functions will have their I/O routed to
   the sAPI DEBUG UART. */
DEBUG_PRINT_ENABLE;


#define TP1_1 (1)	/* Test & Migrate PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_02_blinky
					               to PROJECT = projects/SE-2018-TPs/TP1 */
#define TP1_2 (2)	/* Test & Migrate PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/gpio/gpio_01_switches_leds
					               to PROJECT = projects/SE-2018-TPs/TP1 */
#define TP1_3 (3)	/* Test & Migrate PROJECT = sapi_examples/edu-ciaa-nxp/bare_metal/tick_01_tickHook
 	 	 	 	 	               to PROJECT = projects/SE-2018-TPs/TP1 */
#define TP1_4 (4)

#define TP1_5 (5)

#define TEST (TP1_5)
#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_10MS	(10)			/* 100 ticks per second */
#define TICKRATE_100MS	(100)			/* 10 ticks per second */
#define TICKRATE_MS		(TICKRATE_1MS)	/* ¿? ticks per second */

#define LED_TOGGLE_100MS	(100)
#define LED_TOGGLE_500MS	(500)
#define LED_TOGGLE_1000MS	(1000)
#define LED_TOGGLE_MS		(LED_TOGGLE_1000MS / TICKRATE_MS)




/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

#if (TEST == TP1_1)

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      /* Prendo el led azul */
      gpioWrite( LEDR, ON );

      delay(500);

      /* Apago el led azul */
      gpioWrite( LEDR, OFF );

      delay(500);

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/

#elif (TEST == TP1_2)


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   /* Variable para almacenar el valor de tecla leido */
   bool_t valor;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      valor = !gpioRead( TEC1 );
      gpioWrite( LEDB, valor );

      valor = !gpioRead( TEC2 );
      gpioWrite( LED1, valor );

      valor = !gpioRead( TEC3 );
      gpioWrite( LED2, valor );

      valor = !gpioRead( TEC4 );
      gpioWrite( LED3, valor );

      valor = !gpioRead( GPIO0 );
      gpioWrite( GPIO1, valor );

   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/

#elif (TEST == TP1_3)


/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ){

   static bool_t ledState = OFF;

   gpioMap_t led = (gpioMap_t)ptr;

   if( ledState ){
      ledState = OFF;
   }
   else{
      ledState = ON;
   }
   gpioWrite( led, ledState );
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar el conteo de Ticks con resolucion de 50ms (se ejecuta
      periodicamente una interrupcion cada 50ms que incrementa un contador de
      Ticks obteniendose una base de tiempos). */
   tickConfig( 50 );

   /* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
      simplemente una funcion que se ejecutara peri�odicamente con cada
      interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
      a una interrupcion.
      El segundo parametro es el parametro que recibe la funcion myTickHook
      al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
   */
   tickCallbackSet( myTickHook, (void*)LEDR );
   delay(1000);

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      tickCallbackSet( myTickHook, (void*)LEDG );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LEDB );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LED1 );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LED2 );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LED3 );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LEDR );
      delay(1000);
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
#elif (TEST == TP1_4)
volatile bool LED_Time_Flag = false;

/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ) {
	LED_Time_Flag = true;
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void) {

	/* ------------- INICIALIZACIONES ------------- */
	uint32_t LED_Toggle_Counter = 0;

	/* Inicializar la placa */
	boardConfig();

	/* Inicializar el conteo de Ticks con resolucion de 1ms (se ejecuta
       periodicamente una interrupcion cada TICKRATE_MS que incrementa un contador de
       Ticks obteniendose una base de tiempos). */
	tickConfig( TICKRATE_MS );

	/* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
       simplemente una funcion que se ejecutara peri�odicamente con cada
       interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
       a una interrupcion.
       El segundo parametro es el parametro que recibe la funcion myTickHook
       al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
	*/
	tickCallbackSet( myTickHook, (void*)NULL );

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		__WFI();

		if (LED_Time_Flag == true) {
			LED_Time_Flag = false;

			if (LED_Toggle_Counter == 0) {
				LED_Toggle_Counter = LED_TOGGLE_MS;
				gpioToggle(LED3);
			}
			else
				LED_Toggle_Counter--;
		}
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
       por ningun S.O. */
	return 0 ;
}


#elif (TEST == TP1_5)

volatile bool LED_Time_Flag = false;


/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ) {
	LED_Time_Flag = true;
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void) {

	/* ------------- INICIALIZACIONES ------------- */
	uint32_t LED_Toggle_Counter = 0;

	/* Inicializar la placa */
	boardConfig();

	/* UART for debug messages. */
	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintString( "DEBUG c/sAPI\r\n" );

	/* Inicializar el conteo de Ticks con resolucion de 1ms (se ejecuta
       periodicamente una interrupcion cada TICKRATE_MS que incrementa un contador de
       Ticks obteniendose una base de tiempos). */
	tickConfig( TICKRATE_MS );

	/* Se agrega ademas un "tick hook" nombrado myTickHook. El tick hook es
       simplemente una funcion que se ejecutara peri�odicamente con cada
       interrupcion de Tick, este nombre se refiere a una funcion "enganchada"
       a una interrupcion.
       El segundo parametro es el parametro que recibe la funcion myTickHook
       al ejecutarse. En este ejemplo se utiliza para pasarle el led a titilar.
	*/
	tickCallbackSet( myTickHook, (void*)NULL );

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		__WFI();

		if (LED_Time_Flag == true) {
			LED_Time_Flag = false;

			if (LED_Toggle_Counter == 0) {
				LED_Toggle_Counter = LED_TOGGLE_MS;
				gpioToggle(LED3);
				debugPrintString( "LED Toggle\n" );
			}
			else
				LED_Toggle_Counter--;
		}
	}

	/* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
       por ningun S.O. */
	return 0 ;
}





#endif
