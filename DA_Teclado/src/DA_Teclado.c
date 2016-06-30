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
 * ACTIVIDAD 10
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "DA_Teclado.h"       /* <= own header */
#include "timer.h"
#include "stdint.h"
#include "chip.h"
#include "vector.h"
#include "led.h"
#include "da.h"
#include "Teclas.h"





/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

uint32_t cont=0;
uint32_t datoDAC;
uint8_t Amplitud=128;
uint8_t Periodo=100;
uint8_t paso;
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

void ISR_RTITimer(){
	clearFlag();
	toggleLed(RED);
	cont++;
	if(cont==Amplitud){
		cont=0;
	}
	cargar_valor(cont);


}

int main(void)
{
	initLeds();
	initda();
	initGPIOswitches();
	initRTItimer();
	paso=(Periodo*1000)/Amplitud;
	configInterval_ms(paso);
/*
 * TEC1-> Aumenta amplitud
 * TEC2-> Disminuye amplitud
 * TEC3-> Aumenta periodo
 * TEC4-> Disminuye periodo*/


  while(1){
	  uint8_t TeclaPresionada = scanKeyboard();

	  if(TeclaPresionada&(1<<0)){
		  if(Amplitud<1024){
			  Amplitud+=128;
		  }
		  else Amplitud=1024;
	  }

	  if(TeclaPresionada&(1<<1)){
		  if(Amplitud>128){
			  Amplitud = Amplitud-128;
		  }
		  else Amplitud=128;
	  }

  }

			return 0;
}


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
