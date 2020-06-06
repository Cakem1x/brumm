#include <Servo.h>

int mapRatioOnIntRange(float ratio, int min, int max)
{
  const int value_range = max - min;
  return min + static_cast<int>(static_cast<float>(value_range) * ratio + 0.5f);
}

// serial output
const int baud_rate = 9600;

// should be MEGA's pin "PWM7"
const int servo_pin= 7;
Servo steering_servo;

// use calibration sketch to get these
const int min_pulse_width = 1123; // left
const int max_pulse_width = 1734; // right

// steering speed
const float servo_pose_percentage_increment = 0.01;
const int delay_duration = 15;

// program state
bool increase_servo_pos = true;
float servo_pos_percentage = 0.5;

void setup()
{
  // I/O
  Serial.begin(baud_rate);

  // steering
  Serial.println("Setting up servo");
  steering_servo.attach(servo_pin);
  steering_servo.writeMicroseconds(mapRatioOnIntRange(0.5, min_pulse_width, max_pulse_width));
  Serial.print("Servo attached to PIN ");
  Serial.println(servo_pin);
}

void loop()
{
  if (increase_servo_pos)
  {
    servo_pos_percentage += servo_pose_percentage_increment;
    if (servo_pos_percentage >= 1.0f)
    {
      servo_pos_percentage = 1.0f;
      increase_servo_pos = false;
    }
  }
  else
  {
    servo_pos_percentage -= servo_pose_percentage_increment;
    if (servo_pos_percentage <= 0.0f)
    {
      servo_pos_percentage = 0.0f;
      increase_servo_pos = true;
    }
  }

  const int servo_pulse_width =
    mapRatioOnIntRange(servo_pos_percentage, min_pulse_width, max_pulse_width);
  Serial.print("Target: ");
  Serial.print(servo_pos_percentage);
  Serial.print(" --> ");
  Serial.print(servo_pulse_width);
  Serial.print("ms");
  Serial.println();
  steering_servo.writeMicroseconds(servo_pulse_width);

  // setup next loop
  delay(delay_duration);
}
