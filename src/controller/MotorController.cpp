#include "MotorController.h"
#include <err/Errors.h>

MotorController::MotorController(StepperMotor *stepper, LimitSwitch *limit): stepper(stepper), limit(limit) {
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
	if(MOTOR_CONTROLLER_STATE_HOME == state) {
		// error: cannot start the move process while in the home process
		ERR.error(ERR_HOMING_IN_PROGRESS);
		return;
	}
	
	if(position>upperLimit || position<lowerLimit) {
		// error. Position set out of boundaries
		ERR.error(ERR_SET_OUT_OF_BOUNDS);
		return;
	}

	state = MOTOR_CONTROLLER_STATE_MOVE;

	targetPosition = position;
	int steps = targetPosition - currentPosition;

	stepper->setSpeed(MAX_RPM);
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

void MotorController::home(AsyncCallback *callback) {
	int homeId = MOTOR_CONTROLLER_STATE_HOME/10;
	int stateId = state/10;
	if(homeId == stateId) {
		// error: cannot start the home process while in the home process
		ERR.error(ERR_HOMING_IN_PROGRESS);
		callback->onComplete(false);
		return;
	}
	
	state = MOTOR_CONTROLLER_STATE_HOME_TO_LIMIT;

	stepper->stop();
	stepper->setSpeed(MIN_RPM);
	stepper->move(STEPS_PER_REVOLUTION);
	
	this->callback = callback;
}

void MotorController::run() {
	switch (this->state) {
	case MOTOR_CONTROLLER_STATE_IDLE:
		this->runIdel();
		break;
	case MOTOR_CONTROLLER_STATE_MOVE:
		this->runMove();
		break;
	case MOTOR_CONTROLLER_STATE_HOME_TO_LIMIT:
		this->runHome_toLimit();
		break;
	case MOTOR_CONTROLLER_STATE_HOME_OFF_LIMIT:
		this->runHome_offLimit();
		break;
	default:
		// error: unknown state
		ERR.error(ERR_CONTROLLER_STATE_UNKNOWN);
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

void MotorController::runHome_toLimit() {
	if(!limit->isTriggered()) {
		// moving to find limit

		if(stepper->isMoving()) {
			// keep running the stepper
			stepper->run();
		} else {
			// error: we've failed to find the limit switch. the stepper moved the given number of steps
			ERR.error(ERR_LIMIT_NOT_FOUND);
			state = MOTOR_CONTROLLER_STATE_IDLE;
			callback->onComplete(false);
		}
	} else {
		// limit switch found
		// stop the stepper and prepare to move back off of the limit switch
		stepper->stop();
		stepper->setSpeed(MIN_RPM);
		stepper->move(-STEPS_PER_REVOLUTION);
		state = MOTOR_CONTROLLER_STATE_HOME_OFF_LIMIT;
	}
}

void MotorController::runHome_offLimit() {
	if(limit->isTriggered()) {
		// moving off of the limit switch

		if(stepper->isMoving()) {
			// keep running the stepper
			stepper->run();
		} else {
			// error: we've failed to move off the limit switch. the stepper moved through the defined number of steps
			ERR.error(ERR_LIMIT_OFF_NOT_FOUND);
			state = MOTOR_CONTROLLER_STATE_IDLE;
			callback->onComplete(false);
		}
	} else {
		// we're off of the limit switch
		stepper->stop();

		// set position
		targetPosition = upperLimit;
		currentPosition = upperLimit;

		// calibration is done. Move to the zero position and notify the callback
		state = MOTOR_CONTROLLER_STATE_IDLE;
		setSteps(0);
		callback->onComplete(true);
	}
}

void MotorController::checkBoundaries() {
	if(currentPosition>upperLimit || currentPosition<lowerLimit || limit->isTriggered()) {		
		// Error, motor moved out of bounds
		ERR.error(ERR_MOVED_OUT_OF_BOUNDS);
		stepper->stop();
		return;
	}
}
