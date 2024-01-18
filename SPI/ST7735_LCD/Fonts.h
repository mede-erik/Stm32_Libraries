/**
 * @author Medeossi Erik
 * @date 18/01/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @note This in inspired from controllerstech lib
 * @link https://github.com/controllerstech
 */
#ifndef __FONTS_H__
#define __FONTS_H__

#include <stdint.h>

typedef struct
{
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;

extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

#endif // __FONTS_H__
