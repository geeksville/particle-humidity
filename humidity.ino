// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_SPARK.h>
#include "adafruit_keys.h"


// This #include statement was automatically added by the Particle IDE.
#include <Particle_SI7021.h>


/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

TCPClient TheClient;
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,IO_USERNAME,IO_KEY);

/****************************** Feeds ***************************************/
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish humidityFeed = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/garage.humidity");

SI7021 sensor;

// Auto published variables
double tempC = -100;
double rH = -1;

// Loop persistent state
unsigned long lastUpdate = 0;

int getHumidity(String command) {
    si7021_thc r = sensor.getTempAndRH();

    return r.humidityPercent; // r.celsiusHundredths;
}

// Last time, we only needed to declare pins in the setup function.
// This time, we are also going to register our Particle function

void setup()
{

   // Here's the pin configuration, same as last time
   //pinMode(led1, OUTPUT);

   // We are also going to declare a Particle.function so that we can turn the LED on and off from the cloud.
   Particle.function("led",ledToggle);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.


   if(sensor.begin()) {
       Particle.variable("temperature", &tempC, DOUBLE);
       Particle.variable("humidity", &rH, DOUBLE);

       Particle.function("getHumidity", getHumidity); // FIXME - delete after variables confirmed to work
   }
}




void loop()
{
    if(0) {
        if(sensor.sensorExists()) {
            si7021_thc r = sensor.getTempAndRH();
            rH = r.humidityPercent / 100.0;
            tempC = r.celsiusHundredths / 100.0;
        }

        unsigned long now = Time.now();
        // int maxRate = 60 * 60; // one hour in seconds
        int maxRate = 60; // one minute in seconds
        if(0 && now > lastUpdate + maxRate) {
            lastUpdate = now;

            // Note - may block for a long time (5 min) if not connected to web
            String asStr(rH);
            Particle.publish("newHumidity", asStr.c_str());

            if( mqtt.Update() ){
                humidityFeed.publish(rH);
            }
        }

        delay(200); // wait 200ms - no need to keep hammering the sensor too often
    }
}

// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Particle.function earlier.


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
        RGB.color(255, 0, 0); // red
        return 1;
    }
    else if (command=="off") {
        RGB.color(0, 255, 0); // green
        RGB.control(false);
        return 0;
    }
    else {
        return -1;
    }
}
