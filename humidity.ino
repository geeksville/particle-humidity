// We use adadfruit.io for logging/graphing

// The cheap/easy sensor I found on sparkfun
#include <Particle_SI7021.h>

#include <ParticleWebLog.h>

PRODUCT_ID(8583); // humidity product
PRODUCT_VERSION(1); // increment each time you upload to the console

// Devices
SI7021 sensor;

// Auto published variables
double tempC = -100;
double rH = -1;

ParticleWebLog webLog;

// Last time, we only needed to declare pins in the setup function.
// This time, we are also going to register our Particle function

void setup()
{
    Log.info("in setup");

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
    int maxRate = 60;                                                                                     // one minute in seconds
    if(now > lastUpdate + maxRate) {
        lastUpdate = now;

        Log.info("publishing %d RH, %f degC", (int)( rH * 100), tempC);

        // Send publishes to particle.io
        // Note - may block for a long time (5 min) if not connected to web
        {
            String asStr(rH);
            Particle.publish("humidity", asStr, PRIVATE);

            // Have a separate threshold for an alarm (ifttt)
            const float maxHumid = 0.65;
            if(rH > maxHumid)
                Particle.publish("alarm-humidity", asStr, PRIVATE);
        }
        {
            String asStr(tempC);
            Particle.publish("temperature", asStr, PRIVATE);
        }
    }

    delay(1000);                                                                                     // wait one sec. no need to keep hammering the sensor too often
}
