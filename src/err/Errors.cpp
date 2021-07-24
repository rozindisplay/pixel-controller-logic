#include "Errors.h"

Errors::Errors(): code(ERR_NONE) {
}

void Errors::error(int code) {
    this->code = code;
}

int Errors::reset() {
    int code = this->code;
    this->code = ERR_NONE;
    return code;
}

int Errors::getCode() {
    return code;
}

Errors ERR = Errors();