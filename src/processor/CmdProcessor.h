#ifndef PIXEL_PROCESSOR
#define PIXEL_PROCESSOR

#include "Stream.h"
#include "PixelClientLimit.h"
#include "PixelClientProcessor.h"
#include <controller/MotorController.h>

class HomeCmdProcessor: public AsyncCallback {
public:
    void home();
private:
    char pixel = -1;
    void onComplete(bool);
    void runNext();
};

class CmdProcessor: public PixelClientProcessor {
public:
    void onHome(unsigned char opcode);
    void onSetLimitsAndHome(unsigned char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void onSetLimit(unsigned char opcode, unsigned char pixle, const PixelClientLimit& limit);
    void onSetSteps(unsigned char opcode, unsigned char pixle, int steps);
    void onAddSteps(unsigned char opcode, unsigned char pixle, int steps);
    void onSetAngle(unsigned char opcode, unsigned char pixle, double angle);
    void onAddAngle(unsigned char opcode, unsigned char pixle, double angle);
    void onSetRequestType(unsigned char opcode, unsigned char requestType);
    void requestPing();
    int requestError();
private:
    HomeCmdProcessor homeProcessor;
};

#endif