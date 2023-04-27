/* ARCSweden 2023 */

#ifndef __REFLECTIVE_SENSOR_H
#define __REFLECTIVE_SENSOR_H

#include "Arduino.h"

/* NOTE: Current implementation only supports one sensor per board */
class ReflectiveSensor {
public:
    ReflectiveSensor(int pin, int level = 200, int epsilon = 20, int num_markers = 25);
    void reset();

    int get_counter();
    int get_sensor();
    double get_angular_speed();

private:
    int mNumMarkers;
};

#endif //__REFLECTIVE_SENSOR_H
