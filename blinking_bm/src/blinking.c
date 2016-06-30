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
 * CS     Cari Sosa
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "blinking.h"       /* <= own header */
#include "led.h"
#include "Teclas.h"
#include "stdint.h"
#include "chip.h"
#include "vector.h"

/*==================[macros and definitions]=================================*/
#define DELAY 3000000
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

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

 volatile uint32_t var;
 volatile uint32_t ms;
 /*volatile uint8_t contR=0;
 volatile uint8_t contG=0;
 volatile uint8_t contB=0;
 volatile uint8_t CTr;
 volatile uint8_t CTg;
 volatile uint8_t CTb;*/

int main(void)
{
   /* perform the needed initialization here */
			/*CTr=100;
			CTg=50;
			CTb=10;*/
			ms=1;
			/*initLeds();*/
			initGPIOswitches();
			initRTItimer();
			configIntervalms(ms);

/*teclado matricial*/



/* Test Led multicolor*/

			/*prendeLed(GREEN);
			prendeLed(YELLOW);
			prendeLed(RED);
			prendeLed_RGB(RED);
			prendeLed_RGB(BLUE);*/


/*test Driver led*/
			/*while (1){
							prendeLed(GREEN);
							for (var=DELAY; var!=0; var--);
							apagaLed(GREEN);
							prendeLed(YELLOW);
							for (var=DELAY; var!=0; var--);
							apagaLed(YELLOW);
							prendeLed(RED);
							for (var=DELAY; var!=0; var--);
							apagaLed(RED);
							toggleLed_RGB(BLUE);
							for (var=DELAY; var!=0; var--);
							toggleLed_RGB(BLUE);

}*/

/*test driver teclas*/

			/*while(1){
			uint8_t TeclaPresionada = scanKeyboard();

			if(TeclaPresionada&(1<<0))
				prendeLed_RGB(WHITE);
			else apagaLed_RGB(WHITE);
			if(TeclaPresionada&(1<<1))
				prendeLed(RED);
			else apagaLed(RED);
			if(TeclaPresionada&(1<<2))
				prendeLed(YELLOW);
			else apagaLed(YELLOW);
			if(TeclaPresionada&(1<<3))
				prendeLed(GREEN);
			else apagaLed(GREEN);
			}*/

/*test timer*/
			/*while (1){
			/*uint8_t Tecla1 = scanswitch1();
			if(Tecla1&(1<<0))*/

				/*if(contR>100){
				toggleLed_RGB(RED);
				contR=0;}
				if(contG>50){
				toggleLed_RGB(GREEN);
				contG=0;}
				if(contB>50){
				toggleLed_RGB(BLUE);
				contB=0;}*/


			/*if(contR>CTr){
			toggleLed_RGB(RED);
			contR=0;
			CTr-=10;
				if(CTr==0)
					CTr=100;
			}
			if(contG>CTg){
			toggleLed_RGB(GREEN);
			contG=0;
			CTg-=10;
				if(CTg==0)
				CTg=100;
			}
			if(contB>CTb){
			toggleLed_RGB(BLUE);
			contB=0;
			CTb-=10;
				if(CTb==0)
				CTb=100;

			}*/



			return 0;
}

/*void ISR_RTITimer(){

	contR+=1;
	contG+=1;
	contB+=1;


	clearFlag();
};*/

/*void ISR_RTITimer(){

	toggleLed(RED);
	toggleLed(GREEN);

	clearFlag();
};*/

/*void ISR_RTITimer(){

	toggleLed_RGB(WHITE);
	toggleLed(RED);
	toggleLed(YELLOW);
	toggleLed(GREEN);

	clearFlag();
};*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
