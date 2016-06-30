/* Copyright 2016
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

#ifndef LED_H
#define LED_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *	CS			Cari Sosa
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "chip.h"

/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

#define ENTRADA 	0
#define SALIDA 		1
#define RED 		1
#define GREEN 		2
#define YELLOW		3
#define BLUE 		4
#define WHITE       5

/*==================[typedef]================================================*/

/* Definir las referencias de las estructuras a los puertos*/

typedef struct{
	uint8_t numPort;
	uint8_t numPin;
}GPIO;

typedef struct{
    uint8_t numPort;
    GPIO red;
    GPIO green;
    GPIO blue;
}ledRGB;

typedef struct{
	GPIO red;
	GPIO yellow;
	GPIO green;
}led;

/*==================[external data declaration]==============================*/
/*
 */

/*a los extern los declaramos en otro lado. lo uso cuando necesito en el .h definir una variable global.
 * que podr� ser usada en los .c
 * ser�a mejor evitar esto!
 * Para evitar defino structura en el .c
 * No son variables igual, las podria declarar como constante en el .c,
 * no tendr�a sentido en el .h para que querr�an conocerla todos los que usan el driver?*/
/*extern led edu_ciaa_led;
extern led *p_edu_ciaa_led;
extern ledRGB edu_ciaa_ledRGB;
extern ledRGB *p_edu_ciaa_ledRGB;*/

/*
 * typedef struct{
    GPIO red = {5,0};
    GPIO green = {5,1};
    GPIO blue = {5,2};
}ledRGB;

typedef struct{
	GPIO red = {0,14};
	GPIO yellow = {1,11};
	GPIO green = {1,12};
}led;
 *
 * */



void apagaLeds(void);

void enciendeLeds(void);

void initLeds(void);

void prendeLed(uint8_t color);

void apagaLed(uint8_t color);

void prendeLed_RGB(uint8_t color);

void apagaLed_RGB(uint8_t color);

void toggleLed(uint8_t color);

void toggleLed_RGB(uint8_t color);


/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef LED_H */
