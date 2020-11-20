//Phần phát, các bạn copy rồi lưu lại một file sau đó nạp vào mạch phát nhé.
//Phần phát của module NRF24L01
//Mã code được sưu tầm và chỉnh sửa bởi Huỳnh Minh Phú
//Website tham khảo: http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
//Vui lòng xem video lập trình vi điều khiển 74 để hiểu rõ hơn về cách kết nối bộ NRF24L01 với Arduino
//Xem thêm video 72 để hiểu cách kết nối bộ Joystick với Arduino
//Trong clip này thì chân X của Joystick nối với chân A0, chân Y của Joystick nối với chân A1
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define JOYSTICK_X A0//Chân X của Joystick nối với chân A0
#define JOYSTICK_Y A1//Chân Y nối với chân A1
const uint64_t pipe = 0xE8E8F0F0E1LL; // Định nghĩa đường truyền
RF24 radio(9,10); // Tạo bộ phát Radio
int joystick[2];  // Khai báo mảng 2 phần tử để đọc tín giá trị củ bộ Joystick

void setup()   
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}
void loop()  
{
  joystick[0] = analogRead(JOYSTICK_X);//Đọc tính hiệu theo trục X
  joystick[1] = analogRead(JOYSTICK_Y);//Đọc tín hiệu theo trục Y
  
  radio.write( joystick, sizeof(joystick) );//Nhập giá trị đọc được để gửi
}
