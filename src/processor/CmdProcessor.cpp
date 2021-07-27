#include "CmdProcessor.h"
#include "Wire.h"
#include <controller/MotorController.h>
#include <confg/Config.h>

void CmdProcessor::onHome() {
    homeProcessor.home();
}

void CmdProcessor::onHome(unsigned char pixel) {
    getMotorController(pixel)->home();
}

void CmdProcessor::onSetLimit(unsigned char pixel, const PixLimit& limit) {
    MotorController* motorController = getMotorController(pixel);
    motorController->setUpperLimit(limit.upper);
    motorController->setLowerLimit(limit.lower);
}

void CmdProcessor::onSetSteps(unsigned char pixel, int steps) {
    MotorController* motorController = getMotorController(pixel);
    motorController->setSteps(steps);
}

void CmdProcessor::onAddSteps(unsigned char pixel, int steps) {
    MotorController* motorController = getMotorController(pixel);
    motorController->addSteps(steps);
}

void CmdProcessor::onSetAngle(char unsigned pixel, double angle) {
    MotorController* motorController = getMotorController(pixel);
    motorController->setAngle(angle);
}

void CmdProcessor::onAddAngle(unsigned char pixel, double angle) {
    MotorController* motorController = getMotorController(pixel);
    motorController->addAngle(angle);
}

void CmdProcessor::requestPing() {
    // nop
}

unsigned char CmdProcessor::requestPixels() {
    return PIXEL_COUNT;
}

int CmdProcessor::requestErrorCode() {
    return ERR.getCode();
}

unsigned char CmdProcessor::requestMoving() {
    int count = 0;
    
    for(int i=0; i<PIXEL_COUNT; i++) {
        if(getMotorController(i)->isMoving()) {
            count++;
        }
    }

    return count;
}

bool CmdProcessor::requestIsMoving(unsigned char pixel) {
    return getMotorController(pixel)->isMoving();
}

int CmdProcessor::requestTargetSteps(unsigned char pixel) {
    return getMotorController(pixel)->getSteps();
}

int CmdProcessor::requestSteps(unsigned char pixel) {
    return getMotorController(pixel)->getCurrentSteps();
}

double CmdProcessor::requestTargetAngle(unsigned char pixel) {
    return getMotorController(pixel)->getAngle();
}

double CmdProcessor::requestAngle(unsigned char pixel) {
    return getMotorController(pixel)->getCurrentAngle();
}

const PixLimit CmdProcessor::requestLimit(unsigned char pixel) {
    MotorController* motorController = getMotorController(pixel);
    int lowerLimit = motorController->getLowerLimit();
    int upperLimit = motorController->getUpperLimit();

    return PixLimit(lowerLimit, upperLimit);
}

const PixStatus CmdProcessor::requestStatus(unsigned char pixle) {
    MotorController* motorController = getMotorController(pixle);

    bool moving = motorController->isMoving();
    int target = motorController->getSteps();
    int steps = motorController->getCurrentSteps();
    double angle = motorController->getCurrentAngle();
    int lowerLimit = motorController->getLowerLimit();
    int upperLimit = motorController->getUpperLimit();
    
    return PixStatus(moving, target, steps, angle, PixLimit(lowerLimit, upperLimit));
}

void CmdProcessor::onClearErrorCode() {
    ERR.reset();
}

void HomeCmdProcessor::home() {
    if(pixel!=-1) {
        // error: the home process is already running
        return;
    }
    pixel = 0;
    runNext();
}

void HomeCmdProcessor::onComplete(bool success) {
    if(!success) {
        // error: process failed
        pixel = -1;
        return;
    }

    // increment pixel index and check if there are more to pixels to process
    if(PIXEL_COUNT == ++pixel) {
        // Done. we've recalibrated all pixels
        pixel = -1;
        return;
    }

    // run the next one
    runNext();
}

void HomeCmdProcessor::runNext() {
    if(pixel>=PIXEL_COUNT) {
        // error: index out of bounds
        pixel = -1;
        return;
    }

    // run the home process (asyc)
    getMotorController(pixel)->home(this);
}
