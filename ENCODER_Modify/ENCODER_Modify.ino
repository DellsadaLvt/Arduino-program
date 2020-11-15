/* encoder vs lcd hien thi pos va velocity*/

#include<LiquidCrystal.h>
#include<Servo.h>

LiquidCrystal lcd( 12, 11, 7, 6, 5, 4);
Servo myservo;

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

// Cách nối các chân trên Encoder quay
#define  encoderPinA  2   // Tương ứng chân DT trên Encoder quay DT
#define  encoderPinB  3   // Tương ứng chân CLK trên Encoder quay CLK
#define sw 8  // chan SW
// Chân + nối nguồn 5V và chân GND nối cực âm

#define led 9
byte tt = false;

// cac bien dung cho encoder
volatile unsigned int encoderPos = 0;  // Cho vị trí đầu bằng 0
// VOLATILE dung cho bien toan cuc trong chuong trinh ngat
//Đo tốc độ
int newposition;
int oldposition = 0;
int vantoc;
static boolean rotating = false;    // Quản lý debounce (giống như là chống nhiễu)
//static la bien tinh mo vua co tinh chat cua bien toan cuc vaf bien cuc bo//

// các biến cho trình phục vụ ngắt interrupt service routine vars
boolean A_set = false;
boolean B_set = false;


void setup() 
{
  // LCD
  lcd.begin(16, 2);
  lcd.createChar(1, KhoangTrang);
  lcd.setCursor(3, 0);
  lcd.print("LE VAN THO");
  delay(3000);
  lcd.clear();
  // SERVO
  myservo.attach(10);
  myservo.write(0);
  //
  pinMode( sw,  INPUT_PULLUP);
  pinMode(encoderPinA, INPUT_PULLUP); // INPUT-PULLUP tương đương Mode INPUT và tự động nhận trạng thái HIGH hoặc LOW
  pinMode(encoderPinB, INPUT_PULLUP);
  // Chân encoder tr,ên ngắt 0 (chân 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // Chân encoder trên ngắt 1 (chân 3)
  attachInterrupt(1, doEncoderB, CHANGE);
    //
  pinMode( led, OUTPUT);
  digitalWrite(led, HIGH);
}

// Vòng lặp chính, công việc được thực hiện bởi trình phục vụ ngắt
void loop()
{
  Vantoc();
  servo();
  ht();
  button();
  delay(500);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Vantoc()
{
  rotating = true;  // Khởi động bộ debounce (có thể hiểu như bộ chống nhiễu)
  newposition = encoderPos;
  detachInterrupt(0);   // chống ngắt
  detachInterrupt(1);   // chống ngắt
  vantoc =  (newposition - oldposition) * 60 / 20; // vong/phut
  oldposition = newposition;
  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ht()
{
  if ( vantoc < 0)
  {
    vantoc = abs(vantoc);
    lcd.setCursor( 9, 1);
    lcd.print("-");
  }
  else
  {
    lcd.setCursor(9, 1);
    lcd.write(1);
  }
  lcd.setCursor(0, 0);
  lcd.print("Pos     : ");
  ht_lcd((int)(encoderPos / 1000), 0, 10);
  ht_lcd((int)(encoderPos % 1000), 0, 13);
  lcd.setCursor(0, 1);
  lcd.print("Velocity:");
  ht_lcd((int)(vantoc / 1000), 1, 10);
  ht_lcd((int)(vantoc) % 1000, 1, 13);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ngắt khi chuyển trạng thái của A
void doEncoderA() {
  // debounce
  if ( rotating )
    delay (1);  // Chờ 1 chút

  // Kiểm tra việc chuyển đổi trạng thái, xem có thật sự thay đổi trạng thái chưa
  if ( digitalRead(encoderPinA) != A_set )
  {
    // debounce một lần nữa
    A_set = !A_set;

    // Cộng 1 nếu có tín hiệu A rồi có tín hiệu B
    if ( A_set && !B_set )
      encoderPos += 1;

    rotating = false;  // Không cần debounce nữa cho đến khi được nhấn lần nữa
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ngắt khi thay đổi trạng thái ở B, tương tự như ở A
void doEncoderB() {
  if ( rotating ) delay (1);
  if ( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;
    //  Trừ 1 nếu B rồi đến A
    if ( B_set && !A_set )
      encoderPos -= 1;
    rotating = false;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void button()
{
  if (digitalRead(sw) == LOW)
  {
    delay(20);
    if ( digitalRead(sw) == LOW)
    {
      encoderPos = 0;
      tt = !tt;
      if ( tt == true)
        digitalWrite(led, HIGH);
      else
        digitalWrite( led, LOW);
      while ( digitalRead(sw) == LOW);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ht_lcd(int m, char r, char c)
{
  int dv = m % 10;
  int ch = m / 10 % 10;
  int tr = m / 100;
  lcd.setCursor( c, r);
  //if (tr == 0)
  lcd.print(tr);
  // else
  // lcd.write(1);
  lcd.print(ch);
  lcd.print(dv);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void servo()
{
  int Angle;
  if( encoderPos >=0 && encoderPos <=60)
    Angle = map( encoderPos,0,60, 0, 179);
  if(encoderPos >= 65475)
    Angle = map(65536- encoderPos,0,60, 0, 179);
    if( encoderPos > 60 && encoderPos < 65475)
      Angle = 0;
  myservo.write(Angle);
}
