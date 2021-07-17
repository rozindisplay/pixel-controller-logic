#ifndef PIXEL_CONTROLLER_ERR
#define PIXEL_CONTROLLER_ERR

#include <confg/Consts.h>

#define ERR_NONE 0
#define ERR_HOMING_IN_PROGRESS 1
#define ERR_SET_OUT_OF_BOUNDS 2
#define ERR_MOVED_OUT_OF_BOUNDS 3
#define ERR_CONTROLLER_STATE_UNKNOWN 4
#define ERR_LIMIT_NOT_FOUND 5
#define ERR_LIMIT_OFF_NOT_FOUND 6

class Errors {
public:
    Errors();
    void error(int code);
    int reset();
private:
    int code;
};

extern Errors ERR;

#endif
