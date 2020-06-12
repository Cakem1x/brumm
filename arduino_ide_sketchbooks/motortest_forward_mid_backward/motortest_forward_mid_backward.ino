#include <Servo.h>
#include "drive_state.h"

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
const int delay_duration = 50;
const int stop_duration = 200;

DriveState current_drive_state = DriveState::StopAfterBackwardMovement;
float current_speed = 0.0; // speed between 0 and 1, gets mapped on min/max speed values
int stop_counter = 0; // counter used to standstill for a defined duration

void setup()
{
  // I/O
  Serial.begin(baud_rate);

  // motor output
  Serial.println("Setting up motor");
  motor_controller.attach(motor_pin);
  motor_controller.writeMicroseconds(pulse_width_stop);
  Serial.print("Motor attached to PIN ");
  Serial.println(motor_pin);
}

void loop()
{
  int motor_pulse_width = pulse_width_stop; // will be overwritten later

  switch (current_drive_state)
  {
  case DriveState::StopAfterBackwardMovement:
  case DriveState::StopAfterForwardMovement:
    motor_pulse_width = pulse_width_stop;
    stop_counter += 1;
    if (stop_counter > stop_duration)
    {
      current_drive_state = transition(current_drive_state);
      stop_counter = 0;
    }
    break;

  case DriveState::ForwardAccelerate:
    current_speed += speed_percentage_increment;
    if (current_speed >= 1.0f)
    {
      current_speed = 1.0f;
      current_drive_state = transition(current_drive_state);
    }
    motor_pulse_width = mapRatioOnIntRange(current_speed, pulse_width_stop, pulse_width_max_speed_forward);
    break;

  case DriveState::ForwardDecelerate:
    current_speed -= speed_percentage_increment;
    if (current_speed <= 0.0f)
    {
      current_speed = 0.0f;
      current_drive_state = transition(current_drive_state);
    }
    motor_pulse_width = mapRatioOnIntRange(current_speed, pulse_width_stop, pulse_width_max_speed_forward);
    break;

  case DriveState::BackwardAccelerate:
    current_speed += speed_percentage_increment;
    if (current_speed >= 1.0f)
    {
      current_speed = 1.0f;
      current_drive_state = transition(current_drive_state);
    }
    motor_pulse_width = mapRatioOnIntRange(1.0f - current_speed, pulse_width_max_speed_backwards, pulse_width_stop);
    break;

  case DriveState::BackwardDecelerate:
    current_speed -= speed_percentage_increment;
    if (current_speed <= 0.0f)
    {
      current_speed = 0.0f;
      current_drive_state = transition(current_drive_state);
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
