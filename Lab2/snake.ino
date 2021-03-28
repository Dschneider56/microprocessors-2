#include <Stdio.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int Xpin=A0;
int Ypin=A1;
int Spin=2;
int Xval;
int Yval;
int Sval;
int dt=200;
char data[32];
int incomingByte = 0;
const int buzzer = 8;

Vector norm;
// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;


// timer must be unsigned long otherwise millis value will overflow and loop gets stuck
unsigned long timer = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(Xpin,INPUT);
pinMode(Ypin,INPUT);
pinMode(Spin,INPUT);
digitalWrite(Spin,HIGH);
pinMode(buzzer, OUTPUT);

// Initialize MPU6050
while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
{
  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  delay(500);
}

}

void loop() {
 noTone(buzzer);
 Xval=analogRead(Xpin);
 Yval=analogRead(Ypin);
 Sval=digitalRead(Spin);

 // if no significant change made on joystick, check gyroscope
 if (Xval >= 500 && Xval <= 550 && Yval >= 500 && Yval <= 550 && Sval == 1) {
  // Read normalized values
  norm = mpu.readNormalizeAccel();

  // Calculate Pitch, and Roll
  pitch = -(atan2(norm.XAxis, sqrt(norm.YAxis*norm.YAxis + norm.ZAxis*norm.ZAxis))*180.0)/M_PI;
  roll = (atan2(norm.YAxis, norm.ZAxis)*180.0)/M_PI;

  // If any values above threshold, set Xval, Yval or Sval
  if (pitch > 20) {
    // set Xval to high value (turn right)
    Xval = 777;
    }
  else if (pitch < -20) {
     // set Xval to low value (turn left)
    Xval = -777;
    }
  else if (roll > 20) {
     // set Yval to High value (turn down)
    Yval = 777;
    }
  else if (roll < -20) {
     // set Yval to low value (turn up)
    Yval = -777;
    }

  // defined threshold for accelerometer to consider a "shake"
  if (norm.ZAxis < 3.1 || norm.ZAxis > 15) {
    Sval = 0;
    }
  }


 if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.println(incomingByte);

    if(incomingByte == 'E') {
      // start buzzer tone
      tone(buzzer, 1100);
    }
    else if(incomingByte == 'F') {
      // start buzzer golden tone
      tone(buzzer, 1400);
    }
  }

 // Only send data if a change is made to save performance
 if (Xval < 500 || Xval > 550 || Yval < 500 || Yval > 550 || Sval == 0) {
   sprintf(data, "Start,%d,%d,%d,End,", Xval, Yval, Sval);
   Serial.println(data);
 }

delay(200);


}
