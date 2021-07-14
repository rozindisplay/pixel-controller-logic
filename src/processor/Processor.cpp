#include "Processor.h"
#include "Wire.h"
#include <controller/MotorController.h>
#include <confg/Config.h>
#include <utils/StreamUtils.h>

void Processor::onHome(char opcode) {
    PIXLE_CONTROLLER.home();
}

void Processor::onSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4) {
    MotorController* motorController = NULL;
    
    motorController = PIXLE_CONTROLLER.getMotorController(1);
    motorController->setUpperLimit(limitP1.upper);
    motorController->setLowerLimit(limitP1.lower);

    motorController = PIXLE_CONTROLLER.getMotorController(2);
    motorController->setUpperLimit(limitP2.upper);
    motorController->setLowerLimit(limitP2.lower);

    motorController = PIXLE_CONTROLLER.getMotorController(3);
    motorController->setUpperLimit(limitP3.upper);
    motorController->setLowerLimit(limitP3.lower);

    motorController = PIXLE_CONTROLLER.getMotorController(4);
    motorController->setUpperLimit(limitP4.upper);
    motorController->setLowerLimit(limitP4.lower);

    PIXLE_CONTROLLER.home();
}

void Processor::onSetLimit(char opcode, char pixle, const PixelClientLimit& limit) {
    MotorController* motorController = PIXLE_CONTROLLER.getMotorController(pixle);
    motorController->setUpperLimit(limit.upper);
    motorController->setLowerLimit(limit.lower);
}

void Processor::onSetSteps(char opcode, char pixle, int steps) {
    MotorController* motorController = PIXLE_CONTROLLER.getMotorController(pixle);
    motorController->setSteps(steps);
}

void Processor::onAddSteps(char opcode, char pixle, int steps) {
    MotorController* motorController = PIXLE_CONTROLLER.getMotorController(pixle);
    motorController->addSteps(steps);
}

void Processor::onSetAngle(char opcode, char pixle, double angle) {
    MotorController* motorController = PIXLE_CONTROLLER.getMotorController(pixle);
    motorController->setAngle(angle);
}

void Processor::onAddAngle(char opcode, char pixle, double angle) {
    MotorController* motorController = PIXLE_CONTROLLER.getMotorController(pixle);
    motorController->addAngle(angle);
}
