#include <ReflectiveSensor.h>

// Parameter is pin number sensor is connected on
ReflectiveSensor sensor(3);

void setup() {
  // Open up a serial console
  Serial.begin(9600);
}

void loop() {
  // Read sensor value
  int retval = sensor.get_reading();
  // Print out sensor value as a decimal number
  Serial.print(retval, DEC);
  Serial.print("\n");
}
