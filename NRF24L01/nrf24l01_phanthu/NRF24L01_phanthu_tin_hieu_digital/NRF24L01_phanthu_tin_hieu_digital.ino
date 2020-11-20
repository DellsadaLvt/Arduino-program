// https://github.com/
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int button[1];

#define led 9

void setup()
{
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(led,OUTPUT);
}

void loop()
{
  if(radio.available())
  {
    bool done = false;
    while(!done)
    {
      done = radio.read(button,1);
      Serial.print(button[0]);
      if(button[0] = 111)
      {
        delay(10);
        digitalWrite(led,HIGH);
        delay(2000);
      }
      if(button[0] = 110)
      {
        digitalWrite(led,LOW);
      }
    }
  }
  else
  {
    Serial.print("khong ket noi:");
  }
}
