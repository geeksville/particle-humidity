# A small humidity sensor for my garage

You can see the output of this sensor here: https://io.adafruit.com/punkgeek/dashboards/garage

## Steps to build/install

Rather than using the adequate but very basic web IDE, I've opted to build
locally via their CLI.

Steps required:
* Install the "particle" binary per [instructions](https://docs.particle.io/tutorials/developer-tools/cli/)
* Run "particle setup" to login to your account
* If you want to run a test compile run "particle compile photon" (or whatever
  other device type you are targeting)
* If you want to compile your code and deploy it to your device
"particle flash your_device_name"

## Debugging

* The LED on the photon has some helpful [blink codes](https://docs.particle.io/tutorials/device-os/led/photon/)

## Implementation notes

* use particle board to ifttt

* sensor: https://learn.sparkfun.com/tutorials/si7021-humidity-and-temperature-sensor-hookup-guide

* use adafruit for logging
https://learn.adafruit.com/home-automation-in-the-cloud-with-the-esp8266-and-adafruit-io/hardware-and-software-requirements

* Rejected ideas: Thingspeak talks to particle, but not worth it because matlab centric

* cli setup: https://docs.particle.io/tutorials/developer-tools/cli/
