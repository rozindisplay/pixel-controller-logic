#include "CmdProcessor.h"
#include "Wire.h"
#include <controller/MotorController.h>
#include <confg/Config.h>
#include <utils/StreamUtils.h>

void CmdProcessor::onHome(unsigned char opcode) {
    homeProcessor.home();
}

void CmdProcessor::onSetLimitsAndHome(unsigned char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
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

void CmdProcessor::onSetLimit(unsigned char opcode, unsigned char pixel, const PixelClientLimit& limit) {
    MotorController* motorController = getMotorController(pixel);
    motorController->setUpperLimit(limit.upper);
    motorController->setLowerLimit(limit.lower);
}

void CmdProcessor::onSetSteps(unsigned char opcode, unsigned char pixel, int steps) {
    MotorController* motorController = getMotorController(pixel);
    motorController->setSteps(steps);
}

void CmdProcessor::onAddSteps(unsigned char opcode, unsigned char pixel, int steps) {
    MotorController* motorController = getMotorController(pixel);
    motorController->addSteps(steps);
}

void CmdProcessor::onSetAngle(unsigned char opcode, char unsigned pixel, double angle) {
    MotorController* motorController = getMotorController(pixel);
    motorController->setAngle(angle);
}

void CmdProcessor::onAddAngle(unsigned char opcode, unsigned char pixel, double angle) {
    MotorController* motorController = getMotorController(pixel);
    motorController->addAngle(angle);
}

void CmdProcessor::onSetRequestType(unsigned char opcode, unsigned char requestType) {
    // nop
}

void CmdProcessor::requestPing() {
    // nop
}

int CmdProcessor::requestError() {
    return ERR.reset();
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