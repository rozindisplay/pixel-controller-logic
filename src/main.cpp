// Include the Arduino Stepper Library
#include "Arduino.h"
#include "Wire.h"
#include <confg/Config.h>
#include <processor/CmdProcessor.h>

CmdProcessor processor = CmdProcessor();

static void receive(int bytes) {
	int err;
	while(CLIENT_READER.hasNext()) {
		err = CLIENT_READER.next(&processor);
		if(err!=0) ERR.error(err);
	}
}

static void request() {
	int err = CLIENT_READER.nextRequest(&processor);
	if(err!=0) ERR.error(err);
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
