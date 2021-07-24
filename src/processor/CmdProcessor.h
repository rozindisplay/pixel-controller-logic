#ifndef PIXEL_PROCESSOR
#define PIXEL_PROCESSOR

#include "Stream.h"
#include <pix/PixModel.h>
#include <pix/PixProcessor.h>
#include <controller/MotorController.h>

class HomeCmdProcessor: public AsyncCallback {
public:
    void home();
private:
    char pixel = -1;
    void onComplete(bool);
    void runNext();
};

class CmdProcessor: public PixProcessor {
public:
    void onInit(const PixLimit& limitP1, const PixLimit& limitP2, const PixLimit& limitP3, const PixLimit& limitP4);
    void onHome();
    void onClearErrorCode();
    void onSetLimit(unsigned char pixle, const PixLimit& limit);
    void onSetSteps(unsigned char pixle, int steps);
    void onAddSteps(unsigned char pixle, int steps);
    void onSetAngle(unsigned char pixle, double angle);
    void onAddAngle(unsigned char pixle, double angle);
    void requestPing();
    int requestErrorCode();
    unsigned char requestMovingCount();
    const PixStatus requestStatus(unsigned char pixle);
private:
    HomeCmdProcessor homeProcessor;    
};

#endif