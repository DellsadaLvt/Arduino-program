#include <VirtualWire.h> // khai báo thư viện VirtualWire

void setup()
{
  Serial.begin(9600);// giao tiếp Serial với baudrate 9600
  Serial.println("Ready.........");
  vw_set_ptt_inverted(true);// yêu cầu cho RF link modules
  vw_setup(1024);// cài đặt tốc độ truyền tín hiệu
  vw_set_tx_pin(8);// cài đặt chân digital để phát tín hiệu
}

void loop()
{
  char text[20] = "";// khai báo string dạng array
  byte i = 0;
  while (Serial.available() == 0)
  {
    // nothing
  }
  while (Serial.available() > 0)
  {
    char ch = Serial.read();
    text[i] = ch;
    i++;
    delay(5);
  }
  Serial.print("sent: ");
  Serial.println(text);
  vw_send((byte *)text, sizeof(text));// gửi tín hiệu đi
  vw_wait_tx();
  delay(100);
}
