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
    int pixel = -1;
    void onComplete(bool);
    void runNext();
};

class CmdProcessor: public PixProcessor {
public:
    
    void onHome();
    void onHome(unsigned char pixel);
    void onSetLimit(unsigned char pixel, const PixLimit& limit);
    void onSetSteps(unsigned char pixel, int steps);
    void onAddSteps(unsigned char pixel, int steps);
    void onSetAngle(unsigned char pixel, double angle);
    void onAddAngle(unsigned char pixel, double angle);
    void onClearErrorCode();
    void requestPing();
    unsigned char requestPixels();
    unsigned char requestMoving();
    bool requestIsMoving(unsigned char pixel);
    int requestTargetSteps(unsigned char pixel);
    int requestSteps(unsigned char pixel);
    double requestTargetAngle(unsigned char pixel);
    double requestAngle(unsigned char pixel);
    const PixLimit requestLimit(unsigned char pixel);
    const PixStatus requestStatus(unsigned char pixel);
    int requestErrorCode();
private:
    HomeCmdProcessor homeProcessor;    
};

#endif