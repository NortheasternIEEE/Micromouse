int sensorPinFront = A4;    // select the input for sensor
int sensorPinBack = A3;    // select the input for sensor

void setup() {
  Serial.begin(9600);
  pinMode(sensorPinFront, INPUT);
  pinMode(sensorPinBack, INPUT);
}

void loop() {
  // read value from the sensor with :
   int sensorValueFront = !digitalRead(sensorPinFront);
   int sensorValueBack = !digitalRead(sensorPinBack);
   Serial.print("Front Sensor: ");
   Serial.print(sensorValueFront); //Front 
   Serial.print("\t");
   Serial.print("Back Sensor: ");
   Serial.println(sensorValueBack);
   delay(100);
}

