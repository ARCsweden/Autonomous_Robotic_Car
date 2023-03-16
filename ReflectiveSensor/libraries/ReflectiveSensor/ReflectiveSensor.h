/* ARCSweden 2023 */

#ifndef __REFLECTIVE_SENSOR_H
#define __REFLECTIVE_SENSOR_H

#include "Arduino.h"

class ReflectiveSensor {
public:
    ReflectiveSensor(int pin);

    int get_reading();
private:
    int mPin;
};

#endif //__REFLECTIVE_SENSOR_H
