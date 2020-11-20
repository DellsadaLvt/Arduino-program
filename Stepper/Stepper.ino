#include<Stepper.h>

int in1 = 8;
int in2 = 9;
int in3 = 10;
int in4 = 11;

Stepper mystepper(64,in1,in2,in3,in4);    // 64 so buoc;

void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // quay 1 vong theo mot huong
  Serial.print("clock wwise");
  mystepper.setSpeed(240);
  mystepper.step(2048);             // lay 64 buoc nhan 32; 32 la banh rang nho quay 32 vong thi dc quay 1 vong
  delay(1000);
  // quay nguoc chieu counter clockwise het mot vong
  Serial.println("counter clockwise");
  mystepper.setSpeed(200);
  mystepper.step(-2048);
  delay(1500);
}
