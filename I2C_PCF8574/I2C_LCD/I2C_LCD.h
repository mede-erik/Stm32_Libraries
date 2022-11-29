/**
 * @author Medeossi Erik
 * @date 28/11/2022
 * @details
 */
// TODO add details

static void lcd16x2_i2c_sendCommand(uint8_t command);
static void lcd16x2_i2c_sendData(uint8_t data);
bool lcd16x2_i2c_auto_init(I2C_HandleTypeDef *pI2cHandle);
bool lcd16x2_i2c_auto_init(I2C_HandleTypeDef *pI2cHandle, int addr);
void lcd16x2_i2c_setCursor(uint8_t row, uint8_t col);
void lcd16x2_i2c_1stLine(void);
void lcd16x2_i2c_2ndLine(void);
void lcd16x2_i2c_TwoLines(void);
void lcd16x2_i2c_OneLine(void);
void lcd16x2_i2c_cursorShow(bool state);
void lcd16x2_i2c_clear(void);
void lcd16x2_i2c_display(bool state);
void lcd16x2_i2c_shiftRight(uint8_t offset);
void lcd16x2_i2c_shiftLeft(uint8_t offset);
void lcd16x2_i2c_printf(const char *str, ...);
