#include<SoftwareSerial.h>
SoftwareSerial SIM900A(3,4);// chan TX noi chan3 ,chan RX noi chan so 4
#define buttonsms 7 // chan tin hieu cam bien do am
#define led 9
char tempchar;
void setup()
{
  pinMode(buttonsms, INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  SIM900A.begin(9600);
}

void loop()
{
  if(digitalRead(buttonsms) == HIGH)// neu dat kho
  {
    delay(20);
    digitalWrite(led,HIGH);
    if(digitalRead(buttonsms) == HIGH)
    {
      goidien();
    }
  }
  if(digitalRead(buttonsms)== LOW)
  {
    digitalWrite(led,LOW);
  }
  
}

void goidien()
{
  SIM900A.println("ATD+84363713203;");
  delay(1500);
  SIM900A.println();
}
