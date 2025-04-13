#include <Servo.h>

int const servoPin = 9;
int const yellowLEDpin = 4;
int const redLEDpin = 3;
int const buttonPin = 2;

int const photoResPin = A0; 
int const PotPin = A1;

int servoPos = 0;
int photoResValue = 0;
int PotValue = 0;

float const slope = 45./256.; // this slope is used to transform 0-1023 analog signal into 0-180 degrees for the servo

bool bottunState = LOW;
bool memory = HIGH;

int programMode = 1;

int const wait = 20;

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
  pinMode(redLEDpin, OUTPUT);
  pinMode(yellowLEDpin, OUTPUT);
  pinMode(photoResPin, INPUT);
  pinMode(PotPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  PotValue = analogRead(PotPin);
  photoResValue = analogRead(photoResPin);
  bottunState = digitalRead(buttonPin);
  // ====================================================
  // over here we handle the program mode either potentiometer mode = 1 or photoresistor mode = 2. 

  if (bottunState == HIGH && memory == HIGH){
    if (programMode == 2){
      programMode = 1;
    }else {
      programMode = 2;
    }
    memory = LOW;
    delay(wait);                   // this delay is added to handle the debouncing effect caused by the physical button.
  } else if (bottunState == LOW && memory == LOW) {
    memory = HIGH;                 // this memeory bit is added to handle multiple commands at very short time intervals.
  }
  //=======================================================
  // over here we impliment the system modes

  if (programMode == 1){ // if we are in mode 1 write the angle of the servo using the potentiometer readings and turn on the LED assigned to the potentiometer
    servoPos = slope*PotValue;
    digitalWrite(redLEDpin, HIGH);
    digitalWrite(yellowLEDpin, LOW);
  }else if (programMode == 2){ // if we are in mode 2 write the angle of the servo using the photoresistor readings and turn on the LED assigned to the photoresistor
    servoPos = slope*photoResValue;
    digitalWrite(redLEDpin, LOW);
    digitalWrite(yellowLEDpin, HIGH);
  }
  myServo.write(servoPos);
}
