#ifndef PIXEL_CONTROLLER_CONFIG_CONFIG
#define PIXEL_CONTROLLER_CONFIG_CONFIG

#include "Consts.h"
#include "PixelClientReader.h"
#include <hardware/limit/LimitSwitch.h>
#include <hardware/stepper/StepperMotor.h>
#include <controller/MotorController.h>
#include <err/Errors.h>

const StepperMotorPins STEPPER_PINS_0 = StepperMotorPins(DIGITAL_PD5,DIGITAL_PD4,DIGITAL_PD3,DIGITAL_PD2);
const StepperMotorPins STEPPER_PINS_1 = StepperMotorPins(DIGITAL_PC3,DIGITAL_PC2,DIGITAL_PC1,DIGITAL_PC0);
const StepperMotorPins STEPPER_PINS_2 = StepperMotorPins(DIGITAL_PB5,DIGITAL_PB4,DIGITAL_PB3,DIGITAL_PB2);
const StepperMotorPins STEPPER_PINS_3 = StepperMotorPins(DIGITAL_PB1,DIGITAL_PB0,DIGITAL_PD7,DIGITAL_PD6);

extern LimitSwitch LIMMIT_SWITCH;

extern StepperMotor STEPPER_MOTOR_0;
extern StepperMotor STEPPER_MOTOR_1;
extern StepperMotor STEPPER_MOTOR_2;
extern StepperMotor STEPPER_MOTOR_3;

extern MotorController CONTROLLER_0;
extern MotorController CONTROLLER_1;
extern MotorController CONTROLLER_2;
extern MotorController CONTROLLER_3;

extern PixelClientReader CLIENT_READER;

const StepperMotorPins* getStepperMotorPins(char index);
StepperMotor* getStepperMotor(char index);
MotorController* getMotorController(char index);

#endif