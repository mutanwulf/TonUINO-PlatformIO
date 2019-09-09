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
	#define FIVEBUTTONS

	// uncomment the below line to enable jack detected max volume support
	//#define JACKDETECT

	// Integration von einem LED Strip oder Ring (angepasst an die Anzahl der LEDs) - zum aktivieren // in den folgenden Zeilen löschen
	#define LED_SR        // uncomment the below line to enable LED Strip and Ring support
	//#define LED_SR_Switch // Möglichkeit die LEDs über die Tasten ein- und auszuschalten
	//#define LED_SR_Powersafe // Möglichkeit die LEDs über die Tasten ein- und auszuschalten

	#ifdef JACKDETECT
	  // Definition des Jackdetect Pins
	  #define jdPin 8
	#endif

	#ifdef JACKDETECT
	  // Variablen für Prüfung des Kopfhöreranschlusses
	  int jdMaxVolume = 12 ;     // Maximale Lautstärke wenn Kopfhörer angeschlossen ist
	  int jdInitVolume = 10 ;     // Initiale Lautstärke wenn Kopfhörer angeschlossen ist
	  int jackDetectState = HIGH ;         // aktueller Status - ob Kopfhörer angeschlossen ist
	  int lastJackDetectState = HIGH;     // vorhergehender Status - ob Kopfhörer angeschlossen ist
	  int beforeJackdetectVolume = 10;     // Lautstärke bevor Kopfhörer angeschlossen wurden
	  int beforeJackdetectMaxVolume = 10;     // Maximale Lautstärke bevor Kopfhörer angeschlossen wurden
	#endif

	#ifdef LED_SR
		#include <Adafruit_NeoPixel.h>
		#define LED_PIN    7              // Der Pin am Arduino vom dem das Daten Signal rausgeht
		#define LED_COUNT 18              // Anzahl an LEDs im Ring oder Strip
	 
		// Declare NeoPixel strip object:
		Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

		// Zählvarbiablen
		uint16_t loopCountdown;       // Runterzählen der Loops
		uint16_t lsrLoopCountWait;    // Definierte Anzahl wieviele Loops runtergezählt werden sollen, also wie lange gewartet wird
		uint8_t animationCountdown;   // Wie oft die einmalige Animation ausgeführt wird bevor es zurück in die Hauptschleife (Animationsmodus 0) geht
		uint8_t x;
		uint8_t y;
		uint8_t z;
		uint8_t i;

		// Datenvarbiablen
		uint32_t lsrColorUp = strip.Color(0, 255, 0);   // Farbe wird bei Animation nächstes Lied verwendet
		uint32_t lsrColorDown = strip.Color(0, 0, 255); // Farbe wird bei Animation Lied zurück verwendet
		uint8_t currentDetectedVolume;                  // Speichern der aktuellen Lautstärke für späteren Vergleich
		uint8_t lastDetectedVolume;                     // Speichern der Lautstärke um die Animation nur ein mal zu triggern
		uint8_t volumeScope;                            // Differenz der von euch eingestellten minimalen und maximalen Lautstärke
		uint8_t volumeScopeAmount;                      // Lautstärkenwert in deinem Scope
		uint8_t currentDetectedTrack;                   // Speichern des aktuellen Tracks für späteren Vergleich
		uint8_t lastDetectedTrack;                      // Speichern des Tracks um die Animation nur ein mal zu triggern
		uint8_t lsrAnimationMode;                       // Animationsmodus - 0: Daueranimation, 1-2 einmalige Animation (als Unterbrechung zu 0)
		uint8_t lsrAnimationTrackMode;                  // Bei Animationsmodus Liedwechsel bestimmung der Farbe und Richtung
		uint32_t lsrHueCalc;                            // Zwischenspeicher einer Farbe
		uint32_t lsrColors;                             // Zwischenspeicher einer Farbe
		uint8_t lsrColorR[LED_COUNT];                   // Zwischenspeicher des Rot-Wertes für alle LEDs
		uint8_t lsrColorG[LED_COUNT];                   // Zwischenspeicher des Grün-Wertes für alle LEDs
		uint8_t lsrColorB[LED_COUNT];                   // Zwischenspeicher des Blau-Wertes für alle LEDs
	#endif

	#ifdef LED_SR_Switch
		bool lsrEnable = true;
	#endif

	#ifdef LED_SR_Powersafe
		bool lsrPSEnable = true;
	#endif

	static const uint32_t cardCookie = 322417479;

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
	bool isPlaying();
	bool checkTwo ( uint8_t a[], uint8_t b[] );
	void writeCard(nfcTagObject nfcTag);
	void dump_byte_array(byte * buffer, byte bufferSize);
	void adminMenu(bool fromCard = false);
	bool knownCard = false;

#endif