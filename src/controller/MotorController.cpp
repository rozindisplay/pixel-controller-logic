#include "MotorController.h"
#include <confg/Config.h>

MotorController::MotorController(StepperMotor* stepper): stepper(stepper) {
	// init controller
}

int MotorController::getSteps() {
	return this->targetPosition;
}

int MotorController::getCurrentSteps() {
	return this->currentPosition;
}

void MotorController::setLowerLimit(int lower) {
	lowerLimit = lower;
}

int MotorController::getLowerLimit() {
	return lowerLimit;
}

void MotorController::setUpperLimit(int upper) {
	int centerDelta = upper - upperLimit;
	upperLimit = upper;

	this->currentPosition += centerDelta;
	this->targetPosition += centerDelta;
}

int MotorController::getUpperLimit() {
	return upperLimit;
}

void MotorController::setSteps(int position) {
	if(position>upperLimit || position<lowerLimit) {
		// Error. Position set out of boundaries
		return;
	}

	state = MOTOR_CONTROLLER_STATE_MOVE;

	targetPosition = position;
	int steps = targetPosition - currentPosition;

	stepper->setSpeed(StepperMotor::MAX_RPM);
	stepper->move(steps);
}

void MotorController::addSteps(int steps) {
	setSteps(targetPosition + steps);
}

double MotorController::getAngle() {
	// target steps * (360 deg / revolution steps ) = target deg
	return this->targetPosition * (360.0 / STEPS_PER_REVOLUTION);
}

double MotorController::getCurrentAngle() {
	// current steps * (360 deg / revolution steps ) = current deg
	return this->currentPosition * (360.0 / STEPS_PER_REVOLUTION);
}

void MotorController::setAngle(double degrees) {
	// value deg * (revolution steps / 360 deg) = value steps
	double steps = degrees * (STEPS_PER_REVOLUTION / 360.0);
	setSteps((int)round(steps));
}

void MotorController::addAngle(double degrees) {
	int stepsToAdd = degrees * (STEPS_PER_REVOLUTION / 360.0);
	addSteps(stepsToAdd);
}

bool MotorController::_home() {
	stepper->stop();
	stepper->setSpeed(StepperMotor::MIN_RPM);
	stepper->move(STEPS_PER_REVOLUTION);
	delay(1);

	// search for limit switch
	while(!LIMMIT_SWITCH.isTriggered()) {
		if(!stepper->isMoving()) {
			return false;
		}
		stepper->run();
		delay(1);
	}

	// stop the stepper and prepare to move back to the zero position
	stepper->stop();
	stepper->setSpeed(StepperMotor::MIN_RPM);
	stepper->move(-STEPS_PER_REVOLUTION);
	delay(500);

	// find the upper limit position
	while(LIMMIT_SWITCH.isTriggered()) {
		if(!stepper->isMoving()) {
			return false;
		}
		stepper->run();
		delay(1);
	}

	// uppper limit position found
	targetPosition = upperLimit;
	currentPosition = upperLimit;
	
	stepper->stop();
	
	// move to zero
	setSteps(0);
	while(MOTOR_CONTROLLER_STATE_MOVE == state) {
		run();
		delay(1);
	}

	return MOTOR_CONTROLLER_STATE_IDLE==state;
}

void MotorController::run() {
	switch (this->state) {
	case MOTOR_CONTROLLER_STATE_IDLE:
		this->runIdel();
		break;
	case MOTOR_CONTROLLER_STATE_MOVE:
		this->runMove();
		break;
	}
}

void MotorController::runIdel() {
	// nop
}

void MotorController::runMove() {

	int remainingBefore = stepper->getRemainingSteps();
	stepper->run();
	int remainingAfter = stepper->getRemainingSteps();

	if (remainingBefore != remainingAfter) {
		int direction = stepper->getDirection();
		currentPosition = currentPosition + (direction * (remainingBefore - remainingAfter));
	}

	if (remainingAfter == 0) {
		if (currentPosition != targetPosition) {
			// TODO error
		}

		state = MOTOR_CONTROLLER_STATE_IDLE;
	}
}

void MotorController::checkBoundaries() {
	if(currentPosition>upperLimit || currentPosition<lowerLimit || LIMMIT_SWITCH.isTriggered()) {		
		// Error, motor moved out of bounds
		stepper->stop();
		return;
	}
}
