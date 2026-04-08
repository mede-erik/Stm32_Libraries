# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a collection of STM32 HAL libraries written in C. Each library is self-contained in its own directory with header (.h) and implementation (.c) files. These libraries are designed to be copied into STM32CubeIDE projects.

## Repository Structure

```
├── crc/                    # CRC16 calculation (lookup table based)
├── I2C/
│   ├── INA228/             # INA228 current/power sensor driver
│   └── I2C_PCF8574/
│       └── I2C_LCD/        # PCF8574-based I2C LCD driver
├── log/                    # UART logging utility with severity levels
├── pid/                    # PID controller implementation
├── sensors/
│   └── ntc.h               # NTC thermistor constants (header only)
├── SPI/
│   └── ST7735_LCD/         # ST7735 SPI LCD driver with fonts
└── utility/                # General utility functions (map, swap)
```

## Architecture Patterns

### HAL Include Convention
All library headers include only `main.h` (not conditional STM32 HAL headers directly). The user's project `main.h` must include the appropriate STM32 HAL header for their target.

**Do NOT add conditional HAL includes like this:**
```c
// DON'T DO THIS
#if defined(STM32F4)
  #include "stm32f4xx_hal.h"
#elif defined(STM32F1)
  #include "stm32f1xx_hal.h"
#endif
```

**Instead, only include:**
```c
#include "main.h"
```

### Library Naming Conventions
- Files and directories use snake_case (e.g., `i2c_lcd.h`)
- Public functions use PascalCase with module prefix (e.g., `INA228_ReadCurrent`, `PID_init`)
- Struct types end with `_t` or `_HandleTypeDef` (STM32 HAL style)

### Documentation Style
Use Doxygen comments at the top of each file:
```c
/**
 * @author Medeossi Erik
 * @date DD/MM/YYYY
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version XvY
 * @details Additional details if needed
 */
```

Function documentation example:
```c
/**
 * @brief Brief description
 * @param param1 Description
 * @return Description
 */
```

### Hardware Handle Pattern
Peripheral drivers follow STM32 HAL style with a handle struct containing:
- Pointer to HAL handle (e.g., `I2C_HandleTypeDef *hi2c`)
- Configuration parameters (address, settings)
- Instance-specific state

Example:
```c
typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint16_t addr;
    // ... config fields
} INA228_HandleTypeDef;
```

## Development Workflow

This repository has no build system - code is validated by:
1. Reviewing for STM32 HAL compatibility
2. Checking against STM32CubeIDE compiler warnings
3. Testing on actual hardware

### Before Committing
- Ensure all public functions are declared in the header
- Verify `main.h` is the only HAL-related include
- Add/update Doxygen documentation for new functions
- Include `@version` in header when adding significant features

## License

All code is GPL v3 licensed. Preserve the license header when creating new files:
```c
/**
 * @author Medeossi Erik
 * @date DD/MM/YYYY
 * @link https://github.com/mede-erik/Stm32_Libraries
 */
```
