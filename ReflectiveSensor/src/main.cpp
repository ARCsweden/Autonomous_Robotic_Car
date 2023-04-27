#include "Arduino.h"
#include <PID_v1.h>

#include <ReflectiveSensor.h>

// Pins for motor cntrl
const int MOTOR_PIN_1 = 5;
const int MOTOR_PIN_2 = 11;
const int INHIBIT_1 = 12;
const int INHIBIT_2 = 13;


const int LEVEL = 100;
const int EPSILON = 10;

// Parameter is pin number sensor is connected on
ReflectiveSensor encoder(3, LEVEL, EPSILON);


//Define Variables we'll be connecting to
double pidSetpoint, pidInput, pidOutput;

//Specify the links and initial tuning parameters
PID myPID(&pidInput, &pidOutput, &pidSetpoint, 2, 5, 0, DIRECT);

void bidirMotor(int dir);


void setup() {
    // Open up a serial console
    Serial.begin(9600);

    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(INHIBIT_1, OUTPUT);
    pinMode(INHIBIT_2, OUTPUT);

    digitalWrite(INHIBIT_1, HIGH);
    digitalWrite(INHIBIT_2, HIGH);

    bidirMotor(255);

    //initialize the variables we're linked to
    pidInput = 0;
    pidSetpoint = 180;

    //turn the PID on
    //myPID.SetMode(AUTOMATIC);
}

int oldTime = 0;
int timeAcc = 0;
int secondsCounter = 0;

void loop() {
    int curTime = millis();
    int diffTime = curTime - oldTime;
    oldTime = curTime;

    pidInput = encoder.get_angular_speed();
    double P = 0.5;
    pidOutput = pidOutput + P * (pidSetpoint - pidInput);
    //myPID.Compute();
    int set_speed = pidOutput / 360.f * 255.f;
    set_speed = constrain(set_speed, -255, 255);
    bidirMotor(set_speed);

    timeAcc += diffTime;


    if(timeAcc >= 1000) {
        secondsCounter++;
        timeAcc -= 1000;
        Serial.print("Time: ");
        Serial.print(secondsCounter, DEC);
        Serial.print("s Enc: ");
        Serial.print(encoder.get_counter(), DEC);
        Serial.print(" speed: ");
        Serial.print(encoder.get_angular_speed(), DEC);
        Serial.print("\n");
    }

  /*
    Serial.print(encoder.get_sensor(), DEC);
    Serial.print("\n");
  */
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
