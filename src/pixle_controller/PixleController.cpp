#include "PixleController.h"
#include <confg/Config.h>

void PixleController::run() {
    switch (state) {
    case PIXLE_CONTROLLER_STATE_IDLE:
        runIdle();
        break;
    case PIXLE_CONTROLLER_STATE_HOME:
        runHome();
        break;
    default:
        break;
    }
}

void PixleController::home() {
    state = PIXLE_CONTROLLER_STATE_HOME;
}

void PixleController::runIdle() {
    CONTROLLER_1.run();
}

MotorController* PixleController::getMotorController(char index) {
    switch (index) {
    case 1:
        return &CONTROLLER_1;
    case 2:
        return &CONTROLLER_2;
    case 3:
        return &CONTROLLER_3;
    case 4:
        return &CONTROLLER_4;
    default:
        return NULL;
    }
}

void PixleController::runHome() {
    CONTROLLER_1._home();
    this->state = PIXLE_CONTROLLER_STATE_IDLE;
}
