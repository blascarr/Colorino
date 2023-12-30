#include "ArduinoFake.h"
#include <cstdlib>
// #include "mocks/EEPROM.h"
#include "mocks/Ticker.h"

#include <unity.h>
using namespace fakeit;

void test_colortable();
void test_function_2();

void setUp() { ArduinoFakeReset(); }

void tearDown() {}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test_colortable);
	RUN_TEST(test_function_2);
	UNITY_END();
}