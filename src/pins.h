#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)

#define TCS3200_S0 6
#define TCS3200_S1 7
#define TCS3200_S2 2
#define TCS3200_S3 3
#define TCS3200_OUT 5
#define TCS3200_LED 4

#define IR_PIN 8
#define DRUMSERVO_PIN 9
#define SELECTORSERVO_PIN 10
#define IRinterval 10

#define LCD_SUPPORT true
#define LCD_I2C_DIR 0x3f
#define LCD_I2C_COLUMNS 16
#define LCD_I2C_ROWS 2

#ifndef LCD_I2C_COLUMNS
#define LCD_I2C_COLUMNS 16
#endif

#ifndef LCD_I2C_ROWS
#define LCD_I2C_ROWS 2
#endif

#ifdef LCD_SUPPORT
#include "Menu/LCD_MSG_Definition.h"
// Encoder /////////////////////////////////////
#define encA 11
#define encB 12
// this encoder has a button here
#define encBtn 13
#define ENC_SENSIVITY 4
#else
#include "Menu/MSG_Definition.h"
#endif

#endif

#ifdef ESP8266

#define TCS3200_S0 6
#define TCS3200_S1 7
#define TCS3200_S2 2
#define TCS3200_S3 3
#define TCS3200_OUT 5
#define TCS3200_LED 4

#define IR_PIN 8
#define DRUMSERVO_PIN 9
#define SELECTORSERVO_PIN 10
#define IRinterval 10

#define LCD_SUPPORT true
#define LCD_I2C_DIR 0x3f
#define LCD_I2C_COLUMNS 16
#define LCD_I2C_ROWS 2

#ifndef LCD_I2C_COLUMNS
#define LCD_I2C_COLUMNS 16
#endif

#ifndef LCD_I2C_ROWS
#define LCD_I2C_ROWS 2
#endif
#ifdef LCD_SUPPORT
// Encoder /////////////////////////////////////
#define encA 11
#define encB 12
// this encoder has a button here
#define encBtn 13
#define ENC_SENSIVITY 4
#endif

#endif
