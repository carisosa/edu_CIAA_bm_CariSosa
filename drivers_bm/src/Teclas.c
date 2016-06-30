/* Copyright 2016, Cari Sosa
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

/** \brief Blinking Bare Metal driver Teclas
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
 *	CS			Cari Sosa
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
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif*/
#include "Teclas.h"
#include "chip.h"

/*==================[macros and definitions]=================================*/

#define GPIO_0 0
#define GPIO_1 1
#define GPIO_2 2
#define GPIO_3 3

#define MASK_TEC1 (1<<4)
#define MASK_TEC2 (1<<8)
#define MASK_TEC3 (1<<9)
#define MASK_TEC4 (1<<9)

#define MASK_fil0 (1<<0)
#define MASK_fil1 (1<<1)
#define MASK_fil2 (1<<2)
#define MASK_fil3 (1<<3)

#define MASK_col1 (1<<8)
#define MASK_col2 (1<<12)
#define MASK_col3 (1<<13)

#define MASK_teclas (1<<0)|(1<<1)|(1<<2)|(1<<3)

/*==================[internal data declaration]==============================*/

const GPIOO SW1={0,4};
const GPIOO *pSW1 = &SW1;

const GPIOO SW2={0,8};
const GPIOO *pSW2 = &SW2;

const GPIOO SW3={0,9};
const GPIOO *pSW3 = &SW3;

const GPIOO SW4={1,9};
const GPIOO *pSW4 = &SW4;

const switches teclas={1,2,4,8};

const GPIOO f0={2,0};
const GPIOO *pf0 = &f0;

const GPIOO f1={2,1};
const GPIOO *pf1 = &f1;

const GPIOO f2={2,2};
const GPIOO *pf2 = &f2;

const GPIOO f3={2,3};
const GPIOO *pf3 = &f3;

const GPIOO c1={1,8};
const GPIOO *pc1 = &c1;

const GPIOO c2={3,12};
const GPIOO *pc2 = &c2;

const GPIOO c3={3,13};
const GPIOO *pc3 = &c3;

#define TECLA_A (1<<0)
#define TECLA_B (1<<1)
#define TECLA_C (1<<2)
#define TECLA_D (1<<3)

uint8_t matriz[4][3]={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};

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

void initGPIOswitches(void){

	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_SCU_PinMux(1,0,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1_0 en GPIO 0[4], Tecla 1 */
	Chip_SCU_PinMux(1,1,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1_1 en GPIO 0[8], Tecla 2 */
	Chip_SCU_PinMux(1,2,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1_2 en GPIO 0[9], Tecla 3 */
	Chip_SCU_PinMux(1,6,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P1_6 en GPIO 1[9], Tecla 4 */

	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_0,MASK_TEC1|MASK_TEC2|MASK_TEC3,ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_1,MASK_TEC4,ENTRADA);
};

/**init para teclado matricial*/
 void initGPIOswitchesMat(void){
	 Chip_GPIO_Init(LPC_GPIO_PORT);

	 Chip_SCU_PinMux(4,0,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P4_0 en GPIO 2[0], fil 0 */
	 Chip_SCU_PinMux(4,1,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P4_1 en GPIO 2[1], fil 1 */
	 Chip_SCU_PinMux(4,2,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P4_2 en GPIO 2[2], fil 2 */
	 Chip_SCU_PinMux(4,3,MD_PUP|MD_EZI|MD_ZI,FUNC0);/* mapea P4_3 en GPIO 2[3], fil 3 */

	 Chip_SCU_PinMux(1,5,MD_PDN|MD_EZI|MD_ZI,FUNC0);/* mapea P1_5 en GPIO 1[8], col 0 */
	 Chip_SCU_PinMux(7,4,MD_PDN|MD_EZI|MD_ZI,FUNC0);/* mapea P7_4 en GPIO 3[12], col 1 */
	 Chip_SCU_PinMux(7,5,MD_PDN|MD_EZI|MD_ZI,FUNC0);/* mapea P7_5 en GPIO 3[13], col 2 */

	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_2,MASK_fil0|MASK_fil1|MASK_fil2|MASK_fil3,ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_1,MASK_col1,SALIDA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT,GPIO_3,MASK_col2|MASK_col3,SALIDA);

 };

 /*La función devuelve un 1 si hay una tecla presionada*/
 uint8_t CheckKeyboardMat(void){
	 uint8_t PresseKey=0;
	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc1->numPort,pc1->numPin,ENTRADA);
	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc2->numPort,pc2->numPin,ENTRADA);
	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc3->numPort,pc3->numPin,ENTRADA);
	 if(~((Chip_GPIO_GetPortValue(LPC_GPIO_PORT, pf0->numPort)) & (MASK_teclas))!=0){
		 PresseKey=1;
	 }
	 else{
		 PresseKey=0;
	 }

	 return PresseKey;
 };
 /*En la aplicación se debe asegurar que se llame a scanKeyboardMat bajo la presunción de tecla apretada*/
 uint8_t scanKeyboardMat(void){
	 uint32_t Value=0;
	 uint8_t Fila=0;
	 uint8_t Columna=3;
	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc1->numPort,pc1->numPin, BAJO);
	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc2->numPort,pc2->numPin, ALTO);
	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc3->numPort,pc3->numPin, ALTO);
	 if((Value=~(Chip_GPIO_GetPortValue(LPC_GPIO_PORT, pf0->numPort)) & (MASK_teclas))!=0){
	 		 Columna=1;
	 	 }
	 else{
		 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc1->numPort,pc1->numPin, ALTO);
		 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc2->numPort,pc2->numPin, BAJO);
		 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc3->numPort,pc3->numPin, ALTO);
	 		if(((Value=~(Chip_GPIO_GetPortValue(LPC_GPIO_PORT, pf0->numPort)) & (MASK_teclas))!=0)){
	 			Columna=2;
	 		}
	 		else{
	 			Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc1->numPort,pc1->numPin, ALTO);
	 			Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc2->numPort,pc2->numPin, ALTO);
	 			Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc3->numPort,pc3->numPin, BAJO);
	 		 			if(((Value=~(Chip_GPIO_GetPortValue(LPC_GPIO_PORT, pf0->numPort)) & (MASK_teclas))!=0)){
	 		 			 			Columna=3;
	 		 			 		}
	 		 			else {
	 		 				return ERROR;
	 		 			}
	 		     }
	 }
	switch(Value){
	  			case TECLA_A : Fila=0; break;
	  		    case TECLA_B : Fila=1; break;
	  		    case TECLA_C : Fila=2; break;
	  		    case TECLA_D : Fila=3; break;
	  		    }
	return (Columna+Fila*3);
 };


