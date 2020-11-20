#include<LiquidCrystal.h>

LiquidCrystal lcd( 12,11,7,6,5,4);

byte KhoangTrang[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup()
{
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(1, KhoangTrang);
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print(" dsjk");
  lcd.setCursor(9,1);
  lcd.write(1);
  delay(500);
  lcd.write(1);
  delay(500);
  lcd.write(1);
  delay(500);
  
}
