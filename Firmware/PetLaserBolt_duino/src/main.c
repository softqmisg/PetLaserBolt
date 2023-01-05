#include <Arduino.h>
#include <Servo.h>
//xdir=5~50;yir=5~35
#define SERVO1_PIN  PD3
#define SERVO2_PIN  PD2
#define LASER_PIN  PD4

#define SPEED_CH   2
#define RANDOMSEED_CH  5


#define MIN_X 5
#define MAX_X 50
#define MIN_Y 5
#define MAX_Y 35
#define MIN_DELAY 600
#define MAX_DELAY 3000

#define SERVOSPEED_DELAY  15

Servo myservo1; 
Servo myservo2; 
uint8_t current_pos_s1=MIN_X;
uint8_t current_pos_s2=MIN_Y;

long random_value;

void Servo_move(Servo s,int value,int index)
{
  int current_pos;
  current_pos=(index==1)?current_pos_s1:current_pos_s2;
  if(index==1) current_pos_s1=value;
  else  current_pos_s2=value;

  if(value>current_pos)
  {
    for(int i=current_pos;i<=value;i++)
    {
        Servo_write(s,i);// sets the servo position
        delay(SERVOSPEED_DELAY);    
    }
  }
  else
  {
    for(int i=current_pos;i>=value;i--)
    {
        Servo_write(s,i);// sets the servo position
        delay(SERVOSPEED_DELAY);    
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  myservo1=Servo_attach(PD3);
  myservo2=Servo_attach(PD2);

  Servo_write(myservo1,MIN_X);// sets the servo position
  Servo_write(myservo2,MIN_Y);// sets the servo position
  randomSeed(analogRead(RANDOMSEED_CH));

  delay(5000);   
}
int degree1,degree2;
long delay_s;
int pot;
void loop() {
  // put your main code here, to run repeatedly:
  pinMode(LASER_PIN,OUTPUT);
  digitalWrite(LASER_PIN,HIGH);
  random_value=random(MAX_X-MIN_X);
  degree1=map(random_value,0,MAX_X-MIN_X,MIN_X,MAX_X);
  random_value=random(MAX_Y-MIN_Y);
  degree2=map(random_value,0,MAX_Y-MIN_Y,MIN_Y,MAX_Y); 

  // random_value=random(MAX_DELAY-MIN_DELAY);
  // delay_s=map(random_value,0,MAX_DELAY-MIN_DELAY,MIN_DELAY,MAX_DELAY);    
  pot=analogRead(SPEED_CH);
  delay_s=map(pot,0,1024,MIN_DELAY,MAX_DELAY);    

  Servo_move(myservo1,(int)degree1,1);// sets the servo position
  Servo_move(myservo2,(int)degree2,2);// sets the servo position
  delay(delay_s);

}