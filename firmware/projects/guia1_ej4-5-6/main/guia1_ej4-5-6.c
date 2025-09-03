/*! @mainpage Template
 *
 * @section genDesc General Description
 *
 * This section describes how the program works.
 *
 * <a href="https://drive.google.com/...">Operation Example</a>
 *
 * @section hardConn Hardware Connection
 *
 * |    Peripheral  |   ESP32   	|
 * |:--------------:|:--------------|
 * | 	PIN_X	 	| 	GPIO_X		|
 *
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 12/09/2023 | Document creation		                         |
 *
 * @author Galiani Fiorella (fiorella.galiani@ingenieria.uner.edu.ar)
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include "gpio_mcu.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

typedef struct
{
    gpio_t pin;
    io_t dir;
} gpioConf_t;

/*==================[internal functions declaration]=========================*/

// funcion punto 4
int8_t convertToBcdArray(uint32_t data, uint8_t digits, uint8_t *bcd_number)
{

    // Convertir a BCD desde el dígito menos significativo
    for (int i = digits - 1; i >= 0; i--)
    {
        bcd_number[i] = data % 10; // voy guardando el ultimo numero
        data /= 10;

        // se repite hasta sacar todos los numeros
    }

    return 0;
}

// función punto 5
void setBcdDigit(uint8_t bcd_digit, gpioConf_t *pins)
{
    for (int i = 0; i < 4; i++)
    {
        uint8_t bit = (bcd_digit >> i) & 0x01; // extraer bit i - corro a la derecha i posiciones
        if (bit)
            GPIOOn(pins[i].pin); // enciende GPIO si el bit es 1 - pone alto
        else
            GPIOOff(pins[i].pin); // apaga GPIO si el bit es 0 - pone bajo
    }
}

// funcion punto 6
void displayNumber(uint32_t data, uint8_t digits, gpioConf_t *seg_pins, gpioConf_t *digit_pins)
{

    uint8_t digitos[3];

    // convertir el numero a arreglo BCD
    convertToBcdArray(data, digits, digitos);

    // poner en alto o en bajo
    for (int i = 0; i < digits; i++)
    {
        setBcdDigit(digitos[i], seg_pins);
        GPIOOn(digit_pins[i].pin);
        GPIOOff(digit_pins[i].pin);
    }
}

/*==================[external functions definition]==========================*/

void app_main(void)
{

    // uint32_t number = 12345; //numero de prueba
    // uint8_t digits = 6; //numero de digitos q voy a guardar
    // uint8_t bcd[6]; //arreglo donde se guardan

    // convertToBcdArray(number, digits, bcd);

    // printf("Número convertido a BCD:\n");
    // for (int i = 0; i < digits; i++) {
    //     printf("%d ", bcd[i]);  // imprimir cada dígito
    // }
    // printf("\n");

    gpioConf_t bcdPins[4] = {
        {GPIO_20, GPIO_OUTPUT}, // b0
        {GPIO_21, GPIO_OUTPUT}, // b1
        {GPIO_22, GPIO_OUTPUT}, // b2
        {GPIO_23, GPIO_OUTPUT}  // b3

    };

    gpioConf_t bcdPins2[3] = {
        {GPIO_19, GPIO_OUTPUT}, // digito 1
        {GPIO_18, GPIO_OUTPUT}, // digito 2
        {GPIO_9, GPIO_OUTPUT},  // digito 3
    };

    for (int i = 0; i < 4; i++)
    {
        GPIOInit(bcdPins[i].pin, bcdPins[i].dir);
    }

    for (int i = 0; i < 3; i++)
    {
        GPIOInit(bcdPins2[i].pin, bcdPins2[i].dir);
    }

    displayNumber(586, 3, bcdPins, bcdPins2);

    //  setBcdDigit(4, bcdPins);
}
/*==================[end of file]============================================*/