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

MENU(eepromMenu, EEPROMCONFIG_MSG, doNothing, noEvent, noStyle,
	 OP(CURRENTTABLE_MSG, readColorTable, enterEvent),
	 OP(LOADBW_MSG, loadBW, enterEvent),
	 OP(LOADCOLORTABLE_MSG, loadCT, enterEvent),
	 OP(FACTORYCOLORTABLE_MSG, factoryCT, enterEvent), EXIT(BACK_MSG));

#endif