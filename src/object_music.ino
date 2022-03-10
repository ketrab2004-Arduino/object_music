#include "settings.h"

#include <Extra_Debug.h>

#if USE_IMAGERY
    #include <Adafruit_GFX.h>           // 1.10.13  Adafruit GFX Library
    #include <Adafruit_ILI9341.h>       // 1.5.10   Adafruit ILI9341
    #include <SdFat.h>                  // 1.5.1    SdFat - Adafruit Fork
    #include <Adafruit_SPIFlash.h>      // 3.9.0    Adafruit SPIFlash
    #include <Adafruit_ImageReader.h>   // 2.7.0    Adafruit ImageReader Library

    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

    SdFat SD;
    Adafruit_ImageReader reader(SD);
#endif

#include "songs.h"
#include "MusicController.h"

MusicController music = MusicController(
    BUZZERS,
    (uint16_t)songNotes
    #if USE_IMAGERY
    , &tft
    , &reader
    #endif
);

void setup()
{
    pinMode(BUZZERS, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    #if USE_IMAGERY
        pinMode(TFT_BL, OUTPUT);
        analogWrite(TFT_BL, BRIGHTNESS);

        SD.begin(SD_CS, SD_SCK_MHZ(25));

        tft.begin();
        tft.setRotation(1);

        tft.fillScreen(ILI9341_BLACK);
    #endif
    
    debugBegin(115200);

    delay(1000);
}

void loop()
{
    music.doStep();
}
