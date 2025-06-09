#include <Servo.h>

Servo servo_5;

const int pingUltra = 3;
const int buzzPin = 7;
const int tempsen = A1;
const int fan = 6;
const int pirSen = 10;
const int pirMotor = 9;
const int pirBulb = 2;

int temp = 0;
int pir = 0;

void setup() {
    Serial.begin(9600);
    servo_5.attach(5);
    pinMode(pingUltra, OUTPUT);
    pinMode(buzzPin, OUTPUT);
    pinMode(tempsen, INPUT);
    pinMode(fan, OUTPUT);
    pinMode(pirSen, INPUT);
    pinMode(pirMotor, OUTPUT);
    pinMode(pirBulb, OUTPUT);

} 

void loop() {
    
  long duration,distance;
  pinMode(pingUltra,OUTPUT);
  digitalWrite(pingUltra,LOW);
  delay(200);
  digitalWrite(pingUltra,HIGH);
  delay(500);
  digitalWrite(pingUltra,LOW);
 
  
  pinMode(pingUltra,INPUT);
  duration=pulseIn(pingUltra,HIGH);
  distance=microSecondsToCentimeters(duration);
  if(distance<30){
    servo_5.write(90);
    delay(2);
  }
  else{
    servo_5.write(0);
  }


    if (distance < 30) {
        servo_5.write(90);
    } else {
        servo_5.write(0);
    }

    temp = (-40 + 0.488155 * (analogRead(tempsen) - 20));
    delay(1000);

    if (temp >= 30) {
        digitalWrite(fan, HIGH);
        digitalWrite(buzzPin, HIGH);
    } else {
        digitalWrite(fan, LOW);
        digitalWrite(buzzPin, LOW);
    }

    pir = digitalRead(pirSen);
    if (pir == LOW) {
        digitalWrite(pirMotor, LOW);
        digitalWrite(pirBulb, LOW);
    } else {
        digitalWrite(pirMotor, HIGH);
        digitalWrite(pirBulb, HIGH);
    }

  
  
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("PIR Detection: ");
    Serial.println(pir);
    Serial.print("*******");
    delay(200);
}

long microSecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
}