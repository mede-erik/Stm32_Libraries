/**
 * @author Medeossi Erik
 * @date 19/06/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

 #include "ILI9341_LCD.h"

void LCD_WR_REG(ILI9341_HandleTypeDef *ILI9341,uint8_t data)
{
    HAL_GPIO_WritePin(ILI9341->ILI9341_DC_PORT, ILI9341->ILI9341_DC_PIN, GPIO_PIN_RESET);
    HAL_SPI_Transmit(ILI9341->hspi, &data, 1, HAL_MAX_DELAY);
}

void LCD_WR_DATA(ILI9341_HandleTypeDef *ILI9341,uint8_t data)
{
    
    HAL_GPIO_WritePin(ILI9341->ILI9341_DC_PORT, ILI9341->ILI9341_DC_PIN, GPIO_PIN_SET);
    HAL_SPI_Transmit(ILI9341->hspi, &data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef ILI9341_Init(ILI9341_HandleTypeDef *ILI9341, SPI_HandleTypeDef *hspi, GPIO_TypeDef *ILI9341_DC_PORT, uint16_t ILI9341_DC_PIN, GPIO_TypeDef *ILI9341_CS_PORT, uint16_t ILI9341_CS_PIN, GPIO_TypeDef *ILI9341_RESET_PORT, uint16_t ILI9341_RESET_PIN, uint16_t LCD_width, uint16_t LCD_height)
{
    // Initialize the ILI9341 display with the provided parameters
    ILI9341->hspi = hspi;
    ILI9341->ILI9341_DC_PORT = ILI9341_DC_PORT;
    ILI9341->ILI9341_DC_PIN = ILI9341_DC_PIN;
    ILI9341->ILI9341_CS_PORT = ILI9341_CS_PORT;
    ILI9341->ILI9341_CS_PIN = ILI9341_CS_PIN;
    ILI9341->ILI9341_RESET_PORT = ILI9341_RESET_PORT;
    ILI9341->ILI9341_RESET_PIN = ILI9341_RESET_PIN;
    ILI9341->LCD_width = LCD_width;
    ILI9341->LCD_height = LCD_height;
    
    // Additional initialization code for the display can be added here
    /* Power Control A */
	LCD_WR_REG(ILI9341,0xCB);
	LCD_WR_DATA(ILI9341,0x39);
	LCD_WR_DATA(ILI9341,0x2C);
	LCD_WR_DATA(ILI9341,0x00);
	LCD_WR_DATA(ILI9341,0x34);
	LCD_WR_DATA(ILI9341,0x02);
	/* Power Control B */
	LCD_WR_REG(ILI9341,0xCF);
	LCD_WR_DATA(ILI9341,0x00);
	LCD_WR_DATA(ILI9341,0xC1);
	LCD_WR_DATA(ILI9341,0x30);
	/* Driver timing control A */
	LCD_WR_REG(ILI9341,0xE8);
	LCD_WR_DATA(ILI9341,0x85);
	LCD_WR_DATA(ILI9341,0x00);
	LCD_WR_DATA(ILI9341,0x78);
	/* Driver timing control B */
	LCD_WR_REG(ILI9341,0xEA);
	LCD_WR_DATA(ILI9341,0x00);
	LCD_WR_DATA(ILI9341,0x00);
	/* Power on Sequence control */
	LCD_WR_REG(ILI9341,0xED);
	LCD_WR_DATA(ILI9341,0x64);
	LCD_WR_DATA(ILI9341,0x03);
	LCD_WR_DATA(ILI9341,0x12);
	LCD_WR_DATA(ILI9341,0x81);
	/* Pump ratio control */
	LCD_WR_REG(ILI9341,0xF7);
	LCD_WR_DATA(ILI9341,0x20);
	/* Power Control 1 */
	LCD_WR_REG(ILI9341,0xC0);
	LCD_WR_DATA(ILI9341,0x10);
	/* Power Control 2 */
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(ILI9341,0x10);
	/* VCOM Control 1 */
	LCD_WR_REG(ILI9341,0xC5);
	LCD_WR_DATA(ILI9341,0x3E);
	LCD_WR_DATA(ILI9341,0x28);
	/* VCOM Control 2 */
	LCD_WR_REG(ILI9341,0xC7);
	LCD_WR_DATA(ILI9341,0x86);
	/* VCOM Control 2 */
	LCD_WR_REG(ILI9341,0x36);
	LCD_WR_DATA(ILI9341,0x48);
	/* Pixel Format Set */
	LCD_WR_REG(ILI9341,0x3A);
	LCD_WR_DATA(ILI9341,0x55);    //16bit
	LCD_WR_REG(ILI9341,0xB1);
	LCD_WR_DATA(ILI9341,0x00);
	LCD_WR_DATA(ILI9341,0x18);
	/* Display Function Control */
	LCD_WR_REG(ILI9341,0xB6);
	LCD_WR_DATA(ILI9341,0x08);
	LCD_WR_DATA(ILI9341,0x82);
	LCD_WR_DATA(ILI9341,0x27);
	/* 3GAMMA FUNCTION DISABLE */
	LCD_WR_REG(ILI9341,0xF2);
	LCD_WR_DATA(ILI9341,0x00);
	/* GAMMA CURVE SELECTED */
	LCD_WR_REG(ILI9341,0x26); //Gamma set
	LCD_WR_DATA(ILI9341,0x01); 	//Gamma Curve (G2.2)
	//Positive Gamma  Correction
	LCD_WR_REG(ILI9341,0xE0);
	LCD_WR_DATA(ILI9341,0x0F);
	LCD_WR_DATA(ILI9341,0x31);
	LCD_WR_DATA(ILI9341,0x2B);
	LCD_WR_DATA(ILI9341,0x0C);
	LCD_WR_DATA(ILI9341,0x0E);
	LCD_WR_DATA(ILI9341,0x08);
	LCD_WR_DATA(ILI9341,0x4E);
	LCD_WR_DATA(ILI9341,0xF1);
	LCD_WR_DATA(ILI9341,0x37);
	LCD_WR_DATA(ILI9341,0x07);
	LCD_WR_DATA(ILI9341,0x10);
	LCD_WR_DATA(ILI9341,0x03);
	LCD_WR_DATA(ILI9341,0x0E);
	LCD_WR_DATA(ILI9341,0x09);
	LCD_WR_DATA(ILI9341,0x00);
	//Negative Gamma  Correction
	LCD_WR_REG(ILI9341,0xE1);
	LCD_WR_DATA(ILI9341,0x00);
	LCD_WR_DATA(ILI9341,0x0E);
	LCD_WR_DATA(ILI9341,0x14);
	LCD_WR_DATA(ILI9341,0x03);
	LCD_WR_DATA(ILI9341,0x11);
	LCD_WR_DATA(ILI9341,0x07);
	LCD_WR_DATA(ILI9341,0x31);
	LCD_WR_DATA(ILI9341,0xC1);
	LCD_WR_DATA(ILI9341,0x48);
	LCD_WR_DATA(ILI9341,0x08);
	LCD_WR_DATA(ILI9341,0x0F);
	LCD_WR_DATA(ILI9341,0x0C);
	LCD_WR_DATA(ILI9341,0x31);
	LCD_WR_DATA(ILI9341,0x36);
	LCD_WR_DATA(ILI9341,0x0F);
	//EXIT SLEEP
	LCD_WR_REG(ILI9341,0x11);

	HAL_Delay(120);

	//TURN ON DISPLAY
	LCD_WR_REG(ILI9341,0x29);
	LCD_WR_DATA(ILI9341,0x2C);

	ILI9341_direction(ILI9341,ROTATE_270);

}