/*
     Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc1->numPort,pc1->numPin, estado);

	 Value=~(Chip_GPIO_GetPortValue(LPC_GPIO_PORT, pf0->numPort)) & (MASK_teclas);
	 	 Entra si alguna tecla está presionada
	 	 if(!Value)
	 	     switch(Value){
	 	     case TECLA_A : return TEC2;
	 	     case TECLA_B : return TEC5;
	 	     case TECLA_C : return TEC8;
	 	     case TECLA_D : return TEC11;
	 	     }

	 Chip_GPIO_WritePortBit(LPC_GPIO_PORT, pc2->numPort,pc2->numPin, estado);
	 Value=~(Chip_GPIO_GetPortValue(LPC_GPIO_PORT, pf0->numPort)) & (MASK_teclas);
	 	 	 Entra si alguna tecla está presionada
	 	 	 if(!Value)
	 	 	     switch(Value){
	 	 	     case TECLA_A : return TEC3;
	 	 	     case TECLA_B : return TEC6;
	 	 	     case TECLA_C : return TEC9;
	 	 	     case TECLA_D : return TEC13;
	 	 	     }
*/



/* DetectaTecla recibe como parámetro el número de tecla y chequea el estado*/
uint8_t scanKeyboard(void){
	uint8_t switchPressed = 0;

	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, pSW1->numPort,pSW1->numPin))
		/*devuelve cero si la tecla está presionada*/
	switchPressed |= teclas.SWITCH1; /*(operaciones de bits)*/
	/*Si la tecla está presionada coloca un uno en el bit de switchPressed correspondiente a esa tecla*/
	else
	switchPressed &= ~teclas.SWITCH1;
	/*si no está presionada pone el bit correspondiente en 0,
	 * podría no hacer nada y confiar en que queda en 0 porque le doy ese valor al comienzo de la función*/

	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, pSW2->numPort,pSW2->numPin))
	switchPressed |= teclas.SWITCH2;
	else
	switchPressed &= ~teclas.SWITCH2;

	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, pSW3->numPort,pSW3->numPin))
		switchPressed |= teclas.SWITCH3;
		else
		switchPressed &= ~teclas.SWITCH3;

	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, pSW4->numPort,pSW4->numPin))
		switchPressed |= teclas.SWITCH4;
		else
		switchPressed &= ~teclas.SWITCH4;

	return switchPressed;

 };



/*uint8_t scanswitch1(void){
	if(!Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, pSW1->numPort,pSW1->numPin))
			/*devuelve cero si la tecla está presionada*/
		/*switchPressed |= teclas.SWITCH1; /*(operaciones de bits)*/
		/*Si la tecla está presionada coloca un uno en el bit de switchPressed correspondiente a esa tecla*/
		/*else
		switchPressed &= ~teclas.SWITCH1;
	return teclas.SWITCH1;

};*/
/*lee el estado del puerto que recibe como parámetro*/
/*Chip_GPIO_ReadValue(LPC_GPIO_PORT, p);*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

