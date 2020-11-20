
#include<LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7);
float mua;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(5,0);
  lcd.print(millis()/1000);
  pinMode(9, OUTPUT);
}

void loop()
{
  mua = analogRead(mua);
  if( mua > 200)
    {
      digitalWrite(9, HIGH);
    }
  else
    {
      digitalWrite(9, LOW);
    }
    delay (1000);
}
