#ifndef PIXEL_CONTROLLER_CONFIG_CONFIG
#define PIXEL_CONTROLLER_CONFIG_CONFIG

#include "PixelClientReader.h"

#include <processor/Processor.h>
#include <pixle_controller/PixleController.h>

#ifndef I2C_ADDRESS
#define I2C_ADDRESS 8
#endif

#define STEPS_PER_REVOLUTION 4096

#define DIGITAL_PD0 0
#define DIGITAL_PD1 1
#define DIGITAL_PD2 2
#define DIGITAL_PD3 3
#define DIGITAL_PD4 4
#define DIGITAL_PD5 5
#define DIGITAL_PD6 6
#define DIGITAL_PD7 7
#define DIGITAL_PB0 8
#define DIGITAL_PB1 9
#define DIGITAL_PB2 10
#define DIGITAL_PB3 11
#define DIGITAL_PB4 12
#define DIGITAL_PB5 13
#define DIGITAL_PC0 14
#define DIGITAL_PC1 15
#define DIGITAL_PC2 16
#define DIGITAL_PC3 17
#define DIGITAL_PC4 18
#define DIGITAL_PC5 19

const StepperMotorPins STEPPER_PINS_1 = StepperMotorPins(DIGITAL_PD5,DIGITAL_PD4,DIGITAL_PD3,DIGITAL_PD2);
const StepperMotorPins STEPPER_PINS_2 = StepperMotorPins(DIGITAL_PC3,DIGITAL_PC2,DIGITAL_PC1,DIGITAL_PC0);
const StepperMotorPins STEPPER_PINS_3 = StepperMotorPins(DIGITAL_PB5,DIGITAL_PB4,DIGITAL_PB3,DIGITAL_PB2);
const StepperMotorPins STEPPER_PINS_4 = StepperMotorPins(DIGITAL_PB1,DIGITAL_PB0,DIGITAL_PD7,DIGITAL_PD6);

#define LIMMIT_SWITCH_PIN DIGITAL_PD1
extern LimitSwitch LIMMIT_SWITCH;

extern StepperMotor STEPPER_MOTOR_1;
extern StepperMotor STEPPER_MOTOR_2;
extern StepperMotor STEPPER_MOTOR_3;
extern StepperMotor STEPPER_MOTOR_4;

extern MotorController CONTROLLER_1;
extern MotorController CONTROLLER_2;
extern MotorController CONTROLLER_3;
extern MotorController CONTROLLER_4;

extern PixelClientReader CLIENT_READER;
extern PixleController PIXLE_CONTROLLER;

extern Processor PROCESSOR;

#endif