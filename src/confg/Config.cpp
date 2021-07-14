#include "Wire.h"
#include <confg/Config.h>

LimitSwitch LIMMIT_SWITCH = LimitSwitch(LIMMIT_SWITCH_PIN);

StepperMotor STEPPER_MOTOR_1 = StepperMotor(STEPPER_PINS_1);
StepperMotor STEPPER_MOTOR_2 = StepperMotor(STEPPER_PINS_2);
StepperMotor STEPPER_MOTOR_3 = StepperMotor(STEPPER_PINS_3);
StepperMotor STEPPER_MOTOR_4 = StepperMotor(STEPPER_PINS_4);

MotorController CONTROLLER_1 = MotorController(&STEPPER_MOTOR_1);
MotorController CONTROLLER_2 = MotorController(&STEPPER_MOTOR_2);
MotorController CONTROLLER_3 = MotorController(&STEPPER_MOTOR_3);
MotorController CONTROLLER_4 = MotorController(&STEPPER_MOTOR_4);

PixelClientReader CLIENT_READER = PixelClientReader();
Processor PROCESSOR = Processor();
PixleController PIXLE_CONTROLLER = PixleController();