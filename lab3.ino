int speedPin=5;
int dir1=4;
int dir2=3;
int mSpeed=125;
String speed_str = " 1/2 ";
String dir_str = "   C  ";

const int INTERRUPT_PIN = 2;

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <IRremote.h> //Make sure to install the library

RTC_DS1307 rtc;
DateTime now; 
DateTime last;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Configure IR remote
int IRpin=19;
IRrecv IR(IRpin);
decode_results cmd;
String myCom;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,HIGH);
  delay(25);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // enable IR
  IR.enableIRIn();
  
  attachInterrupt(0,buttonPressed,RISING);
  
  pinMode(speedPin,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);

  while (!Serial); // for Leonardo/Micro/Zero
   Serial.begin(9600);
   if (! rtc.begin()) {
     Serial.println("Couldn't find RTC");
     while (1);
   }
   
 //Set date
 //rtc.adjust(DateTime(2021, 4, 18, 16, 00, 0));
 
 if (! rtc.isrunning()) {
   Serial.println("RTC is NOT running!");
   // following line sets the RTC to the date & time this sketch was compiled
   // This line sets the RTC with an explicit date & time, for example to set
   // January 21, 2014 at 3am you would call:
   // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
 }
  analogWrite(speedPin,mSpeed); // write any speed updates
  DateTime now = rtc.now();
  last = now;
 
  Timer1.initialize(1000000); // every 1 second
  Timer1.attachInterrupt(update_lcd); 
 
}
 
void loop() {
  
  while (IR.decode(&cmd)==0){ 
    delay(10);
    if (digitalRead(dir1) == HIGH) {
      dir_str = "   CC ";
    }
    else {
      dir_str = "   C  ";
    }
  
    DateTime now = rtc.now();
    last = now;
  }
  delay(50);
  IR.resume();

  if (cmd.value==0xFF22DD){ // Slow down
    if (mSpeed == 250) {
      mSpeed = 175;
    }
    else if (mSpeed == 175) {
      mSpeed = 125;
    }
    else {
      mSpeed = 0;
    }
  }


  if (cmd.value==0xFF02FD){ // Change direction
    digitalWrite(dir1,!(digitalRead(dir1)));
    digitalWrite(dir2,!(digitalRead(dir2)));
  }

  
  if (cmd.value==0xFFC23D){ // Speed up
    if (mSpeed == 0) {
      mSpeed = 125;
    }
    else if (mSpeed == 125) {
      mSpeed = 175;
    }
    else {
      mSpeed = 250;
    }
  }

  analogWrite(speedPin,mSpeed); // write any speed updates
  
  if (mSpeed == 250) {
    speed_str = " Full";
  }
  else if (mSpeed == 125) {
    speed_str = " 1/2 ";
  }
  else if (mSpeed == 175) {
    speed_str = " 3/4 ";
  }
  else {
    speed_str = "  0  ";
  }
  


}

void buttonPressed() {
  digitalWrite(dir1,!(digitalRead(dir1)));
  digitalWrite(dir2,!(digitalRead(dir2)));
  }

void update_lcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  
  lcd.print(last.year());
  lcd.print('/');
  lcd.print(last.month());
  lcd.print('/');
  lcd.print(last.day(), DEC);
  lcd.print("  ");
  lcd.print(speed_str);
  
  lcd.setCursor(0, 1);
  lcd.print(last.hour(), DEC);
  lcd.print(':');
  lcd.print(last.minute(), DEC);
  lcd.print(':');
  lcd.print(last.second(), DEC);
  lcd.print("  ");
  lcd.print(dir_str);
}
