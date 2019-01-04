// We use adadfruit.io for logging/graphing

// The cheap/easy sensor I found on sparkfun
#include <Particle_SI7021.h>

#include "papertrail_config.h"

PRODUCT_ID(8583); // humidity product
PRODUCT_VERSION(1); // increment each time you upload to the console

// Devices
SI7021 sensor;

// Auto published variables
double tempC = -100;
double rH = -1;

#if 0
// Soon to be deleted test code

int getHumidity(String command) {
	si7021_thc r = sensor.getTempAndRH();

	return r.humidityPercent;                                                                 // r.celsiusHundredths;
}

// GPIO setup example
//pinMode(led1, OUTPUT);
Particle.function("getHumidity", getHumidity); // FIXME - delete after variables confirmed to work
#endif

// Last time, we only needed to declare pins in the setup function.
// This time, we are also going to register our Particle function

void setup()
{
	Particle.publish("log", "in setup");
	Log.info("in setup");

	// Test function for particle
	Particle.function("led",ledToggle);

	// If our sensor is connected expose our vars
	if(sensor.begin()) {
		Particle.variable("temperature", tempC);
		Particle.variable("humidity", rH);
	}
}




void loop()
{
	static unsigned long lastUpdate = 0;

	if(sensor.sensorExists()) {
		si7021_thc r = sensor.getTempAndRH();
		rH = r.humidityPercent / 100.0;
		tempC = r.celsiusHundredths / 100.0;
	}

	unsigned long now = Time.now();
	// int maxRate = 60 * 60; // one hour in seconds
	int maxRate = 60;                                                                 // one minute in seconds
	if(now > lastUpdate + maxRate) {
		lastUpdate = now;

		Log.info("publishing %d RH, %f degC", (int)( rH * 100), tempC);

		// Send publishes to particle.io
		// Note - may block for a long time (5 min) if not connected to web
		{
			String asStr(rH);
			Particle.publish("humidity", asStr);
		}
		{
			String asStr(tempC);
			Particle.publish("temperature", asStr);
		}
	}

	delay(1000);                                                                 // wait one sec. no need to keep hammering the sensor too often
}


// Sample code test function - delete soon
int ledToggle(String command) {
	/* Particle.functions always take a string as an argument and return an integer.
	   Since we can pass a string, it means that we can give the program commands on how the function should be used.
	   In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
	   Then, the function returns a value to us to let us know what happened.
	   In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
	   and -1 if we received a totally bogus command that didn't do anything to the LEDs.
	 */

	if (command=="on") {
		// digitalWrite(led1,HIGH);
		RGB.control(true);
		RGB.color(255, 0, 0);                                                                                                                                 // red
		return 1;
	}
	else if (command=="off") {
		RGB.color(0, 255, 0);                                                                                                                                 // green
		RGB.control(false);
		return 0;
	}
	else {
		return -1;
	}
}
