// Include the Arduino Stepper Library
#include "Arduino.h"
#include "Wire.h"
#include <confg/Config.h>
#include <processor/CmdProcessor.h>

CmdProcessor processor = CmdProcessor();

static void receive(int bytes) {
	while(CLIENT_READER.hasNext()) {
		CLIENT_READER.next(&processor);
	}
}

static void request() {
	CLIENT_READER.nextRequest(&processor);
}

void setup() {
	// initialize I2C
	Wire.begin(I2C_ADDRESS);
	Wire.onReceive(receive);
	Wire.onRequest(request);
}

void loop() {
	// process each pixel
	
	for(size_t i=0; i<PIXEL_COUNT; i++) {
		getMotorController(i)->run();
	}
	
	delay(1);
}
