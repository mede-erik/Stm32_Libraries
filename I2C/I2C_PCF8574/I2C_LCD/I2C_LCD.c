/**
 * @author Medeossi Erik
 * @date 15/02/2023
 * @version 0.1.2
 * @details Derived from Mohamed Yaqoob's repository
 * @link Mohamed Yaqoob: https://github.com/MYaqoobEmbedded/STM32-Tutorials
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#include "I2C_LCD.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* LCD Commands */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

/* Commands bitfields */
#define LCD_ENTRY_SH 0x01
#define LCD_ENTRY_ID 0x02
#define LCD_DISPLAY_B 0x01
#define LCD_DISPLAY_C 0x02
#define LCD_DISPLAY_D 0x04
#define LCD_SHIFT_RL 0x04
#define LCD_SHIFT_SC 0x08
#define LCD_FUNCTION_F 0x04
#define LCD_FUNCTION_N 0x08
#define LCD_FUNCTION_DL 0x10

/* I2C Control bits */
#define LCD_RS (1 << 0)
#define LCD_RW (1 << 1)
#define LCD_EN (1 << 2)
#define LCD_BK_LIGHT (1 << 3)

/* Predefined I2C addresses for auto-detection */
#define LCD_I2C_ADDR_0 0x4E
#define LCD_I2C_ADDR_1 0x7E
#define LCD_I2C_ADDR_2 0x4C

static void lcd_sendCommand(I2C_LCD_HandleTypeDef *lcd, uint8_t command)
{
    const uint8_t cmd_lo = (0xF0 & (command << 4));
    const uint8_t cmd_hi = (0xF0 & command);
    uint8_t i2cData[4] =
    {
        cmd_hi | LCD_EN | LCD_BK_LIGHT,
        cmd_hi | LCD_BK_LIGHT,
        cmd_lo | LCD_EN | LCD_BK_LIGHT,
        cmd_lo | LCD_BK_LIGHT,
    };
    HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address, i2cData, 4, 200);
}

static void lcd_sendData(I2C_LCD_HandleTypeDef *lcd, uint8_t data)
{
    const uint8_t data_lo = (0xF0 & (data << 4));
    const uint8_t data_hi = (0xF0 & data);
    uint8_t i2cData[4] =
    {
        data_hi | LCD_EN | LCD_BK_LIGHT | LCD_RS,
        data_hi | LCD_BK_LIGHT | LCD_RS,
        data_lo | LCD_EN | LCD_BK_LIGHT | LCD_RS,
        data_lo | LCD_BK_LIGHT | LCD_RS,
    };
    HAL_I2C_Master_Transmit(lcd->hi2c, lcd->address, i2cData, 4, 200);
}

static void lcd_init_sequence(I2C_LCD_HandleTypeDef *lcd)
{
    HAL_Delay(45);
    lcd_sendCommand(lcd, 0x30);
    HAL_Delay(5);
    lcd_sendCommand(lcd, 0x30);
    HAL_Delay(1);
    lcd_sendCommand(lcd, 0x30);
    HAL_Delay(8);
    lcd_sendCommand(lcd, 0x20);
    HAL_Delay(8);
    lcd_sendCommand(lcd, LCD_FUNCTIONSET | LCD_FUNCTION_N);
    HAL_Delay(1);
    lcd_sendCommand(lcd, LCD_DISPLAYCONTROL);
    HAL_Delay(1);
    lcd_sendCommand(lcd, LCD_CLEARDISPLAY);
    HAL_Delay(3);
    lcd_sendCommand(lcd, 0x04 | LCD_ENTRY_ID);
    HAL_Delay(1);
    lcd_sendCommand(lcd, LCD_DISPLAYCONTROL | LCD_DISPLAY_D);
    HAL_Delay(3);
}

