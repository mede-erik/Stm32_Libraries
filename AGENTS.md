# Stm32_Libraries — Agent Guide

## What this is

Standalone STM32 HAL peripheral/component C libraries. Drop `.c`/`.h` into an STM32CubeMX/CubeIDE project. No build system, no tests, no CI.

## Branches & unmerged libraries

Each feature branch adds a new component and is **not merged to main**:

| Branch | New component | Location | HAL include | Have guard |
|--------|--------------|----------|-------------|------------|
| `BME680_dev` | Bosch BME680 environmental sensor | `I2C/BME680/` | conditional `#ifdef` | no |
| `GC9A01_dev` | GC9A01 round LCD (SPI) | `SPI/GC9A01_LCD/` | `main.h` only | yes |
| `ILI9341_dev` | ILI9341 TFT LCD (SPI) | `SPI/ILI9341_LCD/` | `main.h` only | no |
| `MAX6675_dev` | MAX6675 thermocouple (SPI) | `SPI/MAX6675/` | `main.h` only | yes |
| `MCP9600_DEV` | MCP9600 thermocouple (I2C) | `I2C/MCP9600/` | `main.h` only | yes |
| `OBD-II_dev` | OBD-II over CAN | `CAN/ODB-II/` | conditional `#ifdef` | no |
| `st7735_dev` | ST7735 with separate fonts | `SPI/ST7735_LCD/` + `Fonts.c`/`.h` | conditional `#ifdef` | yes |

Legacy libs on main (INA228, the ST7735 on main) still use conditional `#ifdef STM32Fx` blocks. Newer libs (GC9A01, MAX6675, MCP9600) use `#include "main.h"` only — the recommended pattern. **Do not add conditional HAL blocks to new code.**

The `GC9A01_dev` branch has a `CLAUDE.md` documenting conventions (aspirational — not all branches follow it yet).

## Structure (main + branches)

```
crc/                          CRC16 software (table-driven, no HW peripheral)
CAN/ODB-II/         [branch]  OBD-II over CAN
I2C/
  BME680/            [branch] BME680 environmental sensor
  I2C_PCF8574/I2C_LCD/        HD44780 16x2 via PCF8574 I2C backpack
  INA228/                      INA228 power monitor (I2C, 20-bit ΔΣ)
  MCP9600/           [branch] MCP9600 thermocouple (I2C)
SPI/
  GC9A01_LCD/        [branch] GC9A01 round LCD (SPI, circular)
  ILI9341_LCD/       [branch] ILI9341 TFT LCD (SPI)
  MAX6675/           [branch] MAX6675 thermocouple (SPI)
  ST7735_LCD/                  ST7735 TFT LCD (main) + Fonts.c/.h (st7735_dev)
pid/                          PID controller (float, anti-windup clamp ±16777216)
log/                          UART logging, 5 levels, via HAL_UART_Transmit()
sensors/ntc                   NTC thermistor — **stub** (header only, .c empty)
utility/                      map(), swap(), kelvin conversion, uint16 bit-split helpers
```

## Key facts

- **No build system** — add `.c`/`.h` to a CubeMX/CubeIDE project manually.
- **Dependency**: all libraries need `"main.h"` (CubeMX-generated). Some headers add conditional `#ifdef STM32Fx` for direct HAL access — match the convention of the file being edited.
- **Log** uses `HAL_UART_Transmit()` — needs `UART_HandleTypeDef`.
- **PID** clamps integral term to ±16777216.
- **LCD** derived from [MYaqoobEmbedded/STM32-Tutorials](https://github.com/MYaqoobEmbedded/STM32-Tutorials); ST7735 `` st7735_dev also inspired by [controllerstech](https://github.com/controllerstech).
- **Naming** inconsistent: `INA228_HandleTypeDef`, `LOG_HandleTypeDef`, `PID_t`, `GC9A01_HandleTypeDef`.
- **Formatting**: mixed tabs/spaces across files. Follow the existing style.

## Common gotchas

- `utility.c` bug: `uint16_to_uint8_down_bits()` right-shifts by 8 instead of masking `& 0xFF` (identical to `up_bits`).
- `sensors/ntc.c` is empty — header-only stub.
- Several headers lack `#ifndef` guards (pid.h, log.h, utility.h, ntc.h, BME680.h, ILI9341_LCD.h, ODB-II.h, ST7735_LCD.h on main) — watch for double-inclusion.
- Commit messages in Italian; code comments in English with Doxygen `@brief`/`@param`/`@return`.
- No SDK/series target in most files — the user's `main.h` determines the STM32 family at compile time.
- New code should prefer `#include "main.h"` over conditional HAL includes.
