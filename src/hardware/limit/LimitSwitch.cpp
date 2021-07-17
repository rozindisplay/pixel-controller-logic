#include <hardware/limit/LimitSwitch.h>

LimitSwitch::LimitSwitch(uint8_t pin): pin(pin) {
	pinMode(this->pin, INPUT_PULLUP);
};

bool LimitSwitch::isTriggered() {
	return digitalRead(this->pin) == LOW;
};

uint8_t LimitSwitch::getPin() {
	return this->pin;
};
