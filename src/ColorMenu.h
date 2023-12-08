#if defined(ESP8266)
#include <streamFlow.h>
#endif

#include <menu.h>
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>
#define MAX_DEPTH 5

using namespace Menu;

#ifdef LCD_SUPPORT
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <menuIO/PCF8574Out.h>	//arduino I2C LCD
#include <menuIO/chainStream.h> // concatenate multiple input streams (this allows adding a button to the encoder)
#include <menuIO/encoderIn.h>	//quadrature encoder driver and fake stream
#include <menuIO/keyIn.h> //keyboard driver and fake stream (for the encoder button)

LiquidCrystal_PCF8574 lcd(LCD_I2C_DIR);

// ---  Define INPUTS ---
encoderIn<encA, encB> encoder; // simple quad encoder driver
encoderInStream<encA, encB>
	encStream(encoder, ENC_SENSIVITY); // simple quad encoder fake Stream
keyMap encBtn_map[] = {
	{-encBtn,
	 defaultNavCodes[enterCmd].ch}}; // negative pin numbers use internal
									 // pull-up, this is on when low
keyIn<1> encButton(encBtn_map);		 // 1 is the number of keys
menuIn *inputsList[] = {&encStream, &encButton};
chainStream<2> in(inputsList);
MENU_OUTPUTS(out, MAX_DEPTH,
			 LCD_OUT(lcd, {0, 0, LCD_I2C_COLUMNS, LCD_I2C_ROWS}), NONE);
#else

// ---  Define INPUTS ---
serialIn in(Serial);

MENU_OUTPUTS(out, MAX_DEPTH, SERIAL_OUT(Serial), NONE);

#endif