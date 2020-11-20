#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11,7,6,5,4);

byte traitim[8]=    // [8]có 8 biến con ở trong
{
  B01010,
  B11111,       // bieu tuong trai tim
  B11111,
  B01110,         // 5 số là 5 ô trong hàng ngang
  B00100,
  B00000,
  B00000,
  B00000  
};


void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.clear();
 lcd.createChar(1,traitim);
}

void loop()
{
  lcd.setCursor(0,0);
 lcd.print("HELLO WORLD");
 lcd.setCursor(12,0);
 lcd.print(millis()/1000);
 
  lcd.setCursor(1,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(2,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(3,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(4,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(5,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(6,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(7,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(8,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(9,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(10,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(11,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(12,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(13,1);
  lcd.write(1);
  delay(200);
  lcd.setCursor(14,1);
  lcd.write(1);
  delay(200);
  lcd.clear();
}
