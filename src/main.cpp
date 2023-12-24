#include <Arduino.h>
#define SERIAL_DEBUG

#include "TCS3200Debug.h"
#include <Bounce2.h>
#include <Servo.h>
#include <TCS3200.h>
#include <Ticker.h>

// #define ARDUINO_AVR_UNO
// #define ESP8266

#include "config.h"

#include "ColorMenu.h"

uint8_t SERVO_PEEKPOWER = 102;
uint8_t SERVO_STOPPOWER = 90;

TCS3200 CS(TCS3200_S2, TCS3200_S3, TCS3200_OUT, TCS3200_S0, TCS3200_S1,
		   TCS3200_LED);
SerialDebugger SerialDebug = SerialDebugger();
TCS3200Debug CSDebug(CS, SerialDebug);
Servo servoDrum;
Servo servoSelector;
float positions[] = {0, 25, 50, 78, 113, 140, 170, 170};
float selectorOffset = 0;

Bounce IREvent = Bounce();

bool IRFired = false;
int currentColor = 0;

void handleIREvent() {
	IREvent.update();
	if (IREvent.changed()) {
		bool debouncedInput = IREvent.read();
		IRFired = debouncedInput == false;
	}
}

// #include "ColorSM.h"
#include "CalibratorSM.h"
#include "MenuEvents.h"

void setup() {
	Serial.begin(9600);
	servoDrum.attach(DRUMSERVO_PIN);

	IREvent.attach(IR_PIN, INPUT);
	IREvent.interval(IRinterval);
	servoDrum.write(SERVO_STOPPOWER);

	CS.begin();
	CS.nSamples(40);
	CS.setRefreshTime(200);
	CS.setFrequency(TCS3200_FREQ_HI);
	CS.loadBW();
	CS.loadCT();

	servoSelector.attach(SELECTORSERVO_PIN);
	uServoCal = servoSelector.readMicroseconds();
#ifdef _TCS3200COLORSM_H
	colorSMInit();
#endif
#ifdef LCD_SUPPORT_BOARD
	encoder.begin();
	lcd.begin(16, 2);
	lcd.setBacklight(255);
	lcd.setCursor(0, 0);
#endif
	colorSMTest();
}

void loop() {
	handleIREvent();
#ifdef _TCS3200COLORSM_H
	SMTicker.update();
#endif
	SMTickerTest.update();
	nav.poll();
}