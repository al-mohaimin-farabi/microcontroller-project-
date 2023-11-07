#include <Servo.h>
#include <AFMotor.h>

#define B_VRY_PIN A0
#define B_VRX_PIN A1
#define S_VRX_PIN A2
#define MAX_SPEED 190
#define MAX_SPEED_OFFSET 20

Servo spray_Angle;
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

int servo_Position = 0;
int  boat_Joystick_X;
int  boat_Joystick_y;
int  spray_Joystick_x;
int speedSet = 0;


void setup() {
  Serial.begin(9600);
  spray_Angle.attach(10);
}

void loop() {
   boat_Joystick_X = analogRead(B_VRX_PIN);
   boat_Joystick_y = analogRead(B_VRY_PIN);
   spray_Joystick_x = analogRead(S_VRX_PIN);

  int sprayPosition = map(spray_Joystick_x, 0, 1023, 0, 180);
  spray_Angle.write(sprayPosition);

  if ( boat_Joystick_X >= 800) {
    moveForward();
  } else if ( boat_Joystick_X <= 250) {
    moveBackward();
  } else if ( boat_Joystick_y >= 800) {
    turnRight();
  } else if ( boat_Joystick_y <= 250) {
    turnLeft();
  } else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
}

void moveForward() {
  delay(200);

  Serial.print("ff");

  delay(200);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2)  // slowly bring the speed up to avoid loading down the batteries too quickly
  {

    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
}

void moveBackward() {
  delay(200);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2)  // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  delay(200);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}
void turnLeft() {
  delay(200);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}
