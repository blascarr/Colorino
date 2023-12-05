#ifndef _TCS3200CALIBRATIONSM_H
#define _TCS3200CALIBRATIONSM_H

#include <StateMachine.h>
#define SMTestinterval 100
StateMachine colorTestDrum = StateMachine();

enum TESTSTATE {
	MOVEDRUM = 0,
	STOPDRUM = 1,
};
TESTSTATE currentTestState = MOVEDRUM;

void handleTestSMRun() { colorTestDrum.run(); }

Ticker SMTickerTest(handleTestSMRun, SMTestinterval, 0, MILLIS);

void ST0_moveDrum() {
	if (colorTestDrum.executeOnce) {
		// Serial.println("Move Drum while IR ON");
		servoDrum.write(SERVO_PEEKPOWER);
	}
}

void ST1_moveDrum() {
	if (colorTestDrum.executeOnce) {
		// Serial.println("Move Drum while IR OFF");
	}
}

void ST2_stopDrum() {
	Serial.println("Stop Drum");
	currentTestState = STOPDRUM;
	servoDrum.write(SERVO_STOPPOWER);
	SMTickerTest.pause();
}

bool IRFreeWhileMoving() {
	// IRFired = 1 if DARK
	return !IRFired && currentTestState == MOVEDRUM;
}

bool IRNotFreeWhileMoving() {
	// IRFired = 1 if WHITE
	return IRFired && currentTestState == MOVEDRUM;
}

bool IRFreeState() {
	// IRFired = 0 if WHITE
	return IRFired && currentTestState == STOPDRUM;
}

State *ST0 = colorTestDrum.addState(&ST0_moveDrum);
State *ST1 = colorTestDrum.addState(&ST1_moveDrum);
State *ST2 = colorTestDrum.addState(&ST2_stopDrum);
void colorSMTest() {
	ST0->addTransition(&IRFreeWhileMoving, ST1);
	ST1->addTransition(&IRNotFreeWhileMoving, ST2);
	ST2->addTransition(&IRFreeState, ST0);
	SMTickerTest.start();
}
#endif