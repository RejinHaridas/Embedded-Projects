#include <SPI.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0,5, 17,16);   // setting parameters as no rotation , Chip select [in , Data/Command , RESET
  
void setup() {
  // put your setup code here, to run once:

  SPI.begin(18 ,-1, 23);
  u8g2.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 30, "SPI OLED Test!");
  u8g2.sendBuffer();
  delay(1000);
}
