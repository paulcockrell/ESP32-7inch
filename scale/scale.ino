#include <ESP32Time.h>
#include <Wire.h>
#include "display.h"
#include "bigFont.h"
#include "middleFont.h"
#include "smallFont.h"
#include "valueFont.h"

LGFX lcd;
LGFX_Sprite sprite(&lcd);

double rad = 0.01745;

float x[360];  //outer point
float y[360];
float px[360];  //inner point
float py[360];
float lx[360];  //long line
float ly[360];
float shx[360];  //short line
float shy[360];
float tx[360];  //text
float ty[360];

int PPgraph[24] = { 0 };

int angle = 0;
int value = 0;
int chosenFont;
int chosenColor;
int r = 118;
int sx = -2;
int sy = 120;
int inc = 18;
int a = 0;
int prev = 0;
String secs = "00";
int second1 = 0;
int second2 = 0;
bool onOff = 0;
String OO[2] = { "OFF", "ON" };
int deb = 0;

#define I2C_SDA_PIN 17
#define I2C_SCL_PIN 18
#define TOUCH_RST -1  // 38
#define TOUCH_IRQ -1  // 0

ESP32Time rtc(0);

#define PWM_CHANNEL 1
#define PWM_FREQ 5000  //Hz
#define pwm_resolution_bits 10
#define IO_PWM_PIN 38

int n = 0;
int xt = 0, yt = 0;

unsigned short grays[13];
#define red 0xD041
#define blue 0x0AD0
#define yellow 0x9381
#define bck TFT_BLACK
char dd[7] = { 'm', 't', 'w', 't', 'f', 's', 's' };
int brightness[5] = { 40, 80, 100, 120, 140 };
int b = 1;

void setup() {
  rtc.setTime(0, 47, 13, 10, 23, 2023, 0);

  lcd.init();
  lcd.setRotation(0);
  lcd.setBrightness(brightness[b]);
  lcd.setSwapBytes(1);
  lcd.fillScreen(TFT_BLACK);
  sprite.createSprite(400, 340);

  int co = 220;
  for (int i = 0; i < 13; i++) {
    grays[i] = lcd.color565(co, co, co);
    co = co - 20;
  }

  for (int i = 0; i < 360; i++) {
    x[i] = (r * cos(rad * i)) + sx;
    y[i] = (r * sin(rad * i)) + sy;
    px[i] = ((r - 5) * cos(rad * i)) + sx;
    py[i] = ((r - 5) * sin(rad * i)) + sy;

    lx[i] = ((r - 24) * cos(rad * i)) + sx;
    ly[i] = ((r - 24) * sin(rad * i)) + sy;

    shx[i] = ((r - 12) * cos(rad * i)) + sx;
    shy[i] = ((r - 12) * sin(rad * i)) + sy;

    tx[i] = ((r + 28) * cos(rad * i)) + sx;
    ty[i] = ((r + 28) * sin(rad * i)) + sy;
  }

  draw();
}

