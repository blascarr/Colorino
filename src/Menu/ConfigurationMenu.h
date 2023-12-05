#ifndef _TCS3200CONFIGURATIONMENU_H
#define _TCS3200CONFIGURATIONMENU_H

bool ledState = true;
int freq = TCS3200_FREQ_HI;

result setFrequency(eventMask e, navNode &nav, prompt &item) {
	CS.setFrequency(freq);
	return proceed;
}

result getFrequency(eventMask e, navNode &nav, prompt &item) {
	uint8_t freqLevel = CS.getFrequency();
	Serial.println();
	Serial.print("Frequency : ");
	Serial.print(freqLevel);
	Serial.print(freqStates[freqLevel]);
	return proceed;
}

result ledEvent(eventMask e, navNode &nav, prompt &item) {
	CS.LEDON(ledState);
	return proceed;
}

result readRelativeColor(eventMask e, navNode &nav, prompt &item) {
	CSDebug.readColor();
	CSDebug.relativeColor();
	return proceed;
}

result rgbMode(eventMask e, navNode &nav, prompt &item) {
	CS.setRGBMode(rgbState);
	return proceed;
}

result setRefreshTime(eventMask e, navNode &nav, prompt &item) {
	CS.setRefreshTime(refreshTime);
	return proceed;
}

result setSamples(eventMask e, navNode &nav, prompt &item) {
	CS.nSamples(samples);
	return proceed;
}

result LEDToReadEvent(eventMask e, navNode &nav, prompt &item) {
	CS.setLEDtoRead(ledToReadState);
	return proceed;
}

TOGGLE(ledState, LEDToggle, "LED: ", doNothing, noEvent, noStyle,
	   VALUE("ON", HIGH, ledEvent, enterEvent),
	   VALUE("OFF", LOW, ledEvent, enterEvent));

TOGGLE(ledToReadState, LEDToReadToggle, "LED TO READ: ", doNothing, noEvent,
	   noStyle, VALUE("OFF", 0, LEDToReadEvent, enterEvent),
	   VALUE("ONREAD", 1, LEDToReadEvent, enterEvent),
	   VALUE("ON", 2, LEDToReadEvent, enterEvent));

TOGGLE(freq, frequencyToggle, "SET FREQ: ", doNothing, noEvent, noStyle,
	   VALUE("HIGH", TCS3200_FREQ_HI, setFrequency, enterEvent),
	   VALUE("MID", TCS3200_FREQ_MID, setFrequency, enterEvent),
	   VALUE("LOW", TCS3200_FREQ_LO, setFrequency, enterEvent),
	   VALUE("LOW", TCS3200_FREQ_OFF, setFrequency, enterEvent));

TOGGLE(rgbState, RGBToggle, "RGB MODE: ", doNothing, noEvent, noStyle,
	   VALUE("RGB", HIGH, rgbMode, enterEvent),
	   VALUE("RAW", LOW, rgbMode, enterEvent));

MENU(configurationMenu, "SENSOR CONFIGURATION", doNothing, noEvent, noStyle,
	 SUBMENU(LEDToggle),
	 FIELD(refreshTime, "Refresh Time", "", 0, 1000, 100, 10, setRefreshTime,
		   enterEvent, wrapStyle),
	 FIELD(samples, "Samples", "", 0, 500, 50, 10, setSamples, enterEvent,
		   wrapStyle),
	 SUBMENU(RGBToggle), OP("RELATIVE COLOR", readRelativeColor, enterEvent),
	 SUBMENU(LEDToReadToggle), SUBMENU(frequencyToggle),
	 OP("GET FREQUENCY", getFrequency, enterEvent), EXIT("<Back"));

#endif