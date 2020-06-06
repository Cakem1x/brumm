#include <Servo.h>

// serial output
const int baud_rate = 9600;

// steering
const int servo_pin= 7;          // should be MEGA's pin "PWM7"
Servo steering_servo;
const int min_pulse_width = 1000;  // µs
const int max_pulse_width = 2000;  // µs

// poti
const int potentiometer_pin = 0; // should be MEGA's pin A0

void setup()
{
  // I/O
  Serial.begin(baud_rate);

  // steering
  Serial.println("Setting up servo");
  steering_servo.attach(servo_pin, min_pulse_width, max_pulse_width);
  Serial.print("Servo attached to PIN ");
  Serial.println(servo_pin);

  // potentiometer
  Serial.println("Setting up potentiometer");
  Serial.print("Potentiometer attached to PIN ");
  Serial.println(potentiometer_pin);
}

void loop()
{
  // map poti to [0.0, 1.0]
  float potentiometer_ratio = static_cast<float>(analogRead(potentiometer_pin)) / 1024.0f;
  Serial.print("pot val is ");
  Serial.print(potentiometer_ratio);
  Serial.print(". Map onto [");
  Serial.print(min_pulse_width);
  Serial.print(", ");
  Serial.print(max_pulse_width);
  Serial.print("].");
  Serial.println();

  // find corresponding value in [min_pulse_width, max_pulse_width]
  const int value_range = max_pulse_width - min_pulse_width;
  const int target_pulse_width = min_pulse_width + static_cast<int>(static_cast<float>(value_range) * potentiometer_ratio + 0.5f);
  // output to serial and servo
  Serial.print("setting target pulse width: ");
  Serial.print(target_pulse_width);
  Serial.println();
  steering_servo.write(target_pulse_width);
}
