/* ARCSweden 2023 */

#include "ReflectiveSensor.h"

ReflectiveSensor::ReflectiveSensor(int pin, int level, int epsilon)
    : mPin(pin), mLevel(level), mEpsilon(epsilon)
{}

void ReflectiveSensor::reset() {
    mFsm = FSM::WHITE;
    mCounter = 0;
    mSensorValue = 0;
}

void ReflectiveSensor::update(int diffTime) {
    mCurTime += diffTime;
    if(mCurTime >= 1000) {
        mSpeed = mPulsesPerSec;
        mPulsesPerSec = 0;
        mCurTime = 0;
    }

    mSensorValue = get_reading();
    switch(mFsm) {
        case FSM::WHITE:
        if(mSensorValue > mLevel + mEpsilon) {
            mFsm = FSM::BLACK;
            mCounter++;
            mPulsesPerSec++;
        }
        break;
        case FSM::BLACK:
        if(mSensorValue < mLevel - mEpsilon) {
            mFsm = FSM::WHITE;
        }
        break;
    }
}

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
