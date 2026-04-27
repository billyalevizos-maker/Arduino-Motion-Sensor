#include <Servo.h>

// pin connections
const int servoPin = 8 ;
const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 3;


float duration;
float distanceCM;


Servo servo1;


void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  servo1.attach(servoPin); // attaches servo on servoPin to output

}



void loop() {


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // send trigger signal
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

 

  duration = pulseIn(echoPin, HIGH); // waits for the pin to go from LOW to HIGH
  // return pulse duration in microseconds
  // stops timing when pin goes back LOW
  distanceCM = (duration * 0.034) / 2; // 343 m/s = 0.034 cm/microseconds

  // print distance
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println(" cm");

  delay(100); // slows down printing so i can actually read it

  // map distance (cm) to servo position (deg)
  int servoPos = map(distanceCM, 2, 30, 0, 180);
  servo1.write(servoPos);

  if (distanceCM > 0 && distanceCM < 10) {
    digitalWrite(buzzerPin, HIGH); // on (happens if distance is less than 10cm and bigger than 0cm)
  } else {
    digitalWrite(buzzerPin, LOW); // off
  }

}