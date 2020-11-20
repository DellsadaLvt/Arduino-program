#include<mpu6050.h>
#include<Servo.h>

Servo myservo_1;
Servo myservo_2;

void setup()
{
  mpu6050();
  Serial.begin(9600);
  myservo_1.attach(9);
  myservo_2.attach(10);
  
  myservo_1.write(0);
  myservo_1.write(0);
  delay(2000);
}

void loop()
{
  int  giaTrix = map( get_accx(), -16384, 16380, -90, 90);
  int  giaTriy = map( get_accy(), -16384, 16380, -90, 90);
  int  giaTriz = map( get_accz(), -16384, 16380, -90, 90);

  int  giaTrix1 = map( get_gyrox(), -16384, 16380, -90, 90);
  int  giaTriy1 = map( get_gyroy(), -16384, 16380, -90, 90);
  int  giaTriz1 = map( get_gyroz(), -16384, 16380, -90, 90);

  int angle_1 = map(giaTrix, -90, 90, 0,179);
  Serial.println(giaTrix);
  int angle_2 = map(giaTriy, -90, 90, 0,179);
  Serial.println(giaTrix);
  
  myservo_1.write(angle_1);
  myservo_2.write(angle_2); 
  Serial.println(giaTriz);
 /* Serial.println(giaTriz);

  Serial.println(giaTrix1);
  Serial.println(giaTriy1);
  Serial.println(giaTriz1);*/
  Serial.println("/////////////");
  delay(1000);
}
