#include <Servo.h>
#include <Ticker.h>
#include <StateMachine.h>
#include <TCS3200.h>
#define SERIAL_DEBUG 

#define TCS3200_S0 7
#define TCS3200_S1 8
#define TCS3200_S2 4
#define TCS3200_S3 5
#define TCS3200_OUT 6
#define TCS3200_LED 9

// ¿ Que pasa si aumentamos la velocidad ?
#define SERVO_PEEKPOWER 120
#define SERVO_STOPPOWER 90
#define IRinterval  50
#define SMinterval  100
const int buttonPin = 2;
const int motorPin =  10;
const int IRPin =  3; 

int buttonState = 0;
int IRState = 0;

uint8_t IRMAXReadings = 4;
uint8_t IRCurrentCounter = 0;
bool statusColorRead = false;
bool statusDrumMoved = false;

TCS3200 CS( TCS3200_S2, TCS3200_S3, TCS3200_OUT, TCS3200_S0, TCS3200_S1, TCS3200_LED );

void handleIREvent(){
  bool IRValue = digitalRead(IRPin);
    IRCurrentCounter++;
    if( IRValue != IRState && IRCurrentCounter >= IRMAXReadings ) {
      IRCurrentCounter = 0;
      IRState = IRValue;
      if( !IRState ){
        statusDrumMoved = true;
        Serial.println( "statusDrumMoved " );
      }
      Serial.println( IRState );
    }
}

void handleButton(){
  bool buttonValue = digitalRead(buttonPin);
  if (buttonValue != buttonState ) {
    buttonState = buttonValue;
    handleButtonEvent( buttonState );
  }
}

Servo myservo;
Ticker IRTicker(handleIREvent, IRinterval, 0, MILLIS );
Ticker ButtonTicker(handleButton, IRinterval, 0, MILLIS );
StateMachine colorDrum = StateMachine();

void handleSMRun(){
  colorDrum.run();
}
Ticker SMTicker(handleSMRun, SMinterval, 0, MILLIS );

//----- State List ------
void S2_stopDrum(){
  myservo.write(SERVO_STOPPOWER);
  Serial.println("Stop Drum");
  statusColorRead = false;
  statusDrumMoved = false;
}

void S0_readColor(){
  Serial.println("Color read");
  if(colorDrum.executeOnce){
    CS.LEDON( true );
    delay( 2000 );
    CS.LEDON( false );
    statusColorRead = true;
  }
}

void S1_moveDrum(){
  Serial.println("Move Drum");
  myservo.write(SERVO_PEEKPOWER);
  statusColorRead = false;
}

//----- Transition List ------
bool readState(){
  return !IRState && statusColorRead;
}

bool finishMove(){
  return statusDrumMoved;
}

bool readyToRead(){
  return true;
}

State* S0 = colorDrum.addState(&S0_readColor); 
State* S1 = colorDrum.addState(&S1_moveDrum); 
State* S2 = colorDrum.addState(&S2_stopDrum);

void setup() {
  Serial.begin(9600);
  
  pinMode(motorPin, OUTPUT);
  pinMode(IRPin, INPUT);
  pinMode(buttonPin, INPUT);
  myservo.attach(motorPin);

  
  CS.begin();
  CS.nSamples(40);
  CS.setRefreshTime(200);
  CS.setFrequency(TCS3200_FREQ_HI);
  CS.LEDON( false );
  IRTicker.start();
  SMTicker.start();
  ButtonTicker.start();
  S0->addTransition(&readState,S1);
  S1->addTransition(&finishMove,S2);
  S2->addTransition(&readyToRead,S0);
}

void loop() {
  ButtonTicker.update();
  IRTicker.update();
  SMTicker.update();
}

void handleButtonEvent(int state) {
  if(!state) {
    myservo.write(SERVO_PEEKPOWER);
  } else {
    myservo.write(SERVO_STOPPOWER);
  }
}
