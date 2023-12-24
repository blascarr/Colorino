#ifndef _TCS3200CALIBRATIONMENU_H
#define _TCS3200CALIBRATIONMENU_H

result saveCT(eventMask e, navNode &nav, prompt &item) {
	CSDebug.saveCT();
	return proceed;
}

result SaveColor(eventMask e, navNode &nav, prompt &item) {
	colorData colorcl = CSDebug.readRGB();
	CS._ct[manualColorCal].rgb = colorcl;
	return proceed;
}

result darkCal(eventMask e, navNode &nav, prompt &item) {
	CSDebug.setDarkCal();
	CS.saveBW();
	return proceed;
}

result whiteCal(eventMask e, navNode &nav, prompt &item) {
	CSDebug.setWhiteCal();
	CS.saveBW();
	return proceed;
}

result currentDarkCal(eventMask e, navNode &nav, prompt &item) {
	CSDebug.getDarkCal();
	return proceed;
}

result currentWhiteCal(eventMask e, navNode &nav, prompt &item) {
	CSDebug.getWhiteCal();
	return proceed;
}

result manualCalibrate(eventMask e, navNode &nav, prompt &item) {
	Serial.print(manualColorCal);
	Serial.print(CALIBRATECOLOR_MSG);
	Serial.println(colorNames[manualColorCal]);
	return proceed;
}

result manualServoCalibrate(eventMask e, navNode &nav, prompt &item) {
	Serial.print("Servo: ");
	Serial.println(manualServoCal);
	servoSelector.write(manualServoCal + selectorOffset);
	return proceed;
}

result uServoCalibrate(eventMask e, navNode &nav, prompt &item) {
	Serial.print("Servo: ");
	Serial.println(uServoCal);
	servoSelector.writeMicroseconds(uServoCal);
	return proceed;
}

result getuServoCalibrate(eventMask e, navNode &nav, prompt &item) {
	Serial.print("Servo: ");
	Serial.println(servoSelector.readMicroseconds());
	return proceed;
}

result servoPositionsCalibrate(eventMask e, navNode &nav, prompt &item) {
	Serial.print("Pos[ ");
	Serial.print(manualColorCal);
	Serial.print(" ] = ");
	Serial.println(manualServoCal);
	servoSelector.write(manualServoCal);
	positions[manualColorCal] = manualServoCal;
	return proceed;
}

result moveToServoPositionsCalibrate(eventMask e, navNode &nav, prompt &item) {
	Serial.print("Pos[ ");
	Serial.print(manualColorCal);
	Serial.print(" ] = ");
	Serial.println(positions[manualColorCal]);
	servoSelector.write(positions[manualColorCal]);
	return proceed;
}

result getPosServoCalibrate(eventMask e, navNode &nav, prompt &item) {
	for (int pos = 0; pos < SIZECOLORS; pos++) {
		Serial.print("Pos[ ");
		Serial.print(pos);
		Serial.print(" ] = ");
		Serial.println(positions[pos]);
	}
	return proceed;
}
#endif