#include<LiquidCrystal.h>
#include<DS1302.h>
/// init the lcd
LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);
// initial the ds1302
DS1302 rtc( 8, 7, 6);
// initial a date-time
Time t;

void setup()
{
  //set up lcd
  lcd.begin( 16, 2);
  lcd.setCursor(1, 0);
  lcd.print("LE VAN THO");
  delay(1000);
  lcd.clear();
  // set up ds1302
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(FRIDAY);
  rtc.setTime(16, 39, 38);
  rtc.setDate(28, 8, 2020);
  // set serial
  Serial.begin(9600);
}

void loop()
{
  lcd_pro();
  serial();
  delay(1000);
}
/// lcd_rtc program
void lcd_pro()
{
  // get data time
  t = rtc.getTime();
  // display on lcd
  lcd.setCursor(0, 0);
  lcd.print(t.date);
  lcd.print("/");
  lcd.print(rtc.getMonthStr());
  lcd.print("/");
  lcd.print(t.year);
  // get hour
  lcd.setCursor(2, 1);
  lcd.print(t.hour, DEC);
  lcd.print(':');
  lcd.print(t.min, DEC);
  lcd.print(':');
  lcd.print(t.sec, DEC);
  ///////////
  if( t.sec == 00)
    lcd.clear();
  
}

void serial()
{
  Serial.print(t.date);
  Serial.print(rtc.getMonthStr());
  Serial.println(t.year);
  ///
  Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");
  Serial.println(t.sec);
}
