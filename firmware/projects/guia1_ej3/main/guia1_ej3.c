/*! @mainpage Blinking switch
 *
 * \section genDesc General Description
 *
 * This example makes LED_1 and LED_2 blink if SWITCH_1 or SWITCH_2 are pressed.
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 20/08/2025 | Document creation		                         |
 *
 * @author Galiani Fiorella (fiorella.galiani@ingenieria.uner.edu.ar)
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "switch.h"

/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 100
#define ON 1
#define OFF 0
#define TOGGLE 2

/*==================[internal data definition]===============================*/
struct leds
{
	uint8_t mode;	  // ON, OFF, TOGGLE
	uint8_t n_led;	  // indica el número de led a controlar
	uint8_t n_ciclos; // indica la cantidad de ciclos de encendido/apagado
	uint16_t periodo; // indica el tiempo de cada ciclo
} mys_leds;

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
void controlar_led(struct leds *my_leds)
{

	// Caso encender led
	if (my_leds->mode == ON)
	{
		if (my_leds->n_led == 1)
			LedOn(LED_1);
		else if (my_leds->n_led == 2)
			LedOn(LED_2);
		else if (my_leds->n_led == 3)
			LedOn(LED_3);
	}

	// Caso apagar led
	else if (my_leds->mode == OFF)
	{
		if (my_leds->n_led == 1)
			LedOff(LED_1);
		else if (my_leds->n_led == 2)
			LedOff(LED_2);
		else if (my_leds->n_led == 3)
			LedOff(LED_3);
	}

	// Caso parpadear led

	else if (my_leds->mode == TOGGLE)
	{
		for (int i = 0; i < my_leds->n_ciclos; i++)
		{
			if (my_leds->n_led == 1)
				LedToggle(LED_1);
			else if (my_leds->n_led == 2)
				LedToggle(LED_2);
			else if (my_leds->n_led == 3)
				LedToggle(LED_3);
			for (int j = 0; j < my_leds->periodo / CONFIG_BLINK_PERIOD; j++)
			{
				vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
			}
		}
	}
}

void app_main(void)
{
	LedsInit();
	mys_leds.mode = OFF;
	mys_leds.n_led = 2;
	mys_leds.n_ciclos = 5;
	mys_leds.periodo = 1000;

	controlar_led(&mys_leds);

	while (1)
	{
		vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
	}
}
