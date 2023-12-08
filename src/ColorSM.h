#ifndef _TCS3200COLORSM_H
#define _TCS3200COLORSM_H

#include <StateMachine.h>
#define NUM_STATES 5
#define SMinterval 100

Servo servoSelector;
float positions[] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180};
float selectorOffset = 5;

enum STATE {
	ENTRY = 0,
	MOVECANDYTOSENSOR = 1,
	READCANDYCOLOR = 2,
	MOVESLIDER = 3,
	FREECANDY = 4
};

STATE currentState = ENTRY;
STATE previousState = FREECANDY;

StateMachine colorDrum = StateMachine();

void handleSMRun() { colorDrum.run(); }

Ticker SMTicker(handleSMRun, SMinterval, 0, MILLIS);

void nextState() {
	currentState = static_cast<STATE>((currentState + 1) % NUM_STATES);
}
void S0_entry() {
	if (colorDrum.executeOnce) {
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
		nextState();
	}
}

void S4_candyFree() {
	if (colorDrum.executeOnce) {
		servoDrum.write(SERVO_PEEKPOWER);
		nextState();
	}
}

bool entryState() { return currentState == ENTRY; }

bool readState() { return !IRFired && currentState == MOVECANDYTOSENSOR; }

bool colorRead() { return currentState == READCANDYCOLOR; }

bool readyToRead() { return currentState == READCANDYCOLOR; }

State *S0 = colorDrum.addState(&S0_entry);
State *S1 = colorDrum.addState(&S1_moveDrum);
State *S2 = colorDrum.addState(&S2_readColor);
State *S3 = colorDrum.addState(&S3_selectorSlider);
State *S4 = colorDrum.addState(&S4_candyFree);

void colorSMInit() {
	S0->addTransition(&entryState, S1);
	S1->addTransition(&readState, S2);
	S2->addTransition(&colorRead, S3);
	S3->addTransition(&readyToRead, S4);
	S4->addTransition(&readyToRead, S0);
	SMTicker.start();
}
#endif