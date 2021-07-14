#ifndef PIXEL_CONTROLLER_CONTROLLER
#define PIXEL_CONTROLLER_CONTROLLER

#include <hardware/limit/LimitSwitch.h>
#include <hardware/stepper/StepperMotor.h>
#include <looper/Loopable.h>

#define MOTOR_CONTROLLER_STATE_IDLE 1
#define MOTOR_CONTROLLER_STATE_MOVE 2

class MotorController: public Loopable {
public:
	MotorController(StepperMotor*);
	void run();
	bool _home();
	void setLowerLimit(int lower);
	int getLowerLimit();
	void setUpperLimit(int lower);
	int getUpperLimit();
	int getSteps();
	int getCurrentSteps();
	void setSteps(int steps);
	void addSteps(int steps);
	double getAngle();
	double getCurrentAngle();
	void setAngle(double degrees);
	void addAngle(double degrees);

private:

	void runIdel();
	void runMove();
	void checkBoundaries();

	StepperMotor *stepper;

	int currentPosition;
	int targetPosition;

	uint8_t state = MOTOR_CONTROLLER_STATE_IDLE;
	int lowerLimit;
	int upperLimit;
};

#endif