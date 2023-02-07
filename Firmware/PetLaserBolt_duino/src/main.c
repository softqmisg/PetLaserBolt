#include <Arduino.h>
#include <Servo.h>
//xdir=5~50;yir=5~35
#define SERVO1_PIN  PD3
#define SERVO2_PIN  PD2
#define LASER_PIN  PD4

#define SPEED_CH   2
#define RANDOMSEED_CH  5


#define MIN_X           15
#define MAX_X           35
#define MIN_Y           0
#define MAX_Y           40
#define MIN_DELAY       600
#define MAX_DELAY       3000
#define MIN_MOVMENTTIME 10
#define MAX_MOVMENTTIME 40
#define MIN_MOVMENT     5

#define SERVOSPEED_DELAY  10//5

Servo myservo1; 
Servo myservo2; 


/////////////////////////////////////////////////////////////////////////
uint8_t current_pos_x=MIN_X+(MAX_X-MIN_X)/2;
uint8_t current_pos_y=MIN_Y+(MAX_Y-MIN_Y)/2;

long random_value;

int x_new_position=MIN_X+(MAX_X-MIN_X)/2.0;
int y_new_position=MIN_Y+(MAX_Y-MIN_Y)/2.0;
int x_old_position;
int y_old_position;

long delay_s;
int pot;
//////////////////////////////////////////////////////////
void Servo_move(Servo s,int value)
{
  float current_pos;
  current_pos=(s==myservo1)?(float)current_pos_x:(float)current_pos_y;
  if(s==myservo1) current_pos_x=value;
  else  current_pos_y=value;

  int movement_time =random_minmax(MIN_MOVMENTTIME,MAX_MOVMENTTIME);

  float speed=((float)value-current_pos)/(float)movement_time;
  for(int t=0;t<movement_time;t++)
  {
      current_pos=(float)current_pos+speed;
      Servo_write(s,current_pos);// sets the servo position
      delay(SERVOSPEED_DELAY);    
  }  
}
// void Servo_move(Servo s,int value)
// {
//   int current_pos;
//   current_pos=(s==myservo1)?current_pos_x:current_pos_y;
//   if(s==myservo1) current_pos_x=value;
//   else  current_pos_y=value;


//   if(value>current_pos)
//   {
//     for(float i=(float)current_pos;i<=value;i+=0.5)
//     {
//         Servo_write(s,i);// sets the servo position
//         delay(SERVOSPEED_DELAY);    
//     }
//   }
//   else
//   {
//     for(float i=(float)current_pos;i>=value;i-=0.5)
//     {
//         Servo_write(s,i);// sets the servo position
//         delay(SERVOSPEED_DELAY);    
//     }
//   }
// }
/////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  myservo1=Servo_attach(PD3);
  myservo2=Servo_attach(PD2);

  Servo_write(myservo1,(int)x_new_position);// sets the servo position
  Servo_write(myservo2,(int)y_new_position);// sets the servo position
  x_old_position=x_new_position;
  y_old_position=y_new_position;

  randomSeed(analogRead(RANDOMSEED_CH));

  pinMode(LASER_PIN,OUTPUT);
  digitalWrite(LASER_PIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  // random_value=random(MAX_DELAY-MIN_DELAY);
  // delay_s=map(random_value,0,MAX_DELAY-MIN_DELAY,MIN_DELAY,MAX_DELAY);    
  pot=analogRead(SPEED_CH);
  delay_s=map(pot,0,1024,MIN_DELAY,MAX_DELAY);    


  x_new_position=(float)random_minmax(MIN_X+MIN_MOVMENT,MAX_X-MIN_MOVMENT);
  if((x_new_position>x_old_position)&& abs(x_new_position-x_old_position)<5)
    x_new_position=x_new_position+MIN_MOVMENT;
  else if((x_new_position<x_old_position)&& abs(x_new_position-x_old_position)<5)
    x_new_position=x_new_position-MIN_MOVMENT;

  y_new_position=(float)random_minmax(MIN_Y+MIN_MOVMENT,MAX_Y-MIN_MOVMENT);
  if((y_new_position>y_old_position)&& abs(y_new_position-y_old_position)<5)
    y_new_position=y_new_position+MIN_MOVMENT;
  else if((y_new_position<y_old_position)&& abs(y_new_position-y_old_position)<5)
    y_new_position=y_new_position-MIN_MOVMENT;

#if DEBUG
  if(x_new_position>(MAX_X+MIN_X)/2) 
    x_new_position=MAX_X;
  else 
    x_new_position=MIN_X;

  if(y_new_position>(MAX_Y+MIN_Y)/2) y_new_position=MAX_Y;
  else y_new_position=MIN_Y;
#endif

  Servo_move(myservo1,(int)x_new_position);// sets the servo position
  Servo_move(myservo2,(int)y_new_position);// sets the servo position
  delay(delay_s);

}