/* ARCSweden 2023 */

#include "DCMotor.h"
#include "Arduino.h"

DCMotor::DCMotor(int pin1, int pin2, int inhibit1, int inhibit2)
    : mPin1(pin1)
    , mPin2(pin2)
{
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(inhibit1, OUTPUT);
    pinMode(inhibit2, OUTPUT);

    digitalWrite(inhibit1, HIGH);
    digitalWrite(inhibit2, HIGH);
}

// Value from -255 to 255
void DCMotor::setSpeed(int dir) {
    dir = constrain(dir, -255, 255);
    if(dir == 0) {
        analogWrite(mPin1, 0);
        analogWrite(mPin2, 0);
    } else if(dir > 0) {
        analogWrite(mPin1, dir);
        analogWrite(mPin2, 0);
    } else {
        analogWrite(mPin1, 0);
        analogWrite(mPin2, abs(dir));
    }
}

void DCMotor::stop() {
    setSpeed(0);
}
