/* ARCSweden 2023 */

#include "ReflectiveSensor.h"

ReflectiveSensor::ReflectiveSensor(int pin)
    : mPin(pin)
{}

int ReflectiveSensor::get_reading() {
    // Load reflective sensor by driving pin at least 10us
    pinMode(mPin, OUTPUT);
    digitalWrite(mPin, HIGH);
    delayMicroseconds(20);
    // Set pin to input and wait until sensor has depleted
    pinMode(mPin, INPUT);
    int usCounter = 0;
    while(digitalRead(mPin) == HIGH) {
        usCounter++;
        delayMicroseconds(1);
    }
    return usCounter;
}
