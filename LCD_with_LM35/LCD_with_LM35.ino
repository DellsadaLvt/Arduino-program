//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

float var = 3;

void setup()
{
 lcd.begin(16, 2);              // start the library
}

void loop()
{
// lay nhiet do
 var = analogRead(var);
 var = (var*5*1000/1024)/10;
// hien thi nhiet do tren LCD 
 lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up
 lcd.setCursor( 0,0);
 lcd.print(" nhiet do la:");
 lcd.setCursor(13,0);
 lcd.print(var);
 lcd.print(" do C");
 delay(1000);

}
