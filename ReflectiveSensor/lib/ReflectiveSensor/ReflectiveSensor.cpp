/* ARCSweden 2023 */

#include "ReflectiveSensor.h"
#include <TimerOne.h>

int _sensor_pin = 0;
volatile unsigned long _old_time = 0;
volatile unsigned long _sensor_reading = 0;
volatile unsigned long _sensor_counter = 0;
volatile unsigned long _sensor_time_since_last = 0;
volatile unsigned long _last_tick_time = 0;
unsigned long _sensor_level = 0;
int _sensor_epsilon = 0;

enum class FSM {
    WHITE,
    BLACK,
};

FSM _fsm = FSM::WHITE;

void _trigger_sensor() {
    // Load reflective sensor by driving pin at least 10us
    pinMode(_sensor_pin, OUTPUT);
    digitalWrite(_sensor_pin, HIGH);
    delayMicroseconds(50); // 10us required to charge cap
    //digitalWrite(_sensor_pin, LOW);
    //delayMicroseconds(10); // 10us required to charge cap
    // Set pin to input and wait until sensor has depleted
    _old_time = micros();
    pinMode(_sensor_pin, INPUT);
    EIFR = 0x01 << digitalPinToInterrupt(_sensor_pin);
}

void _sensor_ISR() {
    // Readout current time
    unsigned long cur_time = micros();
    unsigned long diff_time = cur_time - _old_time;

    // Set _sensor_reading value (microseconds since last sensor reading start)
    _sensor_reading = diff_time;

    switch(_fsm) {
        case FSM::WHITE:
            if(_sensor_reading > _sensor_level + _sensor_epsilon) {
                _fsm = FSM::BLACK;
                // Increment the encoder count
                _sensor_counter++;
                // Set speed value to number of microseconds since last detected encoder tick
                _sensor_time_since_last = cur_time - _last_tick_time;
                _last_tick_time = cur_time;
            }
            break;
        case FSM::BLACK:
            if(_sensor_reading < _sensor_level - _sensor_epsilon) {
                _fsm = FSM::WHITE;
            }
            break;
    }

    const unsigned long SLOW_TIME = 500000;
    if(cur_time - _last_tick_time >= SLOW_TIME) {
        _sensor_time_since_last = 0;
    }
}

ReflectiveSensor::ReflectiveSensor(int pin, int level, int epsilon, int num_markers)
    : mNumMarkers(num_markers)
{
    _sensor_pin = pin;
    _sensor_level = level;
    _sensor_epsilon = epsilon;

    Timer1.initialize(1000000);
    Timer1.attachInterrupt(_trigger_sensor);
    attachInterrupt(digitalPinToInterrupt(pin), _sensor_ISR, FALLING);
}

void ReflectiveSensor::reset() {
    _sensor_counter = 0;
}

int ReflectiveSensor::get_sensor() {
    return _sensor_reading;
}


int ReflectiveSensor::get_counter() {
    return _sensor_counter;
}

double ReflectiveSensor::get_angular_speed() {
    if(_sensor_time_since_last == 0) return 0;
    return (360.f / mNumMarkers) * 1000000.f / _sensor_time_since_last;
}
