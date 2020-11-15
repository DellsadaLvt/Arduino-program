/*
  Chương trình ĐẾM SỐ VÒNG QUAY BẰNG ENCODER QUAY
  Chương trình được viết bởi Huỳnh Minh Phú
  Các bạn có thể tham khảo video thứ 44 để hiểu rõ về việc kết nối
  Một encoder quay thông thường có 3 chân, nhìn từ mặt trước là A C B
  Quay theo chiều kim đồng hồ A(on)>B(on)>A(off)->B(off)
  Quay ngược chiều kim đồng hồ B(on)>A(on)>B(off)->A(off)
  Ngoài ra còn có một chân có nút nhấn và 2 chân nguồn
  Chương trình này hiện đo rất tốt khi chiều ngược chiều kim đồng hồ nhưng chiều cùng chiều kim đồng hồ thì đo chưa đạt
  Mình đã mất 3 ngày cho nghiên cứu này
  Vì công việc bận bịu nên mình đành tạm gác việc phát triển hướng này, mong các bạn sẽ bổ sung thêm
  Các bạn có thể đo thủ công bằng cách đổi 2 chân DT và CLK nếu muốn đo cùng chiều kim đồng hồ
  Hoặc 1 ngày nào đó khi có thời gian rãnh mình sẽ chỉnh việc đọc chiều quay cùng chiều kim đồng hồ cho chính xác
*/
#include<LiquidCrystal.h>
LiquidCrystal lcd( 12, 11, 7, 6, 5, 4);
// Cách nối các chân trên Encoder quay
#define  encoderPinA  2   // Tương ứng chân DT trên Encoder quay DT
#define  encoderPinB  3   // Tương ứng chân CLK trên Encoder quay CLK
#define sw 8  // chan SW
// Chân + nối nguồn 5V và chân GND nối cực âm
int led = 9;
byte tt = false;

// cac bien dung cho encoder
volatile unsigned int encoderPos = 0;  // Cho vị trí đầu bằng 0
// VOLATILE dung cho bien toan cuc trong chuong trinh ngat
unsigned int lastReportedPos = 1;   // Vị trí cuối bằng 1
//Đo tốc độ
unsigned int newposition;
unsigned int oldposition = 0;
unsigned long newtime;
unsigned long oldtime = 0;
int vantoc;
static boolean rotating = false;    // Quản lý debounce (giống như là chống nhiễu)
//static la bien tinh mo vua co tinh chat cua bien toan cuc vaf bien cuc bo//

// các biến cho trình phục vụ ngắt interrupt service routine vars
boolean A_set = false;
boolean B_set = false;


void setup() {
  lcd.begin(16,2);
  pinMode( sw,  INPUT_PULLUP);
  pinMode(encoderPinA, INPUT_PULLUP); // INPUT-PULLUP tương đương Mode INPUT và tự động nhận trạng thái HIGH hoặc LOW
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode( led, OUTPUT);
  digitalWrite(led, HIGH);
  // Chân encoder trên ngắt 0 (chân 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // Chân encoder trên ngắt 1 (chân 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin(9600);  // chuyển dữ liệu lên cổng Serial Port
}

// Vòng lặp chính, công việc được thực hiện bởi trình phục vụ ngắt
void loop() {
  rotating = true;  // Khởi động bộ debounce (có thể hiểu như bộ chống nhiễu)
  newtime = millis();
 
  newposition = encoderPos;
  //Serial.print(" encoderPos:");
  //Serial.println(encoderPos);
  if (newtime - oldtime == 1000) {
    detachInterrupt(0);   // chống ngắt
    detachInterrupt(1);   // chống ngắt
    int t = abs(newposition - oldposition);
    t = abs(t);
    Serial.print(" bien t:");
    Serial.println(t);
    vantoc =  t* 60 / 20; // vong/phut
    Serial.print("vantoc=");
    Serial.println(vantoc, DEC);
    Serial.print(" encoderPos:");
    Serial.println(encoderPos);
    lcd.setCursor(0,0);
    lcd.print("Pos     : ");
    ht_lcd((int)(encoderPos/1000), 0, 10);
    ht_lcd((int)(encoderPos%1000), 0, 13);
    lcd.setCursor(0,1);
    lcd.print("Velocity: ");
    ht_lcd((int)(vantoc/1000), 1,10);
    ht_lcd((int)(vantoc)%1000, 1,13);
    oldposition = newposition;
    
    
   oldtime = newtime;
   //Serial.print(" oldTime: ");
   //Serial.println(oldtime);
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);
  }
  /*if(digitalRead(sw == LOW))
    {
    encoderPos =0;
    }*/
  button();
}

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

///////////////
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

void ht_lcd(int m, char r, char c)
{ 
  int dv = m%10;
  int ch = m/10%10;
  int tr = m/100;
  lcd.setCursor( c, r);
  lcd.print(tr);
  lcd.print(ch);
  lcd.print(dv);
}

/*void tach_so( int m)
{
  int m1 = m/1000;
  int m2 = m%1000;
  lcd.setCursor(0,0);
  lcd.print("Pos: ");
  ht_lcd(m1, 0, 6);
  lcd.setCursor(0,1);
  lcd.print("Velo: ");
  ht_lcd(m2, 0, 7);*/
  
  
