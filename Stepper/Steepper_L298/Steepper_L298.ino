#include<Stepper.h>
//Khai báo các chân khi kết nối mạch H với Arduino
//Chân in1 nối với chân số 8 của Arduino, in2 nối chân 9, in3 nối chân 10, in4 nối chân 11
int in1=8;
int in2=9;
int in3=10;
int in4=11;
//Khai báo số bước trên 1 vòng và các chân
Stepper myStepper(200,in1,in2,in3,in4);
void setup()
{
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  //Giao tiếp với cổng serial:
  Serial.begin(9600);
}
void loop(){
  //Quay 2 vòng theo 1 hướng:
  Serial.println("cung chieu");
  myStepper.setSpeed(150);
  myStepper.step(400);//Quay 1 vòng
  delay(2000);
  //Quay ngược chiều lại
  Serial.println("nguoc chieu");
  myStepper.setSpeed(60);
  myStepper.step(-400);//Quay ngược lại 1 vòng
  delay(1000);
   }
