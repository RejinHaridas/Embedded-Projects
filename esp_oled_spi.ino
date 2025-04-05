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

// the register level version
/*
#define PIN_CS    5
#define PIN_DC    17
#define PIN_RST   16

#include "driver/spi_master.h"

// SPI handle
spi_device_handle_t spi;

// Send a command byte
void oled_cmd(uint8_t cmd) {
  gpio_set_level(PIN_DC, 0); // Command mode
  spi_transaction_t t = {};
  t.length = 8;
  t.tx_buffer = &cmd;
  spi_device_transmit(spi, &t);
}

// Send a data byte
void oled_data(uint8_t data) {
  gpio_set_level(PIN_DC, 1); // Data mode
  spi_transaction_t t = {};
  t.length = 8;
  t.tx_buffer = &data;
  spi_device_transmit(spi, &t);
}

// OLED Initialization sequence
void oled_init() {
  gpio_set_level(PIN_RST, 0);
  delay(10);
  gpio_set_level(PIN_RST, 1);


// these are the default settings for the initialization of the OLED

  oled_cmd(0xAE); // Display off
  oled_cmd(0xD5); oled_cmd(0x80); // Set display clock
  oled_cmd(0xA8); oled_cmd(0x3F); // Set multiplex
  oled_cmd(0xD3); oled_cmd(0x00); // Display offset
  oled_cmd(0x40); // Start line
  oled_cmd(0x8D); oled_cmd(0x14); // Charge pump
  oled_cmd(0x20); oled_cmd(0x00); // Memory mode
  oled_cmd(0xA1); // Segment remap
  oled_cmd(0xC8); // COM scan direction
  oled_cmd(0xDA); oled_cmd(0x12); // COM pins
  oled_cmd(0x81); oled_cmd(0xCF); // Contrast
  oled_cmd(0xD9); oled_cmd(0xF1); // Precharge
  oled_cmd(0xDB); oled_cmd(0x40); // VCOM
  oled_cmd(0xA4); // Resume display
  oled_cmd(0xA6); // Normal display
  oled_cmd(0xAF); // Display ON
}



void app_main() {
  // Setup GPIO
  gpio_set_direction(PIN_CS, GPIO_MODE_OUTPUT);
  gpio_set_direction(PIN_DC, GPIO_MODE_OUTPUT);
  gpio_set_direction(PIN_RST, GPIO_MODE_OUTPUT);
  
  // SPI Bus Configuration
  spi_bus_config_t buscfg = {
    .mosi_io_num = 23,
    .miso_io_num = -1,
    .sclk_io_num = 18,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 0
  };
  
  spi_device_interface_config_t devcfg = {
    .clock_speed_hz = 10 * 1000 * 1000,
    .mode = 0,
    .spics_io_num = PIN_CS,
    .queue_size = 1,
  };

  spi_bus_initialize(HSPI_HOST, &buscfg, 1);
  spi_bus_add_device(HSPI_HOST, &devcfg, &spi);

  oled_init();

  // Fill screen with some pattern (basic)
  for (int page = 0; page < 8; page++) {
    oled_cmd(0xB0 + page); // Set page
    oled_cmd(0x00);        // Lower col
    oled_cmd(0x10);        // Upper col
    for (int col = 0; col < 128; col++) {
      oled_data(0xFF);     // Solid pixels
    }
  }
}
*/
