#include "ili9341.h"

void LCD_Write_Command(uint8_t cmd)
{
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
  HAL_SPI_Transmit(LCD_SPI_HANDLE, &cmd, 1, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void LCD_Write_Data(uint8_t data)
{
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  HAL_SPI_Transmit(LCD_SPI_HANDLE, &data, 1, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void LCD_Write_Data16(uint16_t data)
{
  uint8_t data_h = (data >> 8);
  uint8_t data_l = data & 0xFF;

  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  HAL_SPI_Transmit(LCD_SPI_HANDLE, &data_h, 1, HAL_MAX_DELAY);
  HAL_SPI_Transmit(LCD_SPI_HANDLE, &data_l, 1, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void LCD_Reset(void)
{
  HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
  HAL_Delay(100);
}

void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
  /* Cài đặt vùng cột */
  LCD_Write_Command(0x2A);  // Column Address Set
  LCD_Write_Data16(x0);
  LCD_Write_Data16(x1);

  /* Cài đặt vùng hàng */
  LCD_Write_Command(0x2B);  // Row Address Set
  LCD_Write_Data16(y0);
  LCD_Write_Data16(y1);

  /* Bắt đầu ghi dữ liệu */
  LCD_Write_Command(0x2C);  // Memory Write
}

void LCD_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
  uint32_t total_pixels = (x1 - x0 + 1) * (y1 - y0 + 1);

  LCD_SetWindow(x0, y0, x1, y1);

  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);

  for (uint32_t i = 0; i < total_pixels; i++) {
    LCD_Write_Data16(color);
  }

  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void LCD_Clear(uint16_t color)
{
  LCD_Fill(0, 0, ILI9341_WIDTH - 1, ILI9341_HEIGHT - 1, color);
}

void LCD_Init(void)
{
  /* Khởi tạo phần cứng */
  LCD_Reset();

  /* Chuỗi lệnh khởi tạo LCD */
  LCD_Write_Command(0x01);  // Software Reset
  HAL_Delay(100);

  LCD_Write_Command(0xCF);  // Power Control B
  LCD_Write_Data(0x00);
  LCD_Write_Data(0xC1);
  LCD_Write_Data(0x30);

  LCD_Write_Command(0xED);  // Power on sequence control
  LCD_Write_Data(0x64);
  LCD_Write_Data(0x03);
  LCD_Write_Data(0x12);
  LCD_Write_Data(0x81);

  LCD_Write_Command(0xE8);  // Driver timing control A
  LCD_Write_Data(0x85);
  LCD_Write_Data(0x00);
  LCD_Write_Data(0x78);

  LCD_Write_Command(0xCB);  // Power Control A
  LCD_Write_Data(0x39);
  LCD_Write_Data(0x2C);
  LCD_Write_Data(0x00);
  LCD_Write_Data(0x34);
  LCD_Write_Data(0x02);

  LCD_Write_Command(0xF7);  // Pump ratio control
  LCD_Write_Data(0x20);

  LCD_Write_Command(0xEA);  // Driver timing control B
  LCD_Write_Data(0x00);
  LCD_Write_Data(0x00);

  LCD_Write_Command(0xC0);  // Power Control 1
  LCD_Write_Data(0x23);

  LCD_Write_Command(0xC1);  // Power Control 2
  LCD_Write_Data(0x10);

  LCD_Write_Command(0xC5);  // VCOM Control 1
  LCD_Write_Data(0x3E);
  LCD_Write_Data(0x28);

  LCD_Write_Command(0xC7);  // VCOM Control 2
  LCD_Write_Data(0x86);

  LCD_Write_Command(0x36);  // Memory Access Control
  LCD_Write_Data(0x48);     // config rotation (0x48 or 0x050)

  LCD_Write_Command(0x3A);  // Pixel Format Set
  LCD_Write_Data(0x55);     // 16-bit color

  LCD_Write_Command(0xB1);  // Frame Rate Control
  LCD_Write_Data(0x00);
  LCD_Write_Data(0x18);

  LCD_Write_Command(0xB6);  // Display Function Control
  LCD_Write_Data(0x08);
  LCD_Write_Data(0x82);
  LCD_Write_Data(0x27);

  LCD_Write_Command(0xF2);  // 3Gamma Function Disable
  LCD_Write_Data(0x00);

  LCD_Write_Command(0x26);  // Gamma curve selected
  LCD_Write_Data(0x01);

  LCD_Write_Command(0xE0);  // Set Gamma
  LCD_Write_Data(0x0F);
  LCD_Write_Data(0x31);
  LCD_Write_Data(0x2B);
  LCD_Write_Data(0x0C);
  LCD_Write_Data(0x0E);
  LCD_Write_Data(0x08);
  LCD_Write_Data(0x4E);
  LCD_Write_Data(0xF1);
  LCD_Write_Data(0x37);
  LCD_Write_Data(0x07);
  LCD_Write_Data(0x10);
  LCD_Write_Data(0x03);
  LCD_Write_Data(0x0E);
  LCD_Write_Data(0x09);
  LCD_Write_Data(0x00);

  LCD_Write_Command(0xE1);  // Set Gamma
  LCD_Write_Data(0x00);
  LCD_Write_Data(0x0E);
  LCD_Write_Data(0x14);
  LCD_Write_Data(0x03);
  LCD_Write_Data(0x11);
  LCD_Write_Data(0x07);
  LCD_Write_Data(0x31);
  LCD_Write_Data(0xC1);
  LCD_Write_Data(0x48);
  LCD_Write_Data(0x08);
  LCD_Write_Data(0x0F);
  LCD_Write_Data(0x0C);
  LCD_Write_Data(0x31);
  LCD_Write_Data(0x36);
  LCD_Write_Data(0x0F);

  LCD_Write_Command(0x11);  // Exit Sleep
  HAL_Delay(120);

  LCD_Write_Command(0x29);  // Display On
  HAL_Delay(20);
}
uint16_t RGBToBGR(uint16_t color)
{
  uint16_t r = (color >> 11) & 0x1F; // 5 red bit
  uint16_t g = (color >> 5) & 0x3F;  // 6 green bit 
  uint16_t b = color & 0x1F;         // 5 blue bit
  return (b << 11) | (g << 5) | r;   // convert to BGR
}
void Draw_Big_N(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, uint16_t color)
{
  uint16_t thickness = width / 5;  

  LCD_Fill(x0, y0, x0 + thickness - 1, y0 + height - 1, color);

  LCD_Fill(x0 + width - thickness, y0, x0 + width - 1, y0 + height - 1, color);

  for (uint16_t i = 0; i < height; i++) {
    uint16_t diagonal_width = (i * (width - thickness)) / height;
    LCD_Fill(x0 + diagonal_width, y0 + i, x0 + diagonal_width + thickness - 1, y0 + i, color);
  }
}

void LCD_DrawChar(uint16_t x, uint16_t y, char ch, uint16_t textColor, uint16_t bgColor)
{
  if (ch < 32 || ch > 127) {
    ch = '?'; // repalce undefine char to '?' 
  }

  // everey char is 5 bytes in font
  uint8_t const *char_ptr = &Font5x7[(ch - 32) * 5];


  for (uint8_t col = 0; col < 5; col++) {
    uint8_t col_data = char_ptr[col];

    // display pixel
    for (uint8_t row = 0; row < 8; row++) {
      if (col_data & (1 << row)) {
        // if pixel is on , draw pixel with color of char
        LCD_SetWindow(x + col, y + row, x + col, y + row);
        LCD_Write_Data16(textColor);
      } else {
        // if pixel is off , draw pixel with color of background
        LCD_SetWindow(x + col, y + row, x + col, y + row);
        LCD_Write_Data16(bgColor);
      }
    }
  }
}
void LCD_DisplayString(uint16_t x, uint16_t y, const char *str, uint16_t textColor, uint16_t bgColor)
{
  uint16_t current_x = x;
  while (*str) {
    LCD_DrawChar(current_x, y, *str, textColor, bgColor);
    current_x += 6;
    str++;
    if (current_x + 5 >= ILI9341_WIDTH) {
      break;
    }
  }
}
void Fill_Screen(uint16_t color)
{
  LCD_SetWindow(0, 0, ILI9341_WIDTH - 1, ILI9341_HEIGHT - 1);

  uint32_t total_pixels = ILI9341_WIDTH * ILI9341_HEIGHT;

  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);

  for (uint32_t i = 0; i < total_pixels; i++) {
    uint8_t high_byte = color >> 8;
    uint8_t low_byte = color & 0xFF;

    HAL_SPI_Transmit(LCD_SPI_HANDLE, &high_byte, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(LCD_SPI_HANDLE, &low_byte, 1, HAL_MAX_DELAY);
  }

  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void LCD_DrawImage(uint16_t x, uint16_t y, const Image *img)
{
  LCD_SetWindow(x, y, x + img->width - 1, y + img->height - 1);
  
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
  
  uint32_t total_pixels = img->width * img->height;
  
  for (uint32_t i = 0; i < total_pixels; i++) {
    uint16_t color = img->data[i];
    
    color = RGB_TO_BGR(color);
    
    uint8_t high_byte = color >> 8;
    uint8_t low_byte = color & 0xFF;
    
    HAL_SPI_Transmit(LCD_SPI_HANDLE, &high_byte, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit(LCD_SPI_HANDLE, &low_byte, 1, HAL_MAX_DELAY);
  }
  
  HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}
