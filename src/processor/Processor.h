#ifndef PIXEL_PROCESSOR
#define PIXEL_PROCESSOR

#include "Stream.h"
#include "PixelClientLimit.h"
#include "PixelClientProcessor.h"
#include <controller/MotorController.h>

class Processor: public PixelClientProcessor {
public:
    void onHome(char opcode);
    void onSetLimitsAndHome(char opcode, const PixelClientLimit& limitP1, const PixelClientLimit& limitP2, const PixelClientLimit& limitP3, const PixelClientLimit& limitP4);
    void onSetLimit(char opcode, char pixle, const PixelClientLimit& limit);
    void onSetSteps(char opcode, char pixle, int steps);
    void onAddSteps(char opcode, char pixle, int steps);
    void onSetAngle(char opcode, char pixle, double angle);
    void onAddAngle(char opcode, char pixle, double angle);
};

#endif