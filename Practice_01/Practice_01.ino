// encoder vs lcd vs servo
//libraries
#include<Servo.h>
#include<LiquidCrystal.h>

// khai bao servo
Servo myservo;

// khai bao encoder
#define encoderPinA 2
#define encoderPinB 3
#define button 8

// khai bao lcd
LiquidCrystal lcd( 12, 11, 7, 6, 5, 4);

// khai bao bien
boolean tt = false;
//ENCODER
volatile int encoderPos = 0;
//unsigned int lastReportedPos = 1 // neu bo unsigned ra sao???????????
static boolean rotating = false;
//do toc do
unsigned int newposition;
unsigned int oldposition = 0;
unsigned int newtime;
unsigned int oldtime = 0;
float vantoc;
// cac bien dung cho chuong trinh ngat
boolean A_set = false;
boolean B_set = false;

void setup()
{
  // khoi tao lcd
  lcd.begin(16,2);
  lcd.setCursor( 3,0);
  lcd.print("LE VAN THO");
  lcd.clear();
  //KHOI TAO SERVO
  myservo.attach(10);

  // khoi tao encoder
  pinMode( encoderPinA, INPUT_PULLUP);// INPUT_PULLUP tuong tu INPUT nhung co them dientro
  pinMode( encoderPinB, INPUT_PULLUP);
  pinMode( button, INPUT_PULLUP);

  // CHAN ENCODER NGAT 0 CHAN D2
  attachInterrupt( 0, doEncoderA, CHANGE);
  // CHAN ENCODER NGAT 1 CHAN D3
  attachInterrupt( 1, doEncoderB, CHANGE);
}

// vong lap chinh
void loop()
{
  sw();
  if( !tt)
    Vantoc();
  else
  encoderPos =0;
}

// ham nut nhan
void sw()
{
  if( digitalRead(button) == LOW)
  {
    delay(20);
    if(digitalRead(button) == LOW)
      tt = !tt;
  }
}

// ngat 0
void doEncoderA()
{
  if(rotating)
    delay(1);
  if( digitalRead(encoderPinA) != A_set)
  {
    A_set =! A_set;
  if( A_set && !B_set)
    encoderPos++;
    rotating = false;
  }  
}

// ngat 1
void doEncoderB()
{
  if(rotating)
    delay(1);
  if( digitalRead(encoderPinB) != B_set)
  {
    B_set = ! B_set;
    if( B_set && !A_set)
      encoderPos--;
    rotating = false;
  }
}

// ham tinh van toc
void Vantoc()
{
  rotating = true;
  newposition = encoderPos;
  //
  lcd.setCursor(0, 0);
  lcd.print("Pos: ");
  lcd.print(encoderPos);
  newtime = millis();
  if( (unsigned int)(newtime - oldtime) ==100)
  {
    detachInterrupt(0);
    detachInterrupt(1);
    vantoc = ( newposition - oldposition)*60/20;
    lcd.setCursor(0, 1);
    lcd.print("VanToc: ");
    lcd.print(vantoc);
    oldposition = newposition;
    oldtime = newtime;
    //
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);
  }
}
