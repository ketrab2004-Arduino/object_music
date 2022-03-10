#ifndef __MUSICCONTROLLER__
#define __MUSICCONTROLLER__

#include <stdint.h>
#include <Arduino.h>
#include "settings.h"
#include <Extra_Debug.h>

#if USE_IMAGERY
    #include <Adafruit_GFX.h>
    #include <Adafruit_ILI9341.h>
    #include <SdFat.h>
    #include <Adafruit_SPIFlash.h>
    #include <Adafruit_ImageReader.h>
#endif

enum MusicState: int8_t {
    NOTE,
    TONE,
    SETTING,
    FINISHED,
    ERRORED
};

struct MusicNote {
    uint16_t frequency;
    uint16_t length;

    unsigned long finishTime = 0; // at what time ( using millis() ) this note ends

    bool finished();

    void empty();
    operator bool();
};

class MusicController {
protected:
    uint16_t songPROGMEMLocation;
    uint8_t buzzerPins;

    #if USE_IMAGERY
    Adafruit_SPITFT *tft;
    Adafruit_ImageReader *imageReader;
    #endif

    char currentChar;
    char lastChar;

    String primaryCache = "";
    String secondaryCache = "";
    bool settingPassedMiddle = false; // for tones and settings
    uint16_t settingDepth = 0;
    void resetSettingValues();

    uint16_t songPos = 0;
    MusicState state = MusicState::NOTE;
    int8_t octave = 4;
    uint16_t bpm = 120;

    MusicNote currentNote;

public:
    MusicController(
        uint8_t buzzers,
        uint16_t PROGMEMSongPos
        #if USE_IMAGERY
        , Adafruit_SPITFT *screen
        , Adafruit_ImageReader *reader
        #endif
    );

    #pragma region Getters
    uint16_t getSongPos();
    MusicState getState();
    uint8_t getOctave();
    uint16_t getBPM();
    MusicNote getCurrentNote();
    #pragma endregion

    uint16_t getNoteLength(int first, int second);
    uint16_t getNoteFrequency(char note);

    char getCharAt(uint16_t pos);

    void changeValueInTextCache(String &cache, unsigned int pos, char desiredValue);
    void fillTextCache(String &cache, char toFillWith = ' ');
    int textCacheToInt(String &cache);

    void playNote();

    void doStep();

    void doNoteStep();

    bool hasTone();
    void doToneStep();

    void doSettingsStep();
};

#endif