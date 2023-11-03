#include <Arduino.h>
#define SERIAL_DEBUG
#include "ColorMenu.h"
#include <Bounce2.h>
#include <Servo.h>
#include <Ticker.h>
#include "TCS3200Debug.h"
#include <TCS3200.h>

#define TCS3200_S0 6
#define TCS3200_S1 7
#define TCS3200_S2 2
#define TCS3200_S3 3
#define TCS3200_OUT 5
#define TCS3200_LED 4

#define IR_PIN 13
#define DRUMSERVO_PIN 9
#define SELECTORSERVO_PIN 10
#define BTN_PIN 12
#define SERVO_PEEKPOWER 105
#define SERVO_STOPPOWER 90
#define IRinterval 50
#define BTNinterval 70

TCS3200 CS(TCS3200_S2, TCS3200_S3, TCS3200_OUT, TCS3200_S0, TCS3200_S1, TCS3200_LED);
SerialDebugger SerialDebug = SerialDebugger();
TCS3200Debug CSDebug(CS, SerialDebug);
Servo servoDrum;
Servo servoSelector;
float positions[] = {0, 22.5, 45, 67.5, 90, 1112.5, 135, 157.5, 180};
float selectorOffset = 5;

Bounce2::Button button = Bounce2::Button();
Bounce IREvent = Bounce();

bool IRFired = false;
int currentColor = 0;

void handleButton()
{
  button.update();
  if (button.changed())
  {
    if (button.pressed())
    {
      servoDrum.write(SERVO_PEEKPOWER);
    }
    else
    {
      servoDrum.write(SERVO_STOPPOWER);
    }
  }
}

void handleIREvent()
{
  IREvent.update();
  if (IREvent.changed())
  {
    bool debouncedInput = IREvent.read();
    IRFired = debouncedInput == false;
  }
}

#include "ColorSM.h"
#include "CalibratorSM.h"
#include "MenuEvents.h"

void setup()
{
  Serial.begin(9600);
  servoDrum.attach(DRUMSERVO_PIN);
  servoSelector.attach(SELECTORSERVO_PIN);
  button.attach(BTN_PIN, INPUT);
  button.interval(BTNinterval);
  button.setPressedState(LOW);
  IREvent.attach(IR_PIN, INPUT);
  IREvent.interval(IRinterval);
  servoDrum.write(SERVO_STOPPOWER);

  CS.begin();
  CS.nSamples(40);
  CS.setRefreshTime(200);
  CS.setFrequency(TCS3200_FREQ_HI);
  CS.loadBW();
  CS.loadCT();
  colorSMInit();
  colorSMTest();
}

void loop()
{
  handleButton();
  handleIREvent();
  SMTicker.update();
  SMTickerTest.update();
  nav.poll();
}
