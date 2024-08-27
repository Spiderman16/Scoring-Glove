
//                                                            MASTER CODE
//                                                           -------------



#include <SoftwareSerial.h>

SoftwareSerial BTSerial(8,9); // the RX and TX

// Foul setting
int foulButtonState = 0;
int lastFoulButtonState = 0; // To store the previous button state
int foulButtonPin = 2;


// Advantage setting
int advantageButtonState = 0;
int lastAdvantageButtonState = 0; // To store the previous button state
int advantageButtonPin = 3;


//Finger points setting

//Fingers Pins
const int thumbFlexPin = A0;
const int pointerFlexPin = A1;
const int middleFlexPin = A2;
const int indexFlexPin = A3;
const int pinkyFlexPin = A6;
//Fingers Value
int thumbValue = 0;
int pointerValue = 0;
int middleValue = 0;
int indexValue = 0;
int pinkyValue = 0;
int flexLimit = 900; //The limit when the flex sensors go over


void setup() {
  //Button Setup
  pinMode(foulButtonPin, INPUT);
  pinMode(advantageButtonPin, INPUT);
  BTSerial.begin(38400); // default for the bluetooth module 
  Serial.begin(9600);
  Serial.println("GO SCORE"); // Serial Communitcation

}

void loop()
{
  foul();
  advantage();
  point();
}

// FOUL BUTTON PROGRAM
void foul()
{
    foulButtonState = digitalRead(foulButtonPin);

    // Edge detection logic
    if (foulButtonState == HIGH && lastFoulButtonState == LOW)
    {
        BTSerial.write('A'); // Send the command to the slave
        Serial.println("Sent Command: A"); 
    }
    lastFoulButtonState = foulButtonState;
}
// ADVANTAGE BUTTON PROGRAM
void advantage()
{
    advantageButtonState = digitalRead(advantageButtonPin);

    // Edge detection logic
    if (advantageButtonState == HIGH && lastAdvantageButtonState == LOW)
    {
        BTSerial.write('B'); // Send the command to the slave
        Serial.println("Sent Command: B"); 
    }
    lastAdvantageButtonState = advantageButtonState;
}
//POINT FINGER PROGRAM
void point()
{
  //FIngers Value Analog
  thumbValue = analogRead(thumbFlexPin);
  indexValue = analogRead(indexFlexPin);
  pointerValue = analogRead(pointerFlexPin);
  middleValue = analogRead(middleFlexPin);
  pinkyValue = analogRead(pinkyFlexPin);
  
  if (pointerValue >= flexLimit && middleValue >= flexLimit && indexValue >= flexLimit && pinkyValue >= flexLimit && thumbValue >= flexLimit)
  {
    BTSerial.write('C'); // Send the command to the slave
    Serial.println("Sent Command: C"); 
  }
  else if (pointerValue >= flexLimit && middleValue >= flexLimit && indexValue >= flexLimit && pinkyValue >= flexLimit)
  {
    BTSerial.write('D'); // Send the command to the slave
    Serial.println("Sent Command: D"); 
  }
  else if (pointerValue >= flexLimit && middleValue >= flexLimit && indexValue >= flexLimit)
  {
    BTSerial.write('E'); // Send the command to the slave
    Serial.println("Sent Command: E"); 
  }
  else if (pointerValue >= flexLimit && middleValue >= flexLimit)
  {
    BTSerial.write('F'); // Send the command to the slave
    Serial.println("Sent Command: F"); 
  }
  else if (pointerValue >= flexLimit)
  {
    BTSerial.write('G'); // Send the command to the slave
    Serial.println("Sent Command: G"); 
  }

  delay(700); // Delay to prevent rapid point increments
}