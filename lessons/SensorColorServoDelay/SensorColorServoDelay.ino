#include <SimpleKalmanFilter.h>
#include <Servo.h>

#include <TCS3200.h>
#define SERIAL_DEBUG 

#define TCS3200_S0 7
#define TCS3200_S1 8
#define TCS3200_S2 4
#define TCS3200_S3 5
#define TCS3200_OUT 6
#define TCS3200_LED 9

#define SERVO_PEEKPOWER 110
#define SERVO_STOPPOWER 90

TCS3200 CS( TCS3200_S2, TCS3200_S3, TCS3200_OUT, TCS3200_S0, TCS3200_S1, TCS3200_LED );
Servo myservo;

const int buttonPin = 2;
const int motorPin =  10;
const int IRPin =  3; 

int buttonState = 0;
int IRState = 0;

unsigned long auxtimer;
uint8_t IRinterval = 100;
uint8_t IRCounterEachInterval = 4;
uint8_t IRCurrentCounter = 0;
bool IRLastState;
bool moveServo = true;

void setup() {
  Serial.begin(9600);
  
  //Serial.println("Hello TCS3200");
  pinMode(motorPin, OUTPUT);
  pinMode(IRPin, INPUT);
  pinMode(buttonPin, INPUT);
  myservo.attach(motorPin);
  
  CS.begin();

  CS.nSamples(40);
  CS.setRefreshTime(200);
  CS.setFrequency(TCS3200_FREQ_HI);

  //CS.calibration(0);
  CS.loadCal(0);
  CS.LEDON( false );
  IRLastState != IRState;
}

void loop() {

  bool buttonValue = digitalRead(buttonPin);
  if (buttonValue != buttonState ) {
    buttonState = buttonValue;
    if(!buttonState){
      myservo.write(SERVO_PEEKPOWER);
    }else {
      myservo.write(SERVO_STOPPOWER);
    }
  }

  if( millis() - auxtimer > IRinterval/IRCounterEachInterval){
    auxtimer = millis();
    bool IRValue = digitalRead(IRPin);
    IRCurrentCounter++;
    if( IRValue != IRState && IRCurrentCounter >= IRCounterEachInterval ) {
      IRCurrentCounter = 0;
      IRState = IRValue;
      if( IRState == LOW ){
        Serial.println( "LOW Value " );
        moveServo = false;
        myservo.write(SERVO_PEEKPOWER);
      }
      Serial.println( IRState );
    }
  };

  /*if ( IRState == IRLastState && moveServo) {
    myservo.write(SERVO_STOPPOWER);
    Serial.println( "Wait..." );
    delay(2000);
    moveServo = true;
    
  } */

  /*if( moveServo ){
    myservo.write(SERVO_PEEKPOWER);
  }*/
  /*if (CS.onChangeColor()) {
    Serial.println(  CS.readColorID()  );
    Serial.println(  CS.readColor()  );
  }*/
}
