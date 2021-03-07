const int ledRed = 52;
const int ledYellow = 50;
const int ledGreen = 48;

const int buttonPin = 46;

const int interval = 1000;  // Time delay for led flashing on startup
unsigned long previousMillis = 0; // Time to compare with when flashing LED on startup

const int buzzer = 44;

// Shift register pins
const int dataIn = 36;
const int clk = 34;
const int latch = 32;

// Patterns for display characters
int datArray[16] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
  B01110111,  // A
  B01111100,  // b
  B00111001,  // C
  B01011110,  // d
  B01111001,  // E
  B01110001   // F
  };

void setup()
{
  //Light set
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzer, OUTPUT);

  // Shift register pins
  pinMode(dataIn, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  
  // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latch, LOW);
 
    // Shift out the bits
    shiftOut(dataIn, clk, MSBFIRST, B00000000);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latch, HIGH);
    
  unsigned long currentMillis = millis();
  
  
  while (digitalRead(buttonPin) == LOW) 
  { 
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // Flip LED state
        if (digitalRead(ledRed) == HIGH) {
            Serial.println("LED IS HIGH, CHANGING TO LOW");
            digitalWrite(ledRed, LOW);
        }
        else {
            Serial.println("LED IS LOW, CHANGING TO HIGH");
            digitalWrite(ledRed, HIGH);
        }
        // save the last time you blinked the LED
        previousMillis = currentMillis;
    }
  }
  Serial.println("EXIT SETUP");
}

void loop() {
  //Red LED is on for 15 seconds
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYellow, LOW);
  Serial.println("Red Light");

  for (int num = 0; num < 12; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latch, LOW);
 
    // Shift out the bits
    shiftOut(dataIn, clk, MSBFIRST, datArray[15 - num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latch, HIGH);
 
    delay(1000);
  }
  
  tone(buzzer, 1000);
  for (int num = 12; num < 15; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latch, LOW);
 
    // Shift out the bits
    shiftOut(dataIn, clk, MSBFIRST, datArray[15 - num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latch, HIGH);
 
    delay(1000);
  }
  noTone(buzzer);

  //Green LED is on for 15 seconds
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  Serial.println("Green Light");

  for (int num = 0; num < 12; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latch, LOW);
 
    // Shift out the bits
    shiftOut(dataIn, clk, MSBFIRST, datArray[15 - num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latch, HIGH);
 
    delay(1000);
  }
  
  tone(buzzer, 1000);
  for (int num = 12; num < 15; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latch, LOW);
 
    // Shift out the bits
    shiftOut(dataIn, clk, MSBFIRST, datArray[15 - num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latch, HIGH);
 
    delay(1000);
  }
  noTone(buzzer);
  
  //Yellow LED is on for 3 seconds
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, HIGH);
  Serial.println("Yellow Light");
  tone(buzzer, 1000);
  for (int num = 12; num < 15; num++)
  {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latch, LOW);
 
    // Shift out the bits
    shiftOut(dataIn, clk, MSBFIRST, datArray[15 - num]);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latch, HIGH);
 
    delay(1000);
  }
  noTone(buzzer);
 
}
