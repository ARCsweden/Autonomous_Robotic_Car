#include <ReflectiveSensor.h>

// Pins for motor cntrl
const int MOTOR_PIN_1 = 5;
const int MOTOR_PIN_2 = 11;
const int INHIBIT_1 = 12;
const int INHIBIT_2 = 13;


const int LEVEL = 200;
const int EPSILON = 20;

// Parameter is pin number sensor is connected on
ReflectiveSensor left_encoder(3, LEVEL, EPSILON);
//ReflectiveSensor right_encoder(4, LEVEL, EPSILON);

void setup() {
  // Open up a serial console
  Serial.begin(9600);

  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  pinMode(INHIBIT_1, OUTPUT);
  pinMode(INHIBIT_2, OUTPUT);

  digitalWrite(INHIBIT_1, HIGH);
  digitalWrite(INHIBIT_2, HIGH);

  bidirMotor(-255);
}

int oldTime = 0;

void loop() {
  int curTime = millis();
  int diffTime = curTime - oldTime;
  oldTime = curTime;

  // Read sensor value
  left_encoder.update(diffTime);
  int speed = left_encoder.get_speed();

//  int right_val = right_encoder.get_reading();
  // Print out sensor value as a decimal number
//  Serial.print("cnt: ");
//  Serial.print(left_encoder.get_counter(), DEC);
//  Serial.print(" L: ");
  Serial.print(left_encoder.get_sensor(), DEC);
//  Serial.print(" Speed: ");
//  Serial.print(speed, DEC);
//  Serial.print(" R: ");
//  Serial.print(right_val, DEC);
  Serial.print("\n");
}

// Value from -255 to 255
void bidirMotor(int dir) {
  if(dir == 0) {
    analogWrite(MOTOR_PIN_1, 0);
    analogWrite(MOTOR_PIN_2, 0);
  } else if(dir > 0) {
    analogWrite(MOTOR_PIN_1, dir);
    analogWrite(MOTOR_PIN_2, 0);
  } else {
    analogWrite(MOTOR_PIN_1, 0);
    analogWrite(MOTOR_PIN_2, abs(dir));
  }
}