bool lcd16x2_i2c_auto_init(I2C_LCD_HandleTypeDef *lcd, I2C_HandleTypeDef *pI2cHandle)
{
    HAL_Delay(50);
    lcd->hi2c = pI2cHandle;

    if (HAL_I2C_IsDeviceReady(pI2cHandle, LCD_I2C_ADDR_0, 5, 500) == HAL_OK)
    {
        lcd->address = LCD_I2C_ADDR_0;
    }
    else if (HAL_I2C_IsDeviceReady(pI2cHandle, LCD_I2C_ADDR_1, 5, 500) == HAL_OK)
    {
        lcd->address = LCD_I2C_ADDR_1;
    }
    else if (HAL_I2C_IsDeviceReady(pI2cHandle, LCD_I2C_ADDR_2, 5, 500) == HAL_OK)
    {
        lcd->address = LCD_I2C_ADDR_2;
    }
    else
    {
        return false;
    }

    lcd_init_sequence(lcd);
    return true;
}

bool lcd16x2_i2c_addr_init(I2C_LCD_HandleTypeDef *lcd, I2C_HandleTypeDef *pI2cHandle, int addr)
{
    lcd->hi2c = pI2cHandle;
    lcd->address = (uint8_t)addr;

    if (HAL_I2C_IsDeviceReady(pI2cHandle, lcd->address, 5, 500) != HAL_OK)
    {
        return false;
    }

    lcd_init_sequence(lcd);
    return true;
}

void lcd16x2_i2c_setCursor(I2C_LCD_HandleTypeDef *lcd, uint8_t row, uint8_t col)
{
    uint8_t mask = col & 0x0F;
    if (row == 0)
        mask |= 0x80;
    else
        mask |= 0xC0;
    lcd_sendCommand(lcd, mask);
}

void lcd16x2_i2c_1stLine(I2C_LCD_HandleTypeDef *lcd)
{
    lcd16x2_i2c_setCursor(lcd, 0, 0);
}

void lcd16x2_i2c_2ndLine(I2C_LCD_HandleTypeDef *lcd)
{
    lcd16x2_i2c_setCursor(lcd, 1, 0);
}

void lcd16x2_i2c_TwoLines(I2C_LCD_HandleTypeDef *lcd)
{
    lcd_sendCommand(lcd, LCD_FUNCTIONSET | LCD_FUNCTION_N);
}

void lcd16x2_i2c_OneLine(I2C_LCD_HandleTypeDef *lcd)
{
    lcd_sendCommand(lcd, LCD_FUNCTIONSET);
}

void lcd16x2_i2c_cursorShow(I2C_LCD_HandleTypeDef *lcd, bool state)
{
    if (state)
        lcd_sendCommand(lcd, LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C | LCD_DISPLAY_D);
    else
        lcd_sendCommand(lcd, LCD_DISPLAYCONTROL | LCD_DISPLAY_D);
}

void lcd16x2_i2c_clear(I2C_LCD_HandleTypeDef *lcd)
{
    lcd_sendCommand(lcd, LCD_CLEARDISPLAY);
    HAL_Delay(3);
}

void lcd16x2_i2c_display(I2C_LCD_HandleTypeDef *lcd, bool state)
{
    if (state)
        lcd_sendCommand(lcd, LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C | LCD_DISPLAY_D);
    else
        lcd_sendCommand(lcd, LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C);
}

void lcd16x2_i2c_shiftRight(I2C_LCD_HandleTypeDef *lcd, uint8_t offset)
{
    for (uint8_t i = 0; i < offset; i++)
        lcd_sendCommand(lcd, 0x1C);
}

void lcd16x2_i2c_shiftLeft(I2C_LCD_HandleTypeDef *lcd, uint8_t offset)
{
    for (uint8_t i = 0; i < offset; i++)
        lcd_sendCommand(lcd, 0x18);
}

void lcd16x2_i2c_printf(I2C_LCD_HandleTypeDef *lcd, const char *str, ...)
{
    char buf[20];
    va_list args;
    va_start(args, str);
    vsnprintf(buf, sizeof(buf), str, args);
    va_end(args);
    for (uint8_t i = 0; i < strlen(buf) && i < 16; i++)
        lcd_sendData(lcd, (uint8_t)buf[i]);
}