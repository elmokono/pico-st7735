// CS_PIN = GP17
// DC_PIN = GP21
// RESET_PIN = GP20
/***************************************************/
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "sprites.h"

#define TFT_DC 21
#define TFT_CS 17
#define TFT_RST 20

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16 *canvas = new GFXcanvas16(128, 128);

uint lastMillis;
float x, y, fps;
int16_t sx = 0;
int16_t sy = 0;
int16_t sw = 128;
int16_t sh = 128;

void setup()
{
  // while (!Serial) { delay(10); }
  Serial.begin(115200);
  tft.initR(INITR_144GREENTAB);
  tft.setRotation(0);
  tft.fillScreen(ST7735_CYAN);
  x = y = fps = 0;
  lastMillis = millis();
}

void getFps(void)
{
  fps++;
  if (millis() - lastMillis >= 1000)
  {
    Serial.print(fps);
    Serial.println(" fps");
    fps = 0;
    lastMillis = millis();
  }
}

void loop(void)
{

  // canvas -> fillScreen(ST7735_BLACK);
  canvas->drawRGBBitmap(sx, sy, bgImage, sw, sh);
  if (x > 112)
  {
    x = 0;
    y++;
    if (y > 112)
      y = 0;
  }
  x++;
  canvas->drawRGBBitmap(x, y, sprite, 16, 16);

  getFps();

  tft.drawRGBBitmap(sx, sy, canvas->getBuffer(), sw, sh);
}
