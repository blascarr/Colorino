result doStop(eventMask e, navNode &nav, prompt &item) { return proceed; }

result readColor(eventMask e, navNode &nav, prompt &item) {
	CSDebug.readColor();
	CSDebug.read();
	return proceed;
}

result nextDrumStep(eventMask e, navNode &nav, prompt &item) {
#ifdef _TCS3200CALIBRATIONSM_H
	currentTestState = MOVEDRUM;
	SMTickerTest.start();
#endif
	return proceed;
}

#if !CONTINUOUS_COLORSM
result resetSM(eventMask e, navNode &nav, prompt &item) {
	resetSMSignal = true;
	SMTicker.resume();
	return proceed;
}
#endif

#ifdef _TCS3200CALIBRATIONMENU_H
MENU(manualCalibrationMenu, MANUALCALIBRATION_MSG, doNothing, noEvent, noStyle,
	 FIELD(manualColorCal, COLOR_MSG, VOID_MSG, 0, 7, 1, 0, manualCalibrate,
		   enterEvent, noStyle),
	 OP(SAVECOLOR_MSG, SaveColor, enterEvent),
	 OP(NEXTDRUMSTEP_MSG, nextDrumStep, enterEvent),
	 OP(SAVECOLORTABLE_MSG, saveCT, enterEvent),
	 OP(MOVE_SERVO_MSG, moveToServoPositionsCalibrate, enterEvent),
	 FIELD(manualServoCal, POS_SERVO_MSG, VOID_MSG, 0, 180, 1, 0,
		   servoPositionsCalibrate, enterEvent, noStyle),
	 EXIT(BACK_MSG));

MENU(calibrationMenu, CALIBRATE_MSG, doNothing, noEvent, noStyle,
	 OP(DARKCALIBRATION_MSG, darkCal, enterEvent),
	 OP(WHITECALIBRATION_MSG, whiteCal, enterEvent),
	 OP(NEXTDRUMSTEP_MSG, nextDrumStep, enterEvent),
	 OP(CURRENTDARK_MSG, currentDarkCal, enterEvent),
	 OP(CURRENTWHITE_MSG, currentWhiteCal, enterEvent),
	 SUBMENU(manualCalibrationMenu),
	 FIELD(manualServoCal, POS_SERVO_MSG, VOID_MSG, 0, 180, 1, 0,
		   manualServoCalibrate, enterEvent, noStyle),
	 OP(GET_POS_SERVO_MSG, getPosServoCalibrate, enterEvent),
	 FIELD(uServoCal, set_uS_USERVO_MSG, VOID_MSG, 0, 2700, 10, 0,
		   uServoCalibrate, enterEvent, noStyle),
	 OP(get_uS_USERVO_MSG, getuServoCalibrate, enterEvent),
	 OP(NEURONACALIBRATION_MSG, doNothing, enterEvent), // Training in Neuron
	 EXIT(BACK_MSG));
#endif

MENU(mainMenu, MAINMENU_MSG, doNothing, noEvent, wrapStyle,
#if !CONTINUOUS_COLORSM
	 OP(RESETSM_MSG, resetSM, enterEvent),
#endif
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