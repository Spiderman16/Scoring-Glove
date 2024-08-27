//                                                               SLAVE CODE
//                                                              -------------

#include <LCD-I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>

LCD_I2C lcd(0x27, 16, 2);
SoftwareSerial BTSerial(8,9); // RX and TX

//Foul vaule
int foulCount = 0;

//Advantage value
int advantageCount = 0;

//Point Value
int pointCount = 0;

char state = '\0'; // to declare to store multiple data

void setup() {
  //LCD Screen Setup
  lcd.begin(); 
  lcd.display();
  lcd.backlight();
  //advantage
  lcd.setCursor(0, 0);
  lcd.print("Ad:");
  lcd.setCursor(3,0);
  lcd.print(advantageCount);
  //foul 
  lcd.setCursor(0, 1);
  lcd.print("FL:");
  lcd.setCursor(3,1);
  lcd.print(foulCount);
  //points
  lcd.setCursor(7,0);
  lcd.print("Point:");
  lcd.setCursor(13,0);
  lcd.print(pointCount);
  
  BTSerial.begin(38400);
  Serial.begin(9600);
  Serial.println("Ready to revevie commmands...");
}

void loop() {
  if(BTSerial.available())
  {
    state = BTSerial.read(); // read the incoming data from the bluetooth
  }
  if(state == 'A')
  {
    foulCount += 1;
    lcd.setCursor(3,1);
    lcd.print(foulCount);
  }
  else if(state == 'B')
  {
    advantageCount += 1;
    lcd.setCursor(3,0);
    lcd.print(advantageCount);
  }
  else if(state == 'C')
  {
    pointCount += 0;
    lcd.setCursor(13,0);
    lcd.print(pointCount);
  }
  else if(state == 'D')
  {
    pointCount += 4;
    lcd.setCursor(13,0);
    lcd.print(pointCount);
  }
  else if(state == 'E')
  {
    pointCount += 3;
    lcd.setCursor(13,0);
    lcd.print(pointCount);
  }
  else if(state == 'F')
  {
    pointCount += 2;
    lcd.setCursor(13,0);
    lcd.print(pointCount);
  }
  else if(state == 'G')
  {
    pointCount += 1;
    lcd.setCursor(13,0);
    lcd.print(pointCount);
  }
}
