#ifndef _TCS3200EEPROMMENU_H
#define _TCS3200EEPROMMENU_H

result loadBW(eventMask e, navNode &nav, prompt &item) {
	CSDebug.loadBW();
	return proceed;
}

result loadCT(eventMask e, navNode &nav, prompt &item) {
	CSDebug.loadCT();
	return proceed;
}

result factoryCT(eventMask e, navNode &nav, prompt &item) {
	CS.setToFactoryCT();
	return proceed;
}

result readColorTable(eventMask e, navNode &nav, prompt &item) {
	CSDebug.readCT();
	return proceed;
}

MENU(eepromMenu, "EEPROM CONFIGURATION", doNothing, noEvent, noStyle,
	 OP("CURRENT COLOR TABLE", readColorTable, enterEvent),
	 OP("LOAD BW EEPROM", loadBW, enterEvent),
	 OP("LOAD COLOR TABLE", loadCT, enterEvent),
	 OP("FACTORY COLOR TABLE", factoryCT, enterEvent), EXIT("<Back"));

#endif