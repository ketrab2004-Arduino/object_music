#include "MusicController.h"


#pragma region MusicNote
bool MusicNote::finished()
{
    bool finished = finishTime < millis();
    if (finished) empty();
    return finished;
}

void MusicNote::empty()
{
    finishTime = 0;
}

MusicNote::operator bool() { return finishTime != 0; }
#pragma endregion


#pragma region MusicController
MusicController::MusicController (
    uint8_t buzzers,
    uint16_t PROGMEMSongPos
    #if USE_IMAGERY
    , Adafruit_SPITFT *screen
    , Adafruit_ImageReader *reader
    #endif
) {
    buzzerPins = buzzers;
    songPROGMEMLocation = PROGMEMSongPos;

    #if USE_IMAGERY
    tft = screen;
    imageReader = reader;
    #endif
}

void MusicController::resetSettingValues()
{
    fillTextCache(primaryCache);
    fillTextCache(secondaryCache);
    settingPassedMiddle = false;
    settingDepth = 0;
}

uint16_t MusicController::getSongPos() { return songPos; }
MusicState MusicController::getState() { return state; }
uint8_t MusicController::getOctave() { return octave; }
uint16_t MusicController::getBPM() { return bpm; }
MusicNote MusicController::getCurrentNote() { return currentNote; }

uint16_t MusicController::getNoteLength(int first, int second)
{
    return
        ((1152 / second) * first) // 1152 is divisable by 9, 32 and etc.
        / 64 * bpm; // apply bpm (64 seconds in a minute because divisable by 32 and helps offset the extra 152ms)
}
uint16_t MusicController::getNoteFrequency(char note)
{
    uint16_t toReturn = 0;
    switch (note) {
        case 'c': toReturn = 32; break;
        case 'C': toReturn = 34; break;
        case 'd': toReturn = 36; break;
        case 'D': toReturn = 38; break;
        case 'e': toReturn = 41; break;
        case 'f': toReturn = 43; break;
        case 'F': toReturn = 46; break;
        case 'g': toReturn = 49; break;
        case 'G': toReturn = 52; break;
        case 'a': toReturn = 55; break;
        case 'A': toReturn = 58; break;
        case 'b': toReturn = 61; break;
        case '_': // toReturn is already 0
        default: break;
    }

    return toReturn * pow(2, octave);
}

char MusicController::getCharAt(uint16_t pos)
{
    return pgm_read_byte_near(songPROGMEMLocation + pos); // shows "unknown register name 'r0'" in vscode, but compiles with no issue
}

void MusicController::changeValueInTextCache(String &cache, unsigned int pos, char desiredValue)
{
    if (pos >= cache.length()) {
        for (unsigned int i = cache.length(); i <= pos; i++) {
            cache += ' ';
        }
    }

    cache.setCharAt(pos, desiredValue);
}
void MusicController::fillTextCache(String &cache, char toFillWith = ' ')
{
    for (unsigned int i = 0; i < cache.length(); i++)
    {
        changeValueInTextCache(cache, i, toFillWith);
    }
}
int MusicController::textCacheToInt(String &cache)
{
    cache.trim(); // trim whitespace (before and after)
    return cache.toInt();
}

void MusicController::playNote()
{
    currentNote.finishTime = millis() + currentNote.length;

    #if 0 // notes log
    debugF("Playing note, current char: ");
    debug(currentChar);
    debugF(", ");
    debugln(songPos);

    debug(currentNote.length);
    debugF("ms, ");
    debug(currentNote.frequency);
    debuglnF("hz");

    debuglnF("=-=-=-=-=-=-=-=-=-=-=");
    #endif

    if (currentNote.frequency == 0) {
        noTone(buzzerPins);
    } else {
        tone(buzzerPins, currentNote.frequency, currentNote.length);
    }
}

void MusicController::doStep()
{
    if (state == MusicState::FINISHED || state == MusicState::ERRORED) return; // don't do loop when finished

    currentChar = getCharAt(songPos);

    if (state != MusicState::TONE) { // don't skip spaces and etc when in note mode (because it means the end of the note)
        switch (currentChar)
        {
            case '\n': // ignore spaces and newlines
            case ' ':
                songPos++;
                return;

            case '\0': // end of string char
                songPos++; // increase so that it shows the total song length
                state = MusicState::FINISHED; // song is finished
                return;

            case '[':
                state = MusicState::SETTING;
                songPos++;
                return;

            default:
                break;
        }
    }

    #if 0 // char log
    if (lastChar != currentChar) {
        debugF("Current char: ");
        debug(currentChar);
        debugF(" at pos: ");
        debugln(songPos);

        debuglnF("=-=-=-=-=-=-=-=-=-=-=");
    }
    #endif

    switch (state)
    {
        case MusicState::NOTE:
            doNoteStep();
            break;

        case MusicState::TONE:
            doToneStep();
            break;

        case MusicState::SETTING:
            doSettingsStep();
            break;

        default:
            break;
    }
    lastChar = currentChar;
}

void MusicController::doNoteStep()
{
    if (!currentNote.finished()) { // if not finished playing current note
        return; // return and don't increase songPos (wait)
    }

    currentNote.frequency = getNoteFrequency(currentChar);
    if (!hasTone()) {
        currentNote.length = getNoteLength(1, 4); // default note type

        playNote();
    } else {
        state = MusicState::TONE;
    }
    songPos++;
}

bool MusicController::hasTone()
{
    return isDigit(getCharAt(songPos +1));
}
void MusicController::doToneStep()
{
    if (isDigit(currentChar)) {

        changeValueInTextCache(
            settingPassedMiddle ? secondaryCache : primaryCache,
            settingDepth,
            currentChar
        );
        settingDepth++;
        songPos++;
        return;

    } else if (currentChar == '/') {
        if (!settingPassedMiddle) {
            settingPassedMiddle = true;
            settingDepth = 0; // reset
            songPos++; // pass middle 1'/'4
            return;
        }
    } else { // not a digit nor a /, so end of block
        if (settingPassedMiddle) {
            currentNote.length = getNoteLength(
                textCacheToInt(primaryCache),
                textCacheToInt(secondaryCache)
            );

            playNote();

            resetSettingValues();
            state = MusicState::NOTE;

            //songPos++; don't go to next char, because current char could be a new note
            return;
        }
    }

    // big error
    debugF("ERROR: something is missing at the note length notation at note: ");
    debug(currentChar);
    debugF(", ");
    debug(songPos);
    debugF("; primary: '");
    debug(primaryCache);
    debugF("', secondary: '");
    debug(secondaryCache);
    debuglnF("'");
    state = MusicState::ERRORED; // stop playing the song
}

void MusicController::doSettingsStep()
{
    bool end = currentChar == ']';
    if (end || currentChar == ';') {

        if (primaryCache.startsWith(F("oct")) || primaryCache.startsWith(F("octave"))) {
            octave = textCacheToInt(secondaryCache);
        } else if (primaryCache.startsWith(F("bpm"))) {
            bpm = textCacheToInt(secondaryCache);
        }
        #if USE_IMAGERY
        else if (primaryCache.startsWith(F("img")) || primaryCache.startsWith(F("image"))) {
            ImageReturnCode code = imageReader->drawBMP(secondaryCache.c_str(), *tft, 0,0);

            if (code != ImageReturnCode::IMAGE_SUCCESS) {
                debugF("WARNING: something went wrong with loading the image '");
                debug(secondaryCache);
                debugF("', return code: ");
                debugln(code);
            }
        }
        #endif
        else {
            debugF("WARNING: the setting '");
            debug(primaryCache);
            debugF("' with value '");
            debug(secondaryCache);
            debugF("' is not a known setting, pos: ");
            debugln(songPos);
        }

        resetSettingValues(); // reset caches and etc.

        if (end) state = MusicState::NOTE; // if end of setting block, go back to note mode
    } else if (currentChar == '=') {
        settingPassedMiddle = true;
        settingDepth = 0;
    } else {
        changeValueInTextCache(
            settingPassedMiddle ? secondaryCache : primaryCache,
            settingDepth,
            currentChar
        );
        settingDepth++;
    }
    
    songPos++;
}
#pragma endregion
