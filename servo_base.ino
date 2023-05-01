#include <Servo.h>
#include <SoftwareSerial.h>
Servo head_servo; 
Servo arm_L_servo; 
Servo arm_R_servo; 
Servo claw_L_servo; 
Servo claw_R_servo; 
Servo door;

int m1a = 2;
int m1b = 4;
int m2a = 7;
int m2b = 8;
int sp = 3;


int bluetoothRx = 12; 
int bluetoothTx = 13; 
float servopos;
int speed1;
SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);

void setup()
{
  head_servo.attach(A1);
  arm_L_servo.attach(A2); 
  arm_R_servo.attach(A3);
  claw_L_servo.attach(A4);
  claw_R_servo.attach(A5);
  door.attach(A0);

  pinMode(m1a, OUTPUT);  
  pinMode(m1b, OUTPUT);  
  pinMode(m2a, OUTPUT); 
  pinMode(m2b, OUTPUT);
  pinMode(sp, OUTPUT);

  
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop()
{
  if(bluetooth.available()>=2)
  {
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos;
    Serial.println(realservo);
    
    if (realservo >= 1000 && realservo <1180) {
      int servo1 = realservo;
      servo1 = map(servo1, 1000, 1180, 0, 180);
      head_servo.write(servo1);
      Serial.println("Servo 1 ON");
      delay(10);
    }
    if (realservo >= 2000 && realservo <2180) {
      int servo2 = realservo;
      servo2 = map(servo2, 2000, 2180, 0, 180);
      arm_L_servo.write(servo2);
      Serial.println("Servo 2 ON");
      delay(10);
    }
    if (realservo >= 3000 && realservo <3180) {
      int servo3 = realservo;
      servo3 = map(servo3, 3000, 3180, 0, 180);
      arm_R_servo.write(servo3);
      Serial.println("Servo 3 ON");
      delay(10);
    }
    if (realservo >= 4000 && realservo <4180) {
      int servo4 = realservo;
      servo4 = map(servo4, 4000, 4180, 0, 180);
      claw_L_servo.write(servo4);
      Serial.println("Servo 4 ON");
      delay(10);
    }
    if (realservo >= 5000 && realservo <5180) {
      int servo5 = realservo;
      servo5 = map(servo5, 5000, 5180, 0, 180);
      claw_R_servo.write(servo5);
      Serial.println("Servo 5 ON");
      delay(10);
    }

    if (realservo == 5400)
    {
      Serial.println("forward");
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW); 
      analogWrite(sp,speed1);       
    }
    if (realservo == 5600)
    {
      Serial.println("right");
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW);
      analogWrite(sp,speed1);
    }
    if (realservo == 5800)
    {
      Serial.println("backward");
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH); 
      analogWrite(sp,speed1);
    }
    if (realservo == 6000)
    {
      Serial.println("left");      
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH);
      analogWrite(sp,speed1);
    
    }
    if (realservo >=7000 && realservo <=7255)
    {
      speed1 = realservo;
      speed1 = map(speed1, 7000, 7255, 0, 255);
      Serial.println(speed1);
    }
    if (realservo == 6200)
    {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, LOW);
    }
    if (realservo == 7000) 
    {
      door.write(127);
    }
    if (realservo == 7200)
    {
      door.write(180);
    }
  }

}
