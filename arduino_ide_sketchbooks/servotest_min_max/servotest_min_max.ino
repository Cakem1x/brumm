#include <Servo.h>

// serial output
const int baud_rate = 9600;

// steering
const int servo_pin= 7;          // should be MEGA's pin "PWM7"
Servo steering_servo;
// use calibration sketch to get these
const int min_pulse_width = 1000;
const int max_pulse_width = 2000;

// program state
bool increase_angle = true;
int servo_angle = 0;

void setup()
{
  // I/O
  Serial.begin(baud_rate);

  // steering
  Serial.println("Setting up servo");
  steering_servo.attach(servo_pin, min_pulse_width, max_pulse_width);
  Serial.print("Servo attached to PIN ");
  Serial.println(servo_pin);
}

void loop()
{
  // steering servo
  const int angle_increment = 1;
  const int delay_duration = 15;

  if (increase_angle)
  {
    servo_angle += angle_increment;
    if (servo_angle >= 180)
    {
      servo_angle = 180;
      increase_angle = false;
    }
  }
  else
  {
    servo_angle -= angle_increment;
    if (servo_angle <= 0)
    {
      servo_angle = 0;
      increase_angle = true;
    }
  }

  Serial.print("Setting servo to angle ");
  Serial.print(servo_angle);
  Serial.println(" degree");

  // delay
  delay(delay_duration);
}
