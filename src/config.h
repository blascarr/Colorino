#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)

#define TCS3200_S0 6
#define TCS3200_S1 7
#define TCS3200_S2 2
#define TCS3200_S3 3
#define TCS3200_OUT 5
#define TCS3200_LED 4

#define IR_PIN 8
#define DRUMSERVO_PIN 9
#define SELECTORSERVO_PIN 10
#define IRinterval 10
bool IR_INPUT_PULLUP = true;

#define CONTINUOUS_COLORSM false
#if !CONTINUOUS_COLORSM
bool resetSMSignal = false;
#endif

/* Global Variables */
bool ledState = true;
int freq = TCS3200_FREQ_HI;
float positions[] = {0, 25, 50, 78, 113, 140, 170, 170};
float selectorOffset = 0;
bool IRFired = true;
int currentColor = 0;

#define SMinterval 100
#define SMTestinterval 100
uint8_t SERVO_PEEKPOWER = 102;
uint8_t SERVO_STOPPOWER = 90;

/* Menu Global Variables */
int refreshTime = 500;
int samples = 50;
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

#define LCD_SUPPORT true

#define LCD_I2C_DIR 0x3f
#define LCD_I2C_COLUMNS 16
#define LCD_I2C_ROWS 2

#ifndef LCD_I2C_COLUMNS
#define LCD_I2C_COLUMNS 16
#endif

#ifndef LCD_I2C_ROWS
#define LCD_I2C_ROWS 2
#endif

#if (defined(LCD_SUPPORT) && !defined(ARDUINO_AVR_UNO))
#define LCD_SUPPORT_BOARD
#endif

#ifdef LCD_SUPPORT_BOARD
#include "Menu/LCD_MSG_Definition.h"
// Encoder /////////////////////////////////////
#define encA 11
#define encB 12
// this encoder has a button here
#define encBtn 13
#define ENC_SENSIVITY 4
#else
#include "Menu/MSG_Definition.h"
#endif

#endif

#ifdef ESP8266

#define TCS3200_S0 6
#define TCS3200_S1 7
#define TCS3200_S2 2
#define TCS3200_S3 3
#define TCS3200_OUT 5
#define TCS3200_LED 4

#define IR_PIN 8
#define DRUMSERVO_PIN 9
#define SELECTORSERVO_PIN 10
#define IRinterval 10

#define LCD_SUPPORT true
#define LCD_I2C_DIR 0x3f
#define LCD_I2C_COLUMNS 16
#define LCD_I2C_ROWS 2

#ifndef LCD_I2C_COLUMNS
#define LCD_I2C_COLUMNS 16
#endif

#ifndef LCD_I2C_ROWS
#define LCD_I2C_ROWS 2
#endif
#ifdef LCD_SUPPORT
// Encoder /////////////////////////////////////
#define encA 11
#define encB 12
// this encoder has a button here
#define encBtn 13
#define ENC_SENSIVITY 4
#endif

#endif
