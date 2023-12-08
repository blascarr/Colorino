#include <Arduino.h>
#define SERIAL_DEBUG

#include "TCS3200Debug.h"
#include <Bounce2.h>
#include <Servo.h>
#include <TCS3200.h>
#include <Ticker.h>

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

#include "ColorMenu.h"

uint8_t SERVO_PEEKPOWER = 102;
uint8_t SERVO_STOPPOWER = 90;

TCS3200 CS(TCS3200_S2, TCS3200_S3, TCS3200_OUT, TCS3200_S0, TCS3200_S1,
		   TCS3200_LED);
SerialDebugger SerialDebug = SerialDebugger();
TCS3200Debug CSDebug(CS, SerialDebug);
Servo servoDrum;

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
#ifdef _TCS3200COLORSM_H
	servoSelector.attach(SELECTORSERVO_PIN);
	colorSMInit();
#endif
#ifdef LCD_SUPPORT
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