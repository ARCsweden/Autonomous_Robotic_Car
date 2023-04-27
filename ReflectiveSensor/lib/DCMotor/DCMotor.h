/* ARCSweden 2023 */

#ifndef __DC_MOTOR_H
#define __DC_MOTOR_H

class DCMotor {
public:
    DCMotor(int pin1, int pin2, int inhibit1, int inhibit2);

    /* Value between -255 and 255 */
    void setSpeed(int dir);
    void stop();

private:
    int mPin1{};
    int mPin2{};
};

#endif // __DC_MOTOR_H
