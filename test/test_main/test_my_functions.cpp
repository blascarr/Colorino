#include <unity.h>

#define RGB_SIZE 4 // array index counter limit
#define SIZENAME 10
#define SIZECOLORS 8

typedef struct {
	float value[RGB_SIZE]; // Raw data from the sensor
} sensorData;

typedef struct {
	uint8_t
		value[RGB_SIZE]; // the evaluated colour data (RGB value 0-255 or other)
} colorData;
typedef struct {
	char name[SIZENAME]; // color name
	colorData rgb;		 // RGB value
} colorTable;

const colorTable _ct[SIZECOLORS] = {
	colorTable{"WHITE", {254, 255, 253}},  colorTable{"BLACK", {0, 0, 0}},
	colorTable{"YELLOW", {233, 207, 120}}, colorTable{"ORANGE", {201, 98, 72}},
	colorTable{"RED", {191, 67, 73}},	   colorTable{"GREEN", {154, 143, 67}},
	colorTable{"BLUE", {139, 139, 166}},   colorTable{"BROWN", {145, 73, 67}}};

colorData red = {{255, 0, 0}};
colorData green = {{0, 255, 0}};
colorData blue = {{0, 0, 255}};

uint8_t checkColor(colorData *rgb) {
	int32_t d;
	uint32_t v, minV = 999999L;
	uint8_t minI;

	for (uint8_t i = 0; i < SIZECOLORS; i++) {
		v = 0;
		for (uint8_t j = 0; j < RGB_SIZE; j++) {
			d = _ct[i].rgb.value[j] - rgb->value[j];
			v += (d * d);
		}
		if (v < minV) {
			minV = v;
			minI = i;
		}
		if (v == 0)
			break; // perfect match, no need to search more
	}
	return (minI);
}

void test_colortable() {
	const uint8_t expectedIndexForRed = 4;
	uint8_t result = checkColor(&red);
	TEST_ASSERT_EQUAL(expectedIndexForRed, result);
}

void test_function_2() { TEST_ASSERT_TRUE(true); }