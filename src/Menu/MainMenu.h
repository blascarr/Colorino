result doStop(eventMask e, navNode &nav, prompt &item) { return proceed; }

result readColor(eventMask e, navNode &nav, prompt &item) {
	CSDebug.readColor();
	CSDebug.read();
	return proceed;
}

result nextDrumStep(eventMask e, navNode &nav, prompt &item) {
	currentTestState = MOVEDRUM;
	SMTickerTest.resume();
	return proceed;
}

#ifdef _TCS3200CALIBRATIONMENU_H
MENU(manualCalibrationMenu, "MANUAL CALIBRATION", doNothing, noEvent, noStyle,
	 FIELD(manualColorCal, "COLOR", "", 0, 7, 1, 0, manualCalibrate, enterEvent,
		   noStyle),
	 OP("SAVE COLOR", SaveColor, enterEvent),
	 OP("NEXT DRUM STEP", nextDrumStep, enterEvent),
	 OP("SAVE EEPROM COLOR TABLE", saveCT, enterEvent), EXIT("<Back"));

MENU(calibrationMenu, "CALIBRATE SENSOR", doNothing, noEvent, noStyle,
	 OP("DARK CALIBRATION", darkCal, enterEvent),
	 OP("WHITE CALIBRATION", whiteCal, enterEvent),
	 OP("NEXT DRUM STEP", nextDrumStep, enterEvent),
	 OP("CURRENT DARK VALUE CALIBRATED ", currentDarkCal, enterEvent),
	 OP("CURRENT WHITE VALUE CALIBRATED ", currentWhiteCal, enterEvent),
	 SUBMENU(manualCalibrationMenu),
	 OP("NEURONA CALIBRATION", doNothing, enterEvent) // Training in Neuron
	 ,
	 FIELD(manualServoCal, "SERVO VEL", "", 0, 180, 1, 0, manualServoCalibrate,
		   enterEvent, noStyle),
	 EXIT("<Back"));
#endif

MENU(mainMenu, "Main Menu", doNothing, noEvent, wrapStyle,
	 OP("READ COLOR", readColor, enterEvent),
	 OP("NEXT DRUM STEP", nextDrumStep, enterEvent)
#ifdef _TCS3200CALIBRATIONMENU_H
		 ,
	 SUBMENU(calibrationMenu)
#endif
#ifdef _TCS3200EEPROMMENU_H
		 ,
	 SUBMENU(eepromMenu)
#endif
#ifdef _TCS3200CONFIGURATIONMENU_H
		 ,
	 SUBMENU(configurationMenu)
#endif
);

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out); // the navigation root object