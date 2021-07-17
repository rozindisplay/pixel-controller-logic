#ifndef PIXEL_CONTROLLER_HARDWARE_STEPPER_MOTOR
#define PIXEL_CONTROLLER_HARDWARE_STEPPER_MOTOR

#include "Arduino.h"

#define STEPS_PER_REVOLUTION 2048
#define MIN_RPM 4
#define MAX_RPM 16

class StepperMotorPins {
public:
	const uint8_t pin1;		// blue
	const uint8_t pin2;		// pink
	const uint8_t pin3;		// yellow
	const uint8_t pin4;		// orange
	StepperMotorPins(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4): pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4){};
};

class StepperMotor {
public:
	

	StepperMotor(const StepperMotorPins& pins);
	void run();
	void stop();
	int getDirection();
	bool isMoving();
	int getRemainingSteps();
	void setSpeed(int rpm);
	void move(int steps);
private:
	const StepperMotorPins* const pins;
	int direction;
	int remainingSteps;
	int step;
	unsigned int delay;
	unsigned long lastStepTime;
};


#endif