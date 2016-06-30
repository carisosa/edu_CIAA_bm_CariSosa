/* Copyright 2016, XXXXXXXXX  
 * All rights reserved.
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
/*#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)*/
#include "chip.h"
/*#elif (mk60fx512vlq15 == CPU)
#else
#endif*/
#include "timer.h"
#include "stdint.h"
/*#include "cmsis_43xx.h" No debería hacer esto*/

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
uint32_t contador;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void initRTItimer(void){
/*Inicializa el timer
 * Le paso la dirección base del RTI timer definida en chip.h*/
	Chip_RIT_Init(LPC_RITIMER);
	NVIC_EnableIRQ(RITIMER_IRQn);
};

/*Configuración del intervalo de [ms]*/
void configInterval_ms(uint32_t interval){

	Chip_RIT_SetTimerInterval(LPC_RITIMER,interval);
};

void configInterval_us(uint32_t interval){
	void Chip_RIT_SetTimerInterval(LPC_RITIMER_T *pRITimer, uint32_t time_interval)
	{
		uint32_t cmp_value_us;

		/* Determine aapproximate compare value based on clock rate and passed interval */
		cmp_value_us = (Chip_Clock_GetRate(CLK_MX_RITIMER) / 1000000) * time_interval;

		/* Set timer compare value */
		Chip_RIT_SetCOMPVAL(pRITimer, cmp_value_us);

		/* Set timer enable clear bit to clear timer to 0 whenever
		   counter value equals the contents of RICOMPVAL */
		Chip_RIT_EnableCTRL(pRITimer, RIT_CTRL_ENCLR);
	}


};

void clearFlag(void){
	Chip_RIT_ClearInt(LPC_RITIMER);
};

/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

