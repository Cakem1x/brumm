#include <Servo.h>

const int SERVO_PIN = 7;          // should be MEGA's PIN "PWM7"
const int min_pulse_width = 1040;  // µs
const int max_pulse_width = 1820;  // µs

Servo myservo;
int servo_angle = 90;
bool increase_angle = true;

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up servo");
  myservo.attach(SERVO_PIN, min_pulse_width, max_pulse_width);
  Serial.print("Servo attached to PIN");
  Serial.println(SERVO_PIN);
}

void loop()
{
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

  myservo.write(servo_angle);

  Serial.print("Reading servo angle: ");
  Serial.print(myservo.read());
  Serial.println(" degree");

  delay(delay_duration);
}
