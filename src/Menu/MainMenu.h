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
MENU(manualCalibrationMenu, MANUALCALIBRATION_MSG, doNothing, noEvent, noStyle,
	 FIELD(manualColorCal, COLOR_MSG, VOID_MSG, 0, 7, 1, 0, manualCalibrate,
		   enterEvent, noStyle),
	 OP(SAVECOLOR_MSG, SaveColor, enterEvent),
	 OP(NEXTDRUMSTEP_MSG, nextDrumStep, enterEvent),
	 OP(SAVECOLORTABLE_MSG, saveCT, enterEvent), EXIT(BACK_MSG));

MENU(calibrationMenu, CALIBRATE_MSG, doNothing, noEvent, noStyle,
	 OP(DARKCALIBRATION_MSG, darkCal, enterEvent),
	 OP(WHITECALIBRATION_MSG, whiteCal, enterEvent),
	 OP(NEXTDRUMSTEP_MSG, nextDrumStep, enterEvent),
	 OP(CURRENTDARK_MSG, currentDarkCal, enterEvent),
	 OP(CURRENTWHITE_MSG, currentWhiteCal, enterEvent),
	 SUBMENU(manualCalibrationMenu),
	 OP(NEURONACALIBRATION_MSG, doNothing, enterEvent) // Training in Neuron
	 ,
	 FIELD(manualServoCal, SERVOVEL_MSG, VOID_MSG, 0, 180, 1, 0,
		   manualServoCalibrate, enterEvent, noStyle),
	 EXIT(BACK_MSG));
#endif

MENU(mainMenu, MAINMENU_MSG, doNothing, noEvent, wrapStyle,
	 OP(READCOLOR_MSG, readColor, enterEvent),
	 OP(NEXTDRUMSTEP_MSG, nextDrumStep, enterEvent)
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