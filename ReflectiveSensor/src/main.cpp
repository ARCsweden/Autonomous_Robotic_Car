#include <Arduino.h>
#include <PID_v1.h>

#include <ReflectiveSensor.h>
#include <DCMotor.h>

// Pins for motor cntrl
const int MOTOR_PIN_1 = 5;
const int MOTOR_PIN_2 = 11;
const int INHIBIT_1 = 12;
const int INHIBIT_2 = 13;
DCMotor motor(MOTOR_PIN_1, MOTOR_PIN_2, INHIBIT_1, INHIBIT_2);

const int LEVEL = 200;
const int EPSILON = 10;
const int ENCODER_PIN = 3;
// Parameter is pin number sensor is connected on
ReflectiveSensor encoder(ENCODER_PIN, LEVEL, EPSILON);

//Define Variables we'll be connecting to
double pidSetpoint, pidInput, pidOutput;

int direction = 1; // 1, -1

//Specify the links and initial tuning parameters
//PID myPID(&pidInput, &pidOutput, &pidSetpoint, 2, 5, 0, DIRECT);

void setup() {
    // Open up a serial console
    Serial.begin(9600);

    motor.stop();

    //initialize the variables we're linked to
    pidInput = 0;
    pidSetpoint = 180;
    motor.setSpeed(255);

    //turn the PID on
    //myPID.SetMode(AUTOMATIC);
}

unsigned long oldTime = 0;
unsigned long timeAcc = 0;
unsigned long secondsCounter = 0;

/* PID Values */
double integral_prior = 0;
double error_prior = 0;

void loop() {
    unsigned long curTime = micros();
    unsigned long diffTime = curTime - oldTime; // in us
    oldTime = curTime;

    /* PID calculations */
    pidInput = encoder.get_angular_speed();
    const double Kp = 0.5;
    const double Ki = 0;
    const double Kd = 0;
    double error = pidSetpoint - pidInput;
    double integral = integral_prior + error * diffTime;
    double derivate = diffTime != 0 ? (error - error_prior) / diffTime : 0;
    pidOutput = Kp * error + Ki * integral + Kd * derivate;
    integral_prior = integral;
    error_prior = error;
    /* End PID calculations */

    //myPID.Compute();
    pidOutput = constrain(pidOutput, 0, 600);
    double set_speed = 255.f * pidOutput / 600.f;
    // TODO: Direction not set in PID
    //motor.setSpeed(set_speed * direction);

    timeAcc += diffTime;
    if(timeAcc >= 1000000ul) {
        timeAcc = 0;
        secondsCounter++;
        Serial.print("Time: ");
        Serial.print(secondsCounter, DEC);
        Serial.print("s Enc: ");
        Serial.print(encoder.get_counter(), DEC);
        Serial.print(" speed: ");
        Serial.print(encoder.get_angular_speed(), DEC);
        Serial.print(" error: ");
        Serial.print(error, DEC);
        Serial.print(" set_speed: ");
        Serial.println(set_speed, DEC);
    }
}
