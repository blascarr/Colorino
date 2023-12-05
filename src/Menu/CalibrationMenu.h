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
	Serial.println(manualColorCal);
	Serial.print(" - Calibrate Color: ");
	Serial.println(colorNames[manualColorCal]);
	return proceed;
}

#endif