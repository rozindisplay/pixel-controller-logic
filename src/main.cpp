// Include the Arduino Stepper Library
#include "Arduino.h"
#include "Wire.h"
#include <confg/Config.h>

static void receive(int bytes) {
	while(CLIENT_READER.hasNext()) {
		CLIENT_READER.next(&PROCESSOR);
	}
}

static void request() {
}

void setup() {
	// initialize I2C
	Wire.begin(I2C_ADDRESS);
	Wire.onReceive(receive);
	Wire.onRequest(request);
}

void loop() {
	PIXLE_CONTROLLER.run();
	delay(1);
}
