#include <Servo.h>

const int WATER_SENSOR_PIN = 2;
const int LED_PIN = 8;
const int BUZZER_PIN = 11;
const int SERVO_PIN = 9;

Servo myServo;

bool waterState = false;

void setup() {
  Serial.begin(9600);

  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0);
}

void loop() {

  int sensorValue = digitalRead(WATER_SENSOR_PIN);

  if (sensorValue == HIGH && waterState == false) {

    // Water detected 
    waterState = true;

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("Water Detected!");
    Serial.println("Servo: 0 -> 90");

    for (int angle = 0; angle <= 90; angle++) {
      myServo.write(angle);
      delay(15);
    }
  }

  else if (sensorValue == LOW && waterState == true) {

    // Water removed 
    waterState = false;

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("Water Removed!");
    Serial.println("Servo: 90 -> 0");

    for (int angle = 90; angle >= 0; angle--) {
      myServo.write(angle);
      delay(15);
    }
  }

  delay(100);
}