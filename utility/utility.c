/*
 * Author: Medeossi Erik
 */

// Includes
#include <stdio.h>
#include <stdlib.h>

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
