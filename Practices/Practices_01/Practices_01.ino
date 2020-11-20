// khai bao thu vien
#include<LiquidCrystal.h>

// khoi tao chan
LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);
int i = 0;
char A[11] = "LE VAN THO";
void setup()
{
  lcd.begin(16, 2);
}

void loop()
{



  for ( i = 0; i < 16; i++)
  {

    lcd.setCursor(i, 0);
    for ( int j = 0; j < 10; j++)
    {
      lcd.print(A[j]);
      delay(100);
    }

    lcd.clear();
  }

  ////////


  
  while(i < 20)
  {
    i++;
    lcd.setCursor(3, 1);
    for ( int j = 0; j < 10; j++)
    {
      lcd.print(A[j]);
      delay(100);
    }

    lcd.clear();
  }

}
