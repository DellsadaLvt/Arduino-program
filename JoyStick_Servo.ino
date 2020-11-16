// 576 --> 56 ---> 101
#include <Servo.h>
Servo myservo_01;
Servo myservo_02;
/////////////////////////
int x = A3;
int y = A2;
int sw = 2;
int led = 3;
byte tt =  false;

void setup()
{
  Serial.begin(9600);
  myservo_01.attach(4);
  myservo_02.attach(5);
  pinMode( sw, INPUT_PULLUP);
  pinMode( led, OUTPUT);
  digitalWrite( led, LOW);

}

void loop()
{
  /* Serial.print("sw:");
    Serial.println(digitalRead(sw));
    Serial.print("tt:");
    Serial.println(tt);
    delay(1000);*/
  /* if (digitalRead(sw) == 0)
    {
     digitalWrite( led, HIGH);
     tt = true;

    }*/
  /*Serial.print("sw:");
    Serial.println(digitalRead(sw));
    Serial.print("tt:");
    Serial.println(tt);
    delay(1000);*/
  button();
  while (  tt == true)
  {
    int cy = map( analogRead(y), 0, 1023, 0, 179);
    myservo_01.write(cy);
    int cx = map( analogRead(x), 0, 1023, 0, 179);
    myservo_02.write(cx);
    /*int gt_sw =  digitalRead(sw) ;
      if (gt_sw == 0)
      {
      digitalWrite( led, LOW);
      tt = false;

      }*/
    button();
    /* Serial.print("sw:");
      Serial.println(digitalRead(sw));
      Serial.print("tt:");
      Serial.println(tt);
      delay(1000);*/
  }

}

void button()
{
  if(digitalRead(sw) == LOW)
  {
    delay(20);
    if( digitalRead(sw) == LOW)
    {
      tt= !tt;
      if( tt == true)
      digitalWrite(led, HIGH);
      else
      digitalWrite( led, LOW);
      while( digitalRead(sw) == LOW);
    }
  }
}
