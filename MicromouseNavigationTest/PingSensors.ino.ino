#include "Arduino.h"
#include "PID.h"
#include "Utility.h"
#include "Sensors.h" 

float duration, cm;

void pingFrontSensor(void)
{
  pinMode(frontSensorPin, OUTPUT);
  digitalWrite(frontSensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontSensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(frontSensorPin, LOW);

  pinMode(frontSensorPin, INPUT);
  duration = pulseIn(frontSensorPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm - Front Sensor");
  Serial.println();
  delay(100);
}

void pingBackSensor(void)
{
  pinMode(backSensorPin, OUTPUT);
  digitalWrite(backSensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(backSensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(backSensorPin, LOW);

  pinMode(backSensorPin, INPUT);
  duration = pulseIn(backSensorPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm - Back Sensor");
  Serial.println();
  delay(100);
  return;
}

float microsecondsToCentimeters(float microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
