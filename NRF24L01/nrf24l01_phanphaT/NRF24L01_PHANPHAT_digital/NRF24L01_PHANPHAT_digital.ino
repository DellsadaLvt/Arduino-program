#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int button[1];

#define var 3;

void setup()
{
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop()
{
  if( digitalRead(var) == HIGH)
  {
    button[0] = 111;
    radio.write(button,1);
  }
  if(digitalRead(var)== LOW)
  {
    button[0] = 110;
    radio.wtite(button,1);
  }
}
