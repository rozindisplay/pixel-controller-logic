#ifndef PIXEL_CONTROLLER_HARDWARE_LIMIT_SWITCH
#define PIXEL_CONTROLLER_HARDWARE_LIMIT_SWITCH

#include "Arduino.h"

class LimitSwitch {
public:
	LimitSwitch(uint8_t);
	bool isTriggered();
	uint8_t getPin();
private:
	uint8_t pin;
};

#endif
