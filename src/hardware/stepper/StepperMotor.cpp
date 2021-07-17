#include <hardware/stepper/StepperMotor.h>

StepperMotor::StepperMotor(const StepperMotorPins& pins): pins(&pins) {
	this->direction = 0;
	this->remainingSteps = 0;
	this->delay = 0;
	this->lastStepTime = 0;
	this->step = 0;

	pinMode(pins.pin1, OUTPUT);
	pinMode(pins.pin2, OUTPUT);
	pinMode(pins.pin3, OUTPUT);
	pinMode(pins.pin4, OUTPUT);
	stop();
}
;

void StepperMotor::stop() {
	this->remainingSteps = 0;
	
	digitalWrite(pins->pin1, LOW);
	digitalWrite(pins->pin2, LOW);
	digitalWrite(pins->pin3, LOW);
	digitalWrite(pins->pin4, LOW);
}
;

int StepperMotor::getDirection() {
	return this->direction;
}
;

bool StepperMotor::isMoving() {
	return this->remainingSteps > 0;
}
;

int StepperMotor::getRemainingSteps() {
	return this->remainingSteps;
}
;

void StepperMotor::setSpeed(int rpm) {
	this->delay = 60L * 1000L * 1000L / STEPS_PER_REVOLUTION / rpm;
}
;

void StepperMotor::move(int steps) {
	this->remainingSteps = abs(steps);

	if (steps == 0) {
		return;
	}

	this->direction = steps > 0 ? 1 : -1;
}
;

void StepperMotor::run() {

	if (remainingSteps == 0) {
		return;
	}

	unsigned long now = micros();
	if (now-lastStepTime < delay) {
		return;
	}

	remainingSteps--;
	lastStepTime = now;
	step = step + direction;

	if (step > 3) {
		step = 0;
	} else if (step < 0) {
		step = 3;
	}

	// positive directions are counter-clockwise
	switch (this->step) {
	case 0: // 0110
		digitalWrite(pins->pin1, LOW);
		digitalWrite(pins->pin2, HIGH);
		digitalWrite(pins->pin3, HIGH);
		digitalWrite(pins->pin4, LOW);
		break;
	case 1: //  0011
		digitalWrite(pins->pin1, LOW);
		digitalWrite(pins->pin2, LOW);
		digitalWrite(pins->pin3, HIGH);
		digitalWrite(pins->pin4, HIGH);
		break;
	case 2: // 1001
		digitalWrite(pins->pin1, HIGH);
		digitalWrite(pins->pin2, LOW);
		digitalWrite(pins->pin3, LOW);
		digitalWrite(pins->pin4, HIGH);
		break;
	case 3: // 1100
		digitalWrite(pins->pin1, HIGH);
		digitalWrite(pins->pin2, HIGH);
		digitalWrite(pins->pin3, LOW);
		digitalWrite(pins->pin4, LOW);
		break;
	}

	// once the position is found, turn off the stepper
	if(remainingSteps==0) {
		stop();
	}
}
;
