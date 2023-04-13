/* ARCSweden 2023 */

#include "ReflectiveSensor.h"

int _sensor_pin = 0;
unsigned long _old_time = 0;
volatile int _sensor_reading = 0;

void _trigger_sensor() {
    // Load reflective sensor by driving pin at least 10us
    pinMode(_sensor_pin, OUTPUT);
    digitalWrite(_sensor_pin, HIGH);
    delayMicroseconds(20); // TODO: Can test to reduce this
    // Set pin to input and wait until sensor has depleted
    pinMode(_sensor_pin, INPUT);
}

void _sensor_ISR() {
    // Readout current time
    unsigned long cur_time = micros();
    unsigned long diff_time = cur_time - _old_time;

    // Set _sensor_reading value (microseconds since last sensor reading start)
    _sensor_reading = diff_time;

    // Trigger new read
    _trigger_sensor();

    _old_time = micros();
}

ReflectiveSensor::ReflectiveSensor(int pin, int level, int epsilon)
    : mLevel(level), mEpsilon(epsilon)
{
    _sensor_pin = pin;

    _trigger_sensor();

    attachInterrupt(digitalPinToInterrupt(pin), _sensor_ISR, FALLING);
}

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
    return _sensor_reading;
}