void ILI9341_Reset(ILI9341_HandleTypeDef *ILI9341)
{

	HAL_GPIO_WritePin(ILI9341->ILI9341_RESET_PORT, ILI9341->ILI9341_RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(ILI9341->ILI9341_RESET_PORT, ILI9341->ILI9341_RESET_PIN, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(ILI9341->ILI9341_CS_PORT, ILI9341->ILI9341_CS_PIN, GPIO_PIN_RESET);
	//LED_H();
}

void ILI9341_SoftReset(ILI9341_HandleTypeDef *ILI9341)
{
	uint8_t cmd;
	cmd = 0x01; //Software reset
	HAL_GPIO_WritePin(ILI9341->ILI9341_DC_PORT, ILI9341->ILI9341_DC_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(ILI9341->hspi, &cmd, 1, HAL_MAX_DELAY);
}


void ILI9341_direction(ILI9341_HandleTypeDef *ILI9341, uint8_t direction)
{
    switch (direction) {
	case ROTATE_0:
		LCD_WR_REG(ILI9341,0x36);
		LCD_WR_DATA(ILI9341,0x48);
		break;
	case ROTATE_90:
		LCD_WR_REG(ILI9341,0x36);
		LCD_WR_DATA(ILI9341,0x28);
		break;
	case ROTATE_180:
		LCD_WR_REG(ILI9341,0x36);
		LCD_WR_DATAILI9341,(0x88);
		break;
	case ROTATE_270:
		LCD_WR_REG(ILI9341,0x36);
		LCD_WR_DATA(ILI9341,0xE8);
		break;
	}
}

void ILI9341_SetWindow(ILI9341_HandleTypeDef *ILI9341,uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
	// Set Window
	LCD_WR_REG(ILI9341,0x2a);
	LCD_WR_DATA(ILI9341,start_x >> 8);
	LCD_WR_DATA(ILI9341,0xFF & start_x);
	LCD_WR_DATA(ILI9341,end_x >> 8);
	LCD_WR_DATA(ILI9341,0xFF & end_x);

	LCD_WR_REG(ILI9341,0x2b);
	LCD_WR_DATA(ILI9341,start_y >> 8);
	LCD_WR_DATA(ILI9341,0xFF & start_y);
	LCD_WR_DATA(ILI9341,end_y >> 8);
	LCD_WR_DATA(ILI9341,0xFF & end_y);

}

void ILI9341_WritePixel(ILI9341_HandleTypeDef *ILI9341,uint16_t x, uint16_t y, uint16_t color)
{
	uint8_t data[2];
	data[0] = color >> 8;
	data[1] = color;
	ILI9341_SetWindow(ILI9341,x, y, x, y);
	// Enable to access GRAM
	LCD_WR_REG(ILI9341,0x2c);
    HAL_GPIO_WritePin(ILI9341->ILI9341_DC_PORT, ILI9341->ILI9341_DC_PIN, GPIO_PIN_SET);
    HAL_SPI_Transmit(ILI9341->hspi, data, 2, HAL_MAX_DELAY);
}

void ILI9341_DrawBitmap(ILI9341_HandleTypeDef *ILI9341,uint16_t w, uint16_t h, uint8_t *s)
{
	// Enable to access GRAM
	LCD_WR_REG(ILI9341,0x2c);
	HAL_GPIO_WritePin(ILI9341->ILI9341_DC_PORT, ILI9341->ILI9341_DC_PIN, GPIO_PIN_SET);
	ConvHL(s, (int32_t)w*h*2);
    HAL_SPI_Transmit(ILI9341->hspi,(uint8_t*) s, w * h * 2, HAL_MAX_DELAY);
}


static void ConvHL(uint8_t *s, int32_t l)
{
	uint8_t v;
	while (l > 0) {
		v = *(s+1);
		*(s+1) = *s;
		*s = v;
		s += 2;
		l -= 2;
	}
}



void ILI9341_DrawRectangle(ILI9341_HandleTypeDef *ILI9341,uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
	uint16_t i, j;
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			ILI9341_WritePixel(ILI9341,x + i, y + j, color);
		}
	}
}

void ILI9341_FillScreen(ILI9341_HandleTypeDef *ILI9341,uint16_t color)
{
	uint16_t i, j;
	ILI9341_SetWindow(ILI9341,0, 0, ILI9341->LCD_width - 1, ILI9341->LCD_height - 1);
	// Enable to access GRAM
	LCD_WR_REG(ILI9341,0x2c);
	HAL_GPIO_WritePin(ILI9341->ILI9341_DC_PORT, ILI9341->ILI9341_DC_PIN, GPIO_PIN_SET);
	for (i = 0; i < ILI9341->LCD_width; i++) {
		for (j = 0; j < ILI9341->LCD_height; j++) {
			LCD_WR_DATA(ILI9341,color >> 8);
			LCD_WR_DATA(ILI9341,0xFF & color);
		}
	}
}		

void ILI9341_DrawLine(ILI9341_HandleTypeDef *ILI9341,uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx = abs(x1 - x0);
	int16_t dy = abs(y1 - y0);
	int16_t sx = (x0 < x1) ? 1 : -1;
	int16_t sy = (y0 < y1) ? 1 : -1;
	int16_t err = dx - dy;

	while (1) {
		ILI9341_WritePixel(ILI9341,x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		int16_t e2 = err << 1;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}	

void ILI9341_DrawCircle(ILI9341_HandleTypeDef *ILI9341,uint16_t x0, uint16_t y0, uint16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	ILI9341_WritePixel(ILI9341,x0, y0 + r, color);
	ILI9341_WritePixel(ILI9341,x0, y0 - r, color);
	ILI9341_WritePixel(ILI9341,x0 + r, y0, color);
	ILI9341_WritePixel(ILI9341,x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		ILI9341_WritePixel(ILI9341,x0 + x, y0 + y, color);						
		ILI9341_WritePixel(ILI9341,x0 - x, y0 + y, color);
		ILI9341_WritePixel(ILI9341,x0 + x, y0 - y, color);
		ILI9341_WritePixel(ILI9341,x0 - x, y0 - y, color);
		ILI9341_WritePixel(ILI9341,x0 + y, y0 + x, color);
		ILI9341_WritePixel(ILI9341,x0 - y, y0 + x, color);
		ILI9341_WritePixel(ILI9341,x0 + y, y0 - x, color);
		ILI9341_WritePixel(ILI9341,x0 - y, y0 - x, color);
	}
}

void ILI9341_DrawArc(ILI9341_HandleTypeDef *ILI9341,uint16_t x0, uint16_t y0, uint16_t r, uint16_t start_angle, uint16_t end_angle, uint16_t color)
{
	int16_t x = r * cos(start_angle * M_PI / 180.0);
	int16_t y = r * sin(start_angle * M_PI / 180.0);
	ILI9341_WritePixel(ILI9341, x0 + x, y0 + y, color);
	for (int16_t angle = start_angle + 1; angle <= end_angle; angle++) {
		x = r * cos(angle * M_PI / 180.0);
		y = r * sin(angle * M_PI / 180.0);
		ILI9341_WritePixel(ILI9341, x0 + x, y0 + y, color);
	}
}

void ILI9341_DrawTriangle(ILI9341_HandleTypeDef *ILI9341,uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	ILI9341_DrawLine(ILI9341,x0, y0, x1, y1, color);
	ILI9341_DrawLine(ILI9341,x1, y1, x2, y2, color);
	ILI9341_DrawLine(ILI9341,x2, y2, x0, y0, color);
}

void ILI9341_DrawPolygon(ILI9341_HandleTypeDef *ILI9341,uint16_t *x, uint16_t *y, uint16_t num_points, uint16_t color)
{
	for (uint16_t i = 0; i < num_points; i++) {
		uint16_t next_index = (i + 1) % num_points;
		ILI9341_DrawLine(ILI9341,x[i], y[i], x[next_index], y[next_index], color);
	}
}

