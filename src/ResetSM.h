#ifndef _RESETSM_H
#define _RESETSM_H

#define resetSMinterval 40
bool resetSMSignal = false;
void resetSMRun() {
	if (Serial.available()) {
		char data = Serial.read();
		Serial.print("SIGNAL : ");
		Serial.print(data);
		if (data == 'R') {
			resetSMSignal = true;
			Serial.print(" - ");
			Serial.println(resetSMSignal);
			SMTicker.resume();
		}
		if (data == 'S') {
			Serial.print(" - Current SM Signal: ");
			Serial.println(resetSMSignal);
		}
	}
}

Ticker resetSMTicker(resetSMRun, resetSMinterval, 0, MILLIS);

#endif