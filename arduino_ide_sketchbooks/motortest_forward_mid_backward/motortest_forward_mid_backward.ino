#include <Servo.h>

int mapRatioOnIntRange(float ratio, int min, int max)
{
  const int value_range = max - min;
  return min + static_cast<int>(static_cast<float>(value_range) * ratio + 0.5f);
}

// serial output
const int baud_rate = 9600;

// should be MEGA's pin "PWM7"
const int motor_pin= 7;
// expects input like a servo, so we can use the servo lib
Servo motor_controller;

// use calibration sketch to get these
const int pulse_width_max_speed_backwards = 1000;
const int pulse_width_stop = 1500;
const int pulse_width_max_speed_forward = 2000;

// speed at which state changes
const float speed_percentage_increment = 0.01;
const int delay_duration = 15;
const int stop_duration = 50;

// program state
enum DriveState
{
  Stop = 0,
  Forward = 1,
  Backward = 2,
};

DriveState current_drive_state = DriveState::Stop;
DriveState next_drive_state = DriveState::Forward;
bool speed_increase = false;
float current_speed = 0.0;
int stop_counter = 0;

void setup()
{
  // I/O
  Serial.begin(baud_rate);

  // steering
  Serial.println("Setting up motor");
  motor_controller.attach(motor_pin);
  motor_controller.writeMicroseconds(pulse_width_stop);
  Serial.print("Motor attached to PIN ");
  Serial.println(motor_pin);
}

void loop()
{
  int motor_pulse_width;

  switch (current_drive_state)
  {
  case DriveState::Stop:
    motor_pulse_width = pulse_width_stop;
    stop_counter += 1;
    if (stop_counter > stop_duration)
    {
      current_drive_state = next_drive_state;
    }
    break;
  case DriveState::Forward:
    if (speed_increase)
    {
      current_speed += speed_increase;
      if (current_speed >= 1.0f)
      {
        current_speed = 1.0f;
        speed_increase = false;
      }
    }
    else
    {
      current_speed -= speed_increase;
      if (current_speed <= 0.0f)
      {
        current_speed = 0.0f;
        speed_increase = true;
        next_drive_state = DriveState::Backward;
        current_drive_state = DriveState::Stop;
      }
    }
    motor_pulse_width = mapRatioOnIntRange(current_speed, pulse_width_stop, pulse_width_max_speed_forward);
    break;
  case DriveState::Backward:
    if (speed_increase)
    {
      current_speed += speed_increase;
      if (current_speed >= 1.0f)
      {
        current_speed = 1.0f;
        speed_increase = false;
      }
    }
    else
    {
      current_speed -= speed_increase;
      if (current_speed <= 0.0f)
      {
        current_speed = 0.0f;
        speed_increase = true;
        next_drive_state = DriveState::Forward;
        current_drive_state = DriveState::Stop;
      }
    }
    motor_pulse_width = mapRatioOnIntRange(1.0f - current_speed, pulse_width_max_speed_backwards, pulse_width_stop);
    break;
  }

  Serial.print("Target: ");
  Serial.print(motor_pulse_width);
  Serial.print("ms");
  Serial.println();
  motor_controller.writeMicroseconds(motor_pulse_width);

  // setup next loop
  delay(delay_duration);
}
