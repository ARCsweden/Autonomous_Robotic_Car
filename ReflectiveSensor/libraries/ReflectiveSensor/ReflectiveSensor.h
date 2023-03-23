/* ARCSweden 2023 */

#ifndef __REFLECTIVE_SENSOR_H
#define __REFLECTIVE_SENSOR_H

#include "Arduino.h"

class ReflectiveSensor {
public:
    ReflectiveSensor(int pin, int level = 200, int epsilon = 20);

    enum class FSM {
        WHITE,
        BLACK,
    };

    // Calls get_reading internally
    void update(int diffTime);
    void reset();
    int get_counter() { return mCounter; }
    int get_sensor() { return mSensorValue; }

    float get_speed() { return mSpeed; }
private:
    int get_reading();

    int mPin;
    int mLevel;
    int mEpsilon;
    int mCounter{};

    int mSensorValue{};

    // PPS
    int mPulsesPerSec{};
    int mCurTime{};
    float mSpeed{};

    FSM mFsm = FSM::WHITE;
};

#endif //__REFLECTIVE_SENSOR_H
