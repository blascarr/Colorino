// EEPROM.h mock
#ifndef EEPROM_H
#define EEPROM_H

class EEPROMClass {
  public:
	void begin() {}
	int read(int address) { return 0; }
	void write(int address, int value) {}
	void end() {}
};

extern EEPROMClass EEPROM;

#endif