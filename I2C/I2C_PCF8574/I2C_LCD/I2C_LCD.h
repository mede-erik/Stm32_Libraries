/**
 * @author Medeossi Erik
 * @date 15/02/2023
 * @version 0.1.2
 * @details Derived from Mohamed Yaqoob's repository
 * @link Mohamed Yaqoob: https://github.com/MYaqoobEmbedded/STM32-Tutorials
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H   

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint8_t address;
} I2C_LCD_HandleTypeDef;

bool lcd16x2_i2c_auto_init(I2C_LCD_HandleTypeDef *lcd, I2C_HandleTypeDef *pI2cHandle);
bool lcd16x2_i2c_addr_init(I2C_LCD_HandleTypeDef *lcd, I2C_HandleTypeDef *pI2cHandle, int addr);
void lcd16x2_i2c_setCursor(I2C_LCD_HandleTypeDef *lcd, uint8_t row, uint8_t col);
void lcd16x2_i2c_1stLine(I2C_LCD_HandleTypeDef *lcd);
void lcd16x2_i2c_2ndLine(I2C_LCD_HandleTypeDef *lcd);
void lcd16x2_i2c_TwoLines(I2C_LCD_HandleTypeDef *lcd);
void lcd16x2_i2c_OneLine(I2C_LCD_HandleTypeDef *lcd);
void lcd16x2_i2c_cursorShow(I2C_LCD_HandleTypeDef *lcd, bool state);
void lcd16x2_i2c_clear(I2C_LCD_HandleTypeDef *lcd);
void lcd16x2_i2c_display(I2C_LCD_HandleTypeDef *lcd, bool state);
void lcd16x2_i2c_shiftRight(I2C_LCD_HandleTypeDef *lcd, uint8_t offset);
void lcd16x2_i2c_shiftLeft(I2C_LCD_HandleTypeDef *lcd, uint8_t offset);
void lcd16x2_i2c_printf(I2C_LCD_HandleTypeDef *lcd, const char *str, ...);

