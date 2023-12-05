#if defined(ESP8266)
#include <streamFlow.h>
#endif

#include <menu.h>
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>
#define MAX_DEPTH 5

using namespace Menu;

// ---  Define INPUTS ---
serialIn serial(Serial);

MENU_OUTPUTS(out, MAX_DEPTH, SERIAL_OUT(Serial), NONE);
