#ifndef PIXEL_CONTROLLER_CONTROLLER
#define PIXEL_CONTROLLER_CONTROLLER

#include <hardware/limit/LimitSwitch.h>
#include <hardware/stepper/StepperMotor.h>

// --== Idel: No operation is being performed ==-- //
#define MOTOR_CONTROLLER_STATE_IDLE            00

// --== Moving: The motor position is being updated ==-- //
#define MOTOR_CONTROLLER_STATE_MOVE            10

// --== Homing: Calibrating the motor's position ==-- //
#define MOTOR_CONTROLLER_STATE_HOME            20
// - looking for the limit switch
#define MOTOR_CONTROLLER_STATE_HOME_TO_LIMIT   21
// - backing off the limit switch
#define MOTOR_CONTROLLER_STATE_HOME_OFF_LIMIT  22

class AsyncCallback {
public:
	virtual void onComplete(bool) = 0;
};

class MotorController {
public:
	MotorController(StepperMotor*, LimitSwitch*);
	void run();
	
	void home(AsyncCallback*);
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
	bool isMoving();
private:

	void runIdel();
	void runMove();
	void runHome_toLimit();
	void runHome_offLimit();
	
	void checkBoundaries();

	StepperMotor *stepper;
	LimitSwitch *limit;

	AsyncCallback* callback;

	int currentPosition;
	int targetPosition;

	uint8_t state = MOTOR_CONTROLLER_STATE_IDLE;
	int lowerLimit;
	int upperLimit;
};

#endif