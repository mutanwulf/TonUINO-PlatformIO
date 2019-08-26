#ifndef MAIN_H
    #define MAIN_H
    /*
    TonUINO Version 2.1.1
    created by Thorsten Voß and licensed under GNU/GPL.
    change by 2019-08 M.Schwager modified for platformio
    */
    #include <SoftwareSerial.h>
    #include <DFMiniMp3.h>
    #include <EEPROM.h>
    #include <JC_Button.h>
    #include <MFRC522.h>
    #include <SPI.h>
    #include <avr/sleep.h>

    // uncomment the below line to enable five button support
    //#define FIVEBUTTONS

    static const uint32_t cardCookie = 362375028; // new code
    // static const uint32_t cardCookie = 322417479; //old code

    // DFPlayer Mini
    SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
    uint16_t numTracksInFolder;
    uint16_t currentTrack;
    uint16_t firstTrack;
    uint8_t queue[255];
    uint8_t volume;

    struct folderSettings {
    uint8_t folder;
    uint8_t mode;
    uint8_t special;
    uint8_t special2;
    };

    //Debugmodus mit Ausgaben
    #define DebugModus true

    // If use of Statusleds
    #define useStatusLED

    // Statusled enable FastLED 
    #ifdef useStatusLED
        // #include "StatusLED.h" //FastLED
        #include <FastLED.h>
        // #include "SmartLEDTon.h"
        #define LED_PIN     5
        #define COLOR_ORDER GRB
        #define LED_TYP     WS2812B
        #define ANZAHL_LEDS    16

        #define BRIGHTNESS  60
        #define FRAMES_PER_SECOND 60

        CRGB leds[ANZAHL_LEDS];
        #define COLOR_ORDER GRB   // Datasheet WS2812 : "Follow the order of GRB to sent data"
        #define OK_COLOR CRGB::Green
        #define KO_COLOR CRGB::Red
        #define WARNING_COLOR CRGB::Orange
        #define INIT_COLOR CRGB::Navy
        #define WAIT_COLOR CRGB::LightPink
        #define PLAY_COLOR CRGB::ForestGreen

        //StatusLEDs anhand der Anzahl der LEDs
        #if NUM_LEDS < 17 
            #define stsLED_1  1
            #define stsLED_2  1
            #define stsLED_3  2
            #define stsLED_4  2
            #define stsLED_5  3
            #define stsLED_6  3
            #define stsLED_7  4
            #define stsLED_8  4
            #define stsLED_9  5
            #define stsLED_10  5
            #define stsLED_11  6
            #define stsLED_12  6
            #define stsLED_13  7
            #define stsLED_14  7
            #define stsLED_15  8
            #define stsLED_16  8
            #define stsLED_17  9
            #define stsLED_18  9
            #define stsLED_19  10
            #define stsLED_20  10
            #define stsLED_21  11
            #define stsLED_22  11
            #define stsLED_23  12
            #define stsLED_24  12
            #define stsLED_25  13
            #define stsLED_26  13
            #define stsLED_27  14
            #define stsLED_28  14
            #define stsLED_29  15
            #define stsLED_30  15
            #define stsLED_31  16
            #define stsLED_32  16
        #else
            #define stsLED_1  1
            #define stsLED_2  2
            #define stsLED_3  3
            #define stsLED_4  4
            #define stsLED_5  5
            #define stsLED_6  6
            #define stsLED_7  7
            #define stsLED_8  8
            #define stsLED_9  9
            #define stsLED_10 10
            #define stsLED_11  11
            #define stsLED_12  12
            #define stsLED_13  13
            #define stsLED_14  14
            #define stsLED_15  15
            #define stsLED_16  16
            #define stsLED_17  17
            #define stsLED_18  18
            #define stsLED_19  19
            #define stsLED_20  20
            #define stsLED_21  21
            #define stsLED_22  22
            #define stsLED_23  23
            #define stsLED_24  24
            #define stsLED_25  25
            #define stsLED_26  26
            #define stsLED_27  27
            #define stsLED_28  28
            #define stsLED_29  29
            #define stsLED_30  30
            #define stsLED_31  31
            #define stsLED_32  32
        #endif
    #endif

    // this object stores nfc tag data
    struct nfcTagObject {
        uint32_t cookie;
        uint8_t version;
        folderSettings nfcFolderSettings;
        //  uint8_t folder;
        //  uint8_t mode;
        //  uint8_t special;
        //  uint8_t special2;
    };

    // admin settings stored in eeprom
    struct adminSettings {
        uint32_t cookie;
        byte version;
        uint8_t maxVolume;
        uint8_t minVolume;
        uint8_t initVolume;
        uint8_t eq;
        bool locked;
        long standbyTimer;
        bool invertVolumeButtons;
        folderSettings shortCuts[4];
        uint8_t adminMenuLocked;
        uint8_t adminMenuPin[4];
    };

    adminSettings mySettings;
    nfcTagObject myCard;
    folderSettings *myFolder;
    unsigned long sleepAtMillis = 0;
    static uint16_t _lastTrackFinished;

    static void nextTrack(uint16_t track);
    uint8_t voiceMenu(int numberOfOptions, int startMessage, int messageOffset,
                    bool preview = false, int previewFromFolder = 0, int defaultValue = 0, bool exitWithLongPress = false);

    //additional Subs and functions
    bool isPlaying();
    void setupCard();
    void resetCard();
    bool readCard(nfcTagObject *nfcTag);
    bool checkTwo ( uint8_t a[], uint8_t b[] );
    void writeCard(nfcTagObject nfcTag);
    void dump_byte_array(byte * buffer, byte bufferSize);
    void adminMenu(bool fromCard = false);
    void setstandbyTimer();
    void playFolder();
    bool askCode(uint8_t*);
    void playShortCut(uint8_t shortCut);
    bool setupFolder(folderSettings * theFolder);

    #ifdef useStatusLED
        void LEDshow();
        void switchOnLeds(int numToFill, uint32_t color);
    #endif

    bool knownCard = false;

    // MFRC522
    #define RST_PIN 9                 // Configurable, see typical pin layout above
    #define SS_PIN 10                 // Configurable, see typical pin layout above
    MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
    MFRC522::MIFARE_Key key;
    bool successRead;
    byte sector = 1;
    byte blockAddr = 4;
    byte trailerBlock = 7;
    MFRC522::StatusCode status;

    #define buttonPause A0
    #define buttonUp A1
    #define buttonDown A2
    #define busyPin 4
    #define shutdownPin 7
    #define openAnalogPin A7

    #ifdef FIVEBUTTONS
        #define buttonFourPin A3
        #define buttonFivePin A4
    #endif

    #define LONG_PRESS 1000

    Button pauseButton(buttonPause);
    Button upButton(buttonUp);
    Button downButton(buttonDown);
    #ifdef FIVEBUTTONS
        Button buttonFour(buttonFourPin);
        Button buttonFive(buttonFivePin);
    #endif

    bool ignorePauseButton = false;
    bool ignoreUpButton = false;
    bool ignoreDownButton = false;
    #ifdef FIVEBUTTONS
        bool ignoreButtonFour = false;
        bool ignoreButtonFive = false;
    #endif

#endif