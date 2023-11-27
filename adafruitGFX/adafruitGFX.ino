#include <Wire.h>
#include <SPI.h>

#include <Arduino_GFX_Library.h>
#define TFT_BL 2
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
  14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
  9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
  15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
  bus,
  800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 1 /* hsync_pulse_width */, 46 /* hsync_back_porch */,
  480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 1 /* vsync_pulse_width */, 23 /* vsync_back_porch */,
  0 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);

#include "touch.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("LVGL Widgets Demo");

  //IO Port Pins
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW);

  // Init Display
  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  delay(200);
  
#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif

  lcd->fillScreen(RED);
  delay(800);
  lcd->fillScreen(BLUE);
  delay(800);
  lcd->fillScreen(YELLOW);
  delay(800);
  lcd->fillScreen(GREEN);
  delay(800);

  Serial.println( "Setup done" );
}

uint8_t counter = 0;
void loop()
{
  if (counter == 0) {
    lcd->fillScreen(RED);
  }
  if (counter == 1) {
    lcd->fillScreen(BLUE);
  }
  if (counter == 2) {
    lcd->fillScreen(YELLOW);
  }
  if (counter == 3) {
    lcd->fillScreen(GREEN);
  }
  counter++;
  if (counter > 3) counter = 0;
  Serial.println("Loopy");
  delay(1000);
}