void draw() {
  sprite.fillSprite(grays[11]);

  // Percent marker
  sprite.fillRoundRect(
    54,
    119,
    26,
    4,
    2,
    TFT_RED);

  // Bar chart
  for (int j = 0; j < 24; j++)
    for (int i = 0; i < PPgraph[j]; i++)
      sprite.fillRect(188 + (j * 6), 90 - (i * 4), 4, 3, grays[5]);

  // Value border
  sprite.fillRect(180, 136, 100, 3, grays[7]);
  sprite.fillRect(186, 130, 3, 34, grays[7]);

  // Percentage sign
  sprite.setTextDatum(4);
  sprite.loadFont(smallFont);
  sprite.setTextColor(grays[7], TFT_BLACK);
  sprite.drawString("%", 60, 106);
  sprite.unloadFont();

  // Gauge dial

  sprite.loadFont(middleFont);

  for (int i = 0; i < 120; i++) {
    a = angle + (i * 3);

    if (a > 359)
      a = (angle + (i * 3)) - 360;

    // -- dot increments
    sprite.drawPixel(x[a], y[a], grays[6]);
    sprite.setTextColor(grays[2], TFT_BLACK);

    // -- small increment line
    if (i % 3 == 0)
      sprite.fillRoundRect(
        x[a] - 5,
        y[a],
        6,
        2,
        1,
        grays[5]);

    // -- medium increment line
    if (i % 6 == 0)
      sprite.fillRoundRect(
        x[a] - 17,
        y[a] - 1,
        18,
        4,
        2,
        grays[4]);

    // -- long increment line
    if (i % 12 == 0) {
      sprite.fillRoundRect(
        x[a] - 29,
        y[a] - 1,
        30,
        4,
        2,
        grays[1]);

      // -- Draw rotary dial value
      sprite.drawString(String((i / 6) * 5), tx[a], ty[a], 2);
    }
  }

  // Days of week
  sprite.setTextDatum(4);
  sprite.setTextColor(grays[2], grays[8]);

  // -- background squares containing day of week
  for (int i = 0; i < 7; i++) {
    sprite.fillRoundRect(
      186 + (i * 30),
      1,
      26,
      34,
      3,
      grays[8]);

    sprite.drawString(String(dd[i]), 186 + ((i + 1) * 30) - 25, 18);
  }

  // Day of week arrow

  sprite.unloadFont();
  sprite.fillTriangle(
    199 + (rtc.getDayofWeek() * 30),
    35,
    199 + (rtc.getDayofWeek() * 30) + 5,
    40,
    (199 + (rtc.getDayofWeek() * 30)) - 5,
    40,
    grays[3]);

  // Time

  sprite.setTextDatum(0);
  sprite.setTextColor(grays[0], bck);
  sprite.loadFont(bigFont);
  sprite.drawString(rtc.getTime().substring(0, 5), 196, 140);
  sprite.unloadFont();

  // Date

  sprite.setTextDatum(0);
  sprite.setTextColor(grays[1], bck);
  sprite.loadFont(middleFont);
  sprite.drawString("December 23", 196, 100);  ////////////////////////date hard coded

  // On/Off percent text

  sprite.setTextDatum(4);
  sprite.fillRect(0, 145, 50, 35, grays[9]);
  sprite.setTextColor(grays[3], grays[9]);
  sprite.drawString(OO[onOff], 12, 162);

  // sprite.unloadFont();

  // sprite.setTextDatum(4);
  // sprite.setTextColor(grays[1], bck);
  // sprite.loadFont(valueFont);
  // sprite.drawString(String((int)(value / 10.00)), 24, 124);
  // sprite.setTextColor(grays[3], bck);
  // sprite.drawString(secs, 362, 78);  /// /////////////////////////////////seconds
  // sprite.unloadFont();

  // sprite.setTextColor(grays[7], bck);
  // sprite.drawString(String((int)x), 150, 50, 4);
  // sprite.drawString(String((int)y), 250, 50, 4);
  //gfx->draw16bitBeRGBBitmap(40, 120, (uint16_t *)sprite.getPointer(), 400, 240);
  sprite.pushSprite(10, 10);

  lcd.display();
}

// void readEncoder() {
//   static int pos = 0;
//   encoder.tick();

//   int newPos = encoder.getPosition();
//   if (pos != newPos) {
//     if (newPos > pos)
//       angle = angle + inc;
//     if (newPos < pos)
//       angle = angle - inc;

//     pos = newPos;
//   }
//   if (angle < 0)
//     angle = 359;

//   if (angle >= 360)
//     angle = 0;
// }

void loop() {
  // readEncoder();

  for (int i = 0; i < 24; i++)
    PPgraph[i] = random(1, 12);

  // if (digitalRead(BUTTON) == 0) {
  //   if (deb == 0) {
  //     deb = 1;
  //     onOff = !onOff;
  //     draw();
  //   }
  // } else deb = 0;

  // if (read_touch(&xt, &yt) == 1) {
  //   if (yt < 240) angle = angle - 3;
  //   else angle = angle + 3;
  // }

  second1 = rtc.getSecond();

  if (second1 < 10) secs = "0" + String(second1);
  else secs = String(second1);

  if (second1 != second2) {
    second2 = second1;
    draw();
  }

  value = map(angle, 0, 359, 1000, 0);
  if (angle != prev) {
    draw();
    prev = angle;
  }
}
