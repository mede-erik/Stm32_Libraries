/**
 * @author Medeossi Erik
 * @date 05/1/2022
 * @link https://github.com/mede-erik/Stm32_Libraries
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
	return kelvin - 273, 15;
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