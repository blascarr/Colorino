#ifndef _TCS3200CONFIGURATIONMENU_H
#define _TCS3200CONFIGURATIONMENU_H

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

result saveConfigInEEPROM(eventMask e, navNode &nav, prompt &item) {
	return proceed;
}

TOGGLE(ledState, LEDToggle, LED_MSG, doNothing, noEvent, noStyle,
	   VALUE(ON_MSG, HIGH, ledEvent, enterEvent),
	   VALUE(OFF_MSG, LOW, ledEvent, enterEvent));

TOGGLE(ledToReadState, LEDToReadToggle, LEDREAD_MSG, doNothing, noEvent,
	   noStyle, VALUE(OFF_MSG, 0, LEDToReadEvent, enterEvent),
	   VALUE(ONREAD_MSG, 1, LEDToReadEvent, enterEvent),
	   VALUE(ON_MSG, 2, LEDToReadEvent, enterEvent));

TOGGLE(freq, frequencyToggle, SETFREQ_MSG, doNothing, noEvent, noStyle,
	   VALUE(HIGH_MSG, TCS3200_FREQ_HI, setFrequency, enterEvent),
	   VALUE(MID_MSG, TCS3200_FREQ_MID, setFrequency, enterEvent),
	   VALUE(LOW_MSG, TCS3200_FREQ_LO, setFrequency, enterEvent),
	   VALUE(OFF_MSG, TCS3200_FREQ_OFF, setFrequency, enterEvent));

TOGGLE(rgbState, RGBToggle, RGBMODE_MSG, doNothing, noEvent, noStyle,
	   VALUE(RGB_MSG, HIGH, rgbMode, enterEvent),
	   VALUE(RAW_MSG, LOW, rgbMode, enterEvent));

TOGGLE(IR_INPUT_PULLUP, IRInputToggle, IR_INPUTLOGIC_MSG, doNothing, noEvent,
	   noStyle, VALUE(ON_MSG, HIGH, doNothing, enterEvent),
	   VALUE(OFF_MSG, LOW, doNothing, enterEvent));

MENU(configurationMenu, SENSORCONFIG_MSG, doNothing, noEvent, noStyle,
	 SUBMENU(LEDToggle),
	 FIELD(refreshTime, REFRESHTIME_MSG, VOID_MSG, 0, 1000, 100, 10,
		   setRefreshTime, enterEvent, wrapStyle),
	 FIELD(samples, SAMPLES_MSG, VOID_MSG, 0, 500, 50, 10, setSamples,
		   enterEvent, wrapStyle),
	 SUBMENU(RGBToggle), OP(REALATIVECOLOR_MSG, readRelativeColor, enterEvent),
	 SUBMENU(LEDToReadToggle), SUBMENU(IRInputToggle), SUBMENU(frequencyToggle),
	 OP(GETFREQUENCY_MSG, getFrequency, enterEvent),
	 OP(SAVE_CONFIG_MSG, saveConfigInEEPROM, enterEvent), EXIT(BACK_MSG));

#endif