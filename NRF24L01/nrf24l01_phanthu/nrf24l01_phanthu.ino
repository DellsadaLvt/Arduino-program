//Phần thu
//Lập trình thu phát tính hiệu Analog qua bộ WiFiNRF24L01
//Phần này thể hiện cách thu phát tín hiệu Analog giữa các bo Arduino
//Người sưu tầm, chỉnh sửa: Huỳnh Minh Phú
//Website tham khảo thêm: http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>
Servo myservo;//Sử dụng RC Servo
const uint64_t pipe = 0xE8E8F0F0E1LL; // Định nghĩa đường truyền dữ liệu
RF24 radio(9,10); // Tạo bộ phát sóng Radio
//Khai báo biến
int joystick[2];  // Tạo mảng 2 phần tử cho việc đọc dữ liệu từ Joystick
int A;
 
void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Bo thu Nrf24L01 bat dau hoat dong");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  myservo.attach(6);
}
void loop()  
{
  if ( radio.available() )
  {
    // Đọc dữ liệu nhận được
    bool done = false;
    while (!done)
    {
      // Đọc dữ liệu
      done = radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.print(joystick[0]);//In dữ liệu theo phương X
      Serial.print(" Y = ");     
      Serial.println(joystick[1]);//In dữ liệu theo phương Y
      A=map(joystick[0],0,1023,0,179);//Quy đổi giá trị đọc được về góc từ 0 đến 180 độ
      Serial.print("gia tri A: ");
      Serial.println(A);//In giá trị quy đổi
      myservo.write(A);//Đưa giá trị góc vào để điều khiển RC servo
      delay(100);//Delay để hiện lên màn hình dễ nhìn
    }
  }
  else//Nếu không kết nối được
  {   
      Serial.println("Khong ket noi duoc");//Hiển thị không kết nối được.
}
}
