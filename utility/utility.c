/**
 * @author Medeossi Erik
 * @date 05/1/2022
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Re-maps a number from one range to another
 *
 * @param x the number to map
 * @param in_min the lower bound of the value’s current range
 * @param in_max the upper bound of the value’s current range
 * @param out_min the lower bound of the value’s target range
 * @param out_max the upper bound of the value’s target range
 * @return long
 */
long map(long x, long in_min, long in_max, long out_min, long out_max)
{

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * @brief swap the two variables
 *
 * @param p_a
 * @param p_b
 */
void swap(int *p_a, int *p_b)
{
	int t;

	t = *p_a;
	*p_a = *p_b;
	*p_b = t;
}

/**
 * @brief converts kelvin degrees to celsius
 *
 * @param kelvin
 * @return float
 */
float kelvin_to_celsius(float kelvin)
{
	return kelvin - 273.15;
}

/**
 * @brief converts kelvin degrees to fahrenheit
 *
 * @param kelvin
 * @return float
 */
float kelvin_to_Fahrenheit(float kelvin)
{
	return (kelvin_to_celsius(kelvin)) * (9 / 5) + 32;
}

/**
 * @brief I take the upper bits of a 16-bit integer in order to be able to place a 16-bit integer in two 8-bit integers
 *
 * @param a 16-bit int to split
 * @return uint8_t upper bits of variable a
 */
uint8_t uint16_to_uint8_up_bits(uint16_t a)
{
	uint8_t b;

	b = (uint8_t)(a >> 8);

	return b;
}

/**
 * @brief I take the lower bits of a 16-bit integer in order to be able to place a 16-bit integer in two 8-bit integers
 *
 * @param a 16-bit int to split
 * @return uint8_t lower bits of variable a
 */
uint8_t uint16_to_uint8_down_bits(uint16_t a)
{
	uint8_t b;

	b = (uint8_t)(a >> 8);

	return b;
}

/**
 * @brief Converts an RGB color with 8 bits per channel (RGB888) to 16-bit format (RGB565).
 *
 * This function takes as input the values of the red, green, and blue channels (each 8 bits)
 * and converts them to the RGB565 format, commonly used in 16-bit color displays.
 * In the RGB565 format, red is represented with 5 bits, green with 6 bits, and blue with 5 bits.
 *
 * The conversion is performed as follows:
 * - The 5 most significant bits of red (r & 0xF8) are placed in bits 11-15 of the result.
 * - The 6 most significant bits of green (g & 0xFC) are placed in bits 5-10 of the result.
 * - The 5 most significant bits of blue (b >> 3) are placed in bits 0-4 of the result.
 *
 * @param r Value of the red channel (0-255).
 * @param g Value of the green channel (0-255).
 * @param b Value of the blue channel (0-255).
 * @return uint16_t Color value in RGB565 format (16 bits).
 */

uint16_t RGB_to_16bit_RGB(uint8_t r, uint8_t g, uint8_t b)
{
	// Convert RGB888 to RGB565
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}
