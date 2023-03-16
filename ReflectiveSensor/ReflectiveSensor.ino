const int SensorIn = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  int retval = getReflectiveReading();
  Serial.print(retval, DEC);
  Serial.print("\n");

}

int getReflectiveReading(){
  int uSecondCounter = 0;
  pinMode(SensorIn, OUTPUT);
  digitalWrite(SensorIn, HIGH);
  delayMicroseconds(20);
  pinMode(SensorIn, INPUT);
  while(digitalRead(SensorIn) == HIGH){
    uSecondCounter += 10;
    delayMicroseconds(10);
  }
  return uSecondCounter;
}
