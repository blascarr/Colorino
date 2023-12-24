// --- MENU VARIABLES ---

int refreshTime = 500;
int samples = 50;
TCS3200_LEDStatus ledToReadState = TCS3200_LEDON;
enum Colors {
	WHITE = 1,
	BLACK = 0,
	YELLOW = 2,
	ORANGE = 3,
	RED = 4,
	GREEN = 5,
	BLUE = 6,
	BROWN = 7
};
const char *colorNames[] = {"WHITE", "BLACK", "YELLOW", "ORANGE",
							"RED",	 "GREEN", "BLUE",	"BROWN"};

enum RGBMode { RGB, RAW };
int manualColorCal = 0;
int manualServoCal = SERVO_PEEKPOWER;
int uServoCal = 0;
RGBMode rgbState = RGB; // Default Mode - RGB
String freqStates[4] = {" - HIGH 100%", " - MID 20%", " - LOW 2%", " - OFF 0%"};

#include "Menu/CalibrationMenu.h"
// #include "Menu/ConfigurationMenu.h"
// #include "Menu/EEPROMMenu.h"
#include "Menu/MainMenu.h"
