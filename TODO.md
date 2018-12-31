# TODO for Humidity
* remove dead test code
* use the application layer watchdog https://docs.particle.io/reference/device-os/firmware/photon/#application-watchdog

# For other non humidity applications
* Use the Papertrail logging provider
* possibly use SYSTEM_THREAD mode as described in the debugging page - to allow
running loop() before we have net connection.
* possibly use semi-automatic wifi mode for a similar effect
* keep schedules in backup SRAM or EEPROM
* Use sleep to cut power consumption (if on battery)
