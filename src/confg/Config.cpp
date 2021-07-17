#include "Wire.h"
#include <confg/Config.h>

LimitSwitch LIMMIT_SWITCH = LimitSwitch(LIMMIT_SWITCH_PIN);

StepperMotor STEPPER_MOTOR_0 = StepperMotor(STEPPER_PINS_0);
StepperMotor STEPPER_MOTOR_1 = StepperMotor(STEPPER_PINS_1);
StepperMotor STEPPER_MOTOR_2 = StepperMotor(STEPPER_PINS_2);
StepperMotor STEPPER_MOTOR_3 = StepperMotor(STEPPER_PINS_3);

MotorController CONTROLLER_0 = MotorController(&STEPPER_MOTOR_0, &LIMMIT_SWITCH);
MotorController CONTROLLER_1 = MotorController(&STEPPER_MOTOR_1, &LIMMIT_SWITCH);
MotorController CONTROLLER_2 = MotorController(&STEPPER_MOTOR_2, &LIMMIT_SWITCH);
MotorController CONTROLLER_3 = MotorController(&STEPPER_MOTOR_3, &LIMMIT_SWITCH);

PixelClientReader CLIENT_READER = PixelClientReader();

const StepperMotorPins* getStepperMotorPins(char index) {
    if(index<0 || index>=PIXEL_COUNT) {
        // error: index out of bounds
        return NULL;
    }

    switch (index) {
        case 0:
            return &STEPPER_PINS_0;
        case 1:
            return &STEPPER_PINS_1;
        case 2:
            return &STEPPER_PINS_2;
        case 3:
            return &STEPPER_PINS_3;
        default:
            // error: out of bounds
            return NULL;
    }
}
StepperMotor* getStepperMotor(char index) {
    if(index<0 || index>=PIXEL_COUNT) {
        // error: index out of bounds
        return NULL;
    }

    switch (index) {
        case 0:
            return &STEPPER_MOTOR_0;
        case 1:
            return &STEPPER_MOTOR_1;
        case 2:
            return &STEPPER_MOTOR_2;
        case 3:
            return &STEPPER_MOTOR_3;
        default:
            // error: out of bounds
            return NULL;
    }
}
MotorController* getMotorController(char index) {
    if(index<0 || index>=PIXEL_COUNT) {
        // error: index out of bounds
        return NULL;
    }

    switch (index) {
        case 0:
            return &CONTROLLER_0;
        case 1:
            return &CONTROLLER_1;
        case 2:
            return &CONTROLLER_2;
        case 3:
            return &CONTROLLER_3;
        default:
            // error: out of bounds
            return NULL;
    }
}