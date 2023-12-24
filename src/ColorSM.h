#ifndef _TCS3200COLORSM_H
#define _TCS3200COLORSM_H

#include <StateMachine.h>
#define SMinterval 100

StateMachine colorDrum = StateMachine();
void handleSMRun() { colorDrum.run(); }
Ticker SMTicker(handleSMRun, SMinterval, 0, MILLIS);

#if CONTINUOUS_COLORSM
#define NUM_STATES 5
#else
#include "ResetSM.h"
#define NUM_STATES 6
#endif

enum STATE {
	ENTRY = 0,
	MOVECANDYTOSENSOR = 1,
	READCANDYCOLOR = 2,
	MOVESLIDER = 3,
	FREECANDY = 4
#if !CONTINUOUS_COLORSM
	,
	WAITSIGNAL = 5
#endif
};

STATE currentState = ENTRY;

void nextState() {
	currentState = static_cast<STATE>((currentState + 1) % NUM_STATES);
}
void S0_entry() {
	if (colorDrum.executeOnce) {
		servoDrum.write(SERVO_PEEKPOWER);
		currentState = ENTRY;
	}
}

void S1_moveDrum() {
	if (colorDrum.executeOnce) {
		servoDrum.write(SERVO_PEEKPOWER);
		nextState();
	}
}

void S2_readColor() {
	servoDrum.write(SERVO_STOPPOWER);
	if (colorDrum.executeOnce) {
		currentColor = CS.readLastColorID();
		nextState();
	}
}

void S3_selectorSlider() {
	if (colorDrum.executeOnce) {
		servoSelector.write(positions[currentColor] + selectorOffset);
		servoDrum.write(SERVO_PEEKPOWER);
		nextState();
	}
}

void S4_candyFree() {
	if (colorDrum.executeOnce) {
		servoDrum.write(SERVO_PEEKPOWER);
		nextState();
	}
}

bool entryState() { return IRFired && currentState == ENTRY; }
bool readState() { return !IRFired && currentState == MOVECANDYTOSENSOR; }
bool readyToRead() { return currentState == READCANDYCOLOR; }
bool colorRead() { return IRFired && currentState == MOVESLIDER; }
bool freeCandy() { return !IRFired && currentState == FREECANDY; }

State *S0 = colorDrum.addState(&S0_entry);	   // Candy Inside Drum
State *S1 = colorDrum.addState(&S1_moveDrum);  // Drum moves to color Sensor
State *S2 = colorDrum.addState(&S2_readColor); // Candy read
State *S3 = colorDrum.addState(&S3_selectorSlider); // Tube Selector moves
State *S4 = colorDrum.addState(&S4_candyFree);		// Drum moves to free candy

#if !CONTINUOUS_COLORSM
bool readyToWait() { return resetSMSignal && currentState == WAITSIGNAL; }
void S5_waitSignal() {
	if (colorDrum.executeOnce) {
		servoDrum.write(SERVO_STOPPOWER);
		nextState();
		resetSMSignal = false;
		SMTicker.pause();
	}
}
State *S5 = colorDrum.addState(&S5_waitSignal);
#endif

void colorSMInit() {
	S0->addTransition(&entryState, S1); // Candy Inside Drum
	S1->addTransition(&readState, S2);
	S2->addTransition(&readyToRead, S3); // Candy prepared to Read in CS
	S3->addTransition(&colorRead, S4); // Selector Moves if color has been read

#if CONTINUOUS_COLORSM
	S4->addTransition(&freeCandy, S0); // No wait and jump to the next state
#else
	S4->addTransition(&freeCandy, S5);
	S5->addTransition(&readyToWait, S0); // Wait until Reset Signal
#endif
	SMTicker.start();
}
#endif