#ifndef PIXEL_CONTROLLER_PIXEL_CONTROLLER
#define PIXEL_CONTROLLER_PIXEL_CONTROLLER

#include <looper/Loopable.h>
#include <controller/MotorController.h>

#define PIXLE_CONTROLLER_STATE_IDLE 0
#define PIXLE_CONTROLLER_STATE_HOME 1

class PixleController: Loopable {
public:
    void run();
    void home();
    MotorController* getMotorController(char index);
private:
    void runIdle();
    void runHome();

    int state = PIXLE_CONTROLLER_STATE_IDLE;
};

#endif