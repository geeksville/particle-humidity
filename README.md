# A small humidity sensor for my garage

NOTE: This project is not yet complete.  This readme currently is a raw set of notes to myself...

## Steps to build/install

Rather than using the adequate but very basic web IDE, I've opted to build
locally via their CLI.

Steps required:
* Install the "particle" binary per [instructions](https://docs.particle.io/tutorials/developer-tools/cli/)
* Run "particle setup" to login to your account
* This project also logs data to the adafruit.io platform, so you'll need to
register an account there and download your "AIO key" into a file called
"adafruit_keys.h"
* If you want to run a test compile run "particle compile photon" (or whatever
  other device type you are targeting)
* If you want to compile your code and deploy it to your device
"particle flash your_device_name"

## Notes yet to categorize

use particle board to ifttt

sensor: https://learn.sparkfun.com/tutorials/si7021-humidity-and-temperature-sensor-hookup-guide
https://cdn.sparkfun.com/datasheets/Sensors/Weather/Si7021.pdf

https://learn.sparkfun.com/tutorials/photon-development-guide/particle-build-online

use adafruit for logging
https://learn.adafruit.com/home-automation-in-the-cloud-with-the-esp8266-and-adafruit-io/hardware-and-software-requirements

* particle web api docs

curl "https://api.particle.io/v1/devices/0123456789abcdef/temp?access_token=123412341234"

* how to talk to adafruit

https://www.hackster.io/anasdalintakam/particle-photon-mqtt-integration-with-adafruit-io-6e1d22

* Rejected ideas
Thingspeak talks to particle, but not worth it because matlab centric

* cli setup
https://docs.particle.io/tutorials/developer-tools/cli/
