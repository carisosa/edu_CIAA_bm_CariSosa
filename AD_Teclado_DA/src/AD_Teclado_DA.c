/* Copyright 2016, Cari Sosa
 *  * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a little example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * CS
 * ---------------------------
 * Cari Sosa EXAMEN
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "AD_Teclado_DA.h"       /* <= own header */
#include "stdint.h"
#include "chip.h"
#include "da.h"
#include "timer.h"
#include "vector.h"
#include "Teclas.h"
#include "led.h"
#include "da.h"
#include "uart2.h"

/*==================[macros and definitions]=================================*/
#define ganancia_p 2
#define ganancia_n 0.5
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
uint8_t canal=1;
uint32_t num=0;
uint32_t Tmuestreo=100;
uint16_t datoAD;
uint32_t datoDA;
uint32_t datoDA_min=0;
uint32_t datoDA_max=1024;

uint32_t amplitud_max=1024;
uint32_t amplitud_min=0;
uint32_t amplitud;

uint32_t br=115200;
uint8_t letra;
uint8_t cadena1[] = "AUMENTO DE GANANCIA";
uint8_t NB1=19;
uint8_t cadena2[] = "DISMINUYO GANANCIA";
uint8_t NB2=18;
uint8_t cadena3[] = "MUTE";
uint8_t NB3=4;
uint8_t cadena4[] = "SAT";
uint8_t NB4=4;


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */

/*Para una frecuencia de muestreo de 10[HZ] es necesario que el timer interrumpa cada 100[ms] y realice la conversión AD*/
/*Adquisición de señal analogica con el ADC0 canal 1*/
void ISR_RTITimer(){
	clearFlag();
	prendeLed(GREEN);
	toggleLed(RED); //cambia el estado del LED1 cada vez que toma una muestra

	select_mode();
	leer_dato(canal,&datoAD);
	datoDA=datoAD; //<- chequear que sea realmente el dato y no la dirección de memoria!!

	cargar_valor(datoDA);
	amplitud=datoDA;
}

int main(void)
{
	initGPIOswitches();
	initLeds();
	initad(canal,num);

	initda();
	inituart2(br);

	initRTItimer();
	configInterval_ms(Tmuestreo); //el timer interrumpe cada 100[ms]


	while(1){


		uint8_t TeclaPresionada = scanKeyboard();
/*escanea continuamente el teclado y solo si alguna tecla es presionada avanza*/

		if(TeclaPresionada!=0){
/*podría deshabilitar el timer mientras analiza las condiciones
 * pero la frecuencia de muestreo es baja por lo que asumo que no voy a tener problemas*/

/*Si la tecla presionada es la Tecla 1 debo aumentar la ganancia e indicar la acción por consola*/
/*LEER!!! INTERPRETE QUE SE DEVIA VARIAR LA AMPLITUD DEL DATO!
 * ES DECIR QUE SE BEDE MANTENER LA TECLA PRESIONADA PARA VER LA MODIFICACIÓN EN LA SEÑAL*/
		if(TeclaPresionada&(1<<0)){
			amplitud=(ganancia_p*amplitud);
			cargar_valor(amplitud);
			UARTenviar(cadena1,NB1);
		}
		else{
/*Si la tecla presionada es la Tecla 2 debo disminuir la ganancia e indicar la acción por consola*/
			if(TeclaPresionada&(1<<1)){
				amplitud=(ganancia_n*amplitud);
				cargar_valor(amplitud);
				UARTenviar(cadena2,NB2);
			}
			else {
/*Si la tecla presionada es la Tecla 3 debo llevar la señal de salida a cero e indicar la acción por consola*/
				if(TeclaPresionada&(1<<2)){
					cargar_valor(datoDA_min);
					UARTenviar(cadena3,NB3);
				}

				else {
/*Si la tecla presionada es la Tecla 4 debo llevar la señal de salida al estado saturado e indicar la acción por consola*/
					if(TeclaPresionada&(1<<3)){
						cargar_valor(datoDA_max);
						UARTenviar(cadena4,NB4);
					}

				}
		   }
		 }

		}
	}



	return 0;
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
