/*
 * Author: Medeossi Erik
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief transforms a number belonging to a particular range and transposes it into a new range of numbers
 *
 * @param x The number to transpose
 * @param in_min the minimum value of the first interval
 * @param in_max the maximum value of the first interval
 * @param out_min the minimum value of the second interval
 * @param out_max the maximum value of the second interval
 * @return long
 */

long map(long x, long in_min, long in_max, long out_min, long out_max)
{

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void swap(int *p_a, int *p_b)
{
	int t;

	t = *p_a;
	*p_a = *p_b;
	*p_b = t;
}

float kelvin_to_celsius(float kelvin)
{
	return kelvin - 273, 15;
}

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