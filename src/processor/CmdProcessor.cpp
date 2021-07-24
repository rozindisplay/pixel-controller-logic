#include "CmdProcessor.h"
#include "Wire.h"
#include <controller/MotorController.h>
#include <confg/Config.h>

void CmdProcessor::onInit(const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4) {
    MotorController* motorController = NULL;
    
    motorController = getMotorController(1);
    motorController->setUpperLimit(limitP1.upper);
    motorController->setLowerLimit(limitP1.lower);

    motorController = getMotorController(2);
    motorController->setUpperLimit(limitP2.upper);
    motorController->setLowerLimit(limitP2.lower);

    motorController = getMotorController(3);
    motorController->setUpperLimit(limitP3.upper);
    motorController->setLowerLimit(limitP3.lower);

    motorController = getMotorController(4);
    motorController->setUpperLimit(limitP4.upper);
    motorController->setLowerLimit(limitP4.lower);

    homeProcessor.home();
}

void CmdProcessor::onHome() {
    homeProcessor.home();
}

void CmdProcessor::onClearErrorCode() {
    ERR.reset();
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

int CmdProcessor::requestErrorCode() {
    return ERR.getCode();
}

unsigned char CmdProcessor::requestMovingCount() {
    int count = 0;
    
    for(int i=0; i<PIXEL_COUNT; i++) {
        if(getMotorController(i)->isMoving()) {
            count++;
        }
    }

    return count;
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
