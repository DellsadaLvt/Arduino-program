#include<Servo.h>
#include<Wire.h>
#include<I2Cdev.h>
#include<MPU6050.h>

MPU6050 sensor;
int16_t ax,ay,az;
int16_t gx,gy,gz;

Servo myservo;

int gtrihientai;
int giatritruoc;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.print(" khoi dong MPU");
  sensor.initialize();
 Serial.println(sensor.testConnection()? "sensor da duoc ket noi" :! " sensor chua ket noi");
  myservo.attach(9);
}

void loop()
{
  sensor.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);
  Serial.println(ay); Serial.print("\t");
  Serial.println(ax);
  gtrihientai = map (ay, -1700,1700,0,179);
  if (gtrihientai!= giatritruoc )
  {
     myservo.write(gtrihientai);
     giatritruoc = gtrihientai;
  }
  delay(1000);
}
