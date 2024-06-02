
#include <Servo.h>

#define MOTION_SENSOR_PIN  D7 
#define SERVO_PIN          D1 

Servo servo; 

int angle = 0;         
int prev_motion_state;   
int motion_state; r

void setup() {
  Serial.begin(9600);                
  pinMode(MOTION_SENSOR_PIN, INPUT); 
  servo.attach(SERVO_PIN);           

  servo.write(angle);
  motion_state = digitalRead(MOTION_SENSOR_PIN);
}

void loop() {
  prev_motion_state    = motion_state;             
  motion_state = digitalRead(MOTION_SENSOR_PIN); 

  if (motion_state == LOW && prev_motion_state == HIGH) { 
    Serial.println("Motion detected!, rotating servo motor to 90°");
    servo.write(180);
  } else if (motion_state == HIGH && prev_motion_state == LOW) { 
    Serial.println("Motion stopped!, rotating servo motor to 0°");
    servo.write(0);
  }
}