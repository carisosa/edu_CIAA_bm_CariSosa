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
#include "uart2.h"
#include "stdint.h"
/*#include "cmsis_43xx.h" No deber�a hacer esto*/

/*==================[macros and definitions]=================================*/
#define UART2_PIN_PKG 7
#define UART2_PIN_TXD 1
#define UART2_PIN_RXD 2



/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void inituart2(uint32_t baud){
	/*select DAC function*/
	Chip_SCU_PinMux(UART2_PIN_PKG, UART2_PIN_TXD, MD_PDN, FUNC6);
	Chip_SCU_PinMux(UART2_PIN_PKG, UART2_PIN_RXD, MD_PLN| MD_EZI |MD_ZI,FUNC6);

	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaud(LPC_USART2, baud);
	Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN|UART_FCR_TRG_LEV0);

	Chip_UART_TXEnable(LPC_USART2);

}

uint8_t UARTleerbyte(void){
	uint8_t dato = Chip_UART_ReadByte(LPC_USART2);
	return dato;
}

void UARTenviar(uint8_t *data, uint8_t numByte){

	while(numByte!=0){
	if((Chip_UART_CheckBusy(LPC_USART2))==RESET){
		Chip_UART_Send((LPC_USART_T *)LPC_USART2,data,1);
	    numByte --;
	    data++;}
	}

}





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

