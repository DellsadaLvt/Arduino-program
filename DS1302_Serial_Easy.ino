//Mã code của chương trình (Code for RTC DS1302)
// DS1302_Serial_Hard (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to use my DS1302-library to
// retrieve time- and date-date for you to manipulate.
//
// I assume you know how to connect the DS1302.
// DS1302:  CE pin ( RST)   -> Arduino Digital 5
//          I/O pin ( DAT)  -> Arduino Digital 4
//          SCLK pin  -> Arduino Digital 3

#include <DS1302.h>

// Init the DS1302
DS1302 rtc(5, 4, 3);

// Init a Time-data structure
Time t;
int led =12;
void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
 
  // Setup Serial connection
  Serial.begin(9600);

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(WEDNESDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 17, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(18, 06, 2019);   // Set the date to August 6th, 2010
  pinMode(led,OUTPUT);
}

void loop()
{
  // Get data from the DS1302
  t = rtc.getTime();
 
  // Send date over serial connection
  Serial.print(t.date, DEC);
  Serial.print("-");
  Serial.print(rtc.getMonthStr());
  Serial.print("-");
  Serial.print(t.year, DEC);
  Serial.println(":");
 
  // Send Day-of-Week and time
   Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");
  Serial.print(t.sec, DEC);
  Serial.println(":");

  // Send a divider for readability
  Serial.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");
  if(t.sec>0&&t.min==18&&t.hour==12)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  // Wait one second before repeating :)
  delay (1000);
}
