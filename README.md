A project about RC car autonomization.

Current work is managed in this little project board: https://github.com/Cakem1x/brumm/projects/1

# Repo Organisation
Hardware
----------
See the wiki for now https://github.com/Cakem1x/brumm/wiki/Hardware

Software
----------
* Small, stand-alone **prototypes** to test different features we'll need on the Arduino: `arduino_ide_sketchbooks` 
  * `calib_with_poti`: Use poti to adjust PWM pulse width for getting desirable ranges for calibration.
  * `servotest_min_max`: For testing steering. Will control steering servo to move between left (min) and right (max).
  * `motortest_forward_mid_backward`: For testing the motor (via the drive controller). Will:
    * From standstill, accelerate to max speed forwards. Then, decrease speed back to standstill.
    * Then, from standstill, accelerate to max speed backwards. Then, decrease speed back to standstill.
    * Repeat.
