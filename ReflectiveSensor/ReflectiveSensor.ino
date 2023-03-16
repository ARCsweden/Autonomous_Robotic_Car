#include <ReflectiveSensor.h>

ReflectiveSensor sensor(3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int retval = sensor.get_reading();
  Serial.print(retval, DEC);
  Serial.print("\n");
}
