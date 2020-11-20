/* CHƯƠNG TRÌNH ĐỌC THẺ TỪ
Chương trình này được sưu tầm từ nhiều nguồn tài liệu tiếng Anh trên internet, được dịch và diễn giải thêm bởi Huỳnh Minh Phú.
*/
#include <MFRC522.h>
//Lấy thư viện của bộ thẻ từ của RC522 tại https://github.com/ljos/MFRC522
#include <SPI.h>

/*
Cách nối dây:
Thứ tự SPI   Chân trên UNO  Chân trên Mega2560        Chân trên Leonardo
1 (NSS) SAD (SS)   10               53                            10
2       SCK        13               52                            SCK1 (1 on ICPS header)
3       MOSI       11               51                            MOSI1 (1 on ICPS header)
4       MISO       12               50                            MISO1 (1 on ICPS header)
5       IRQ        *                *                             *
6       GND       GND               GND                           GND
7       RST        5                ?                             Reset
8      +3.3V (VCC) 3V3              3V3                           3.3V
Dấu * nghĩa là không cần thiết, tức IRQ không cần nối dây

*/
#define SAD 10
#define RST 5
MFRC522 nfc(SAD, RST);


#define ledPinOpen    2//Điều khiển led tại chân 2 sáng khi thẻ từ đưa vào được nhận diện
#define ledPinClosed  3//Điều khiển led tại chân 3 sáng khi thẻ từ đưa vào chưa được nhận điện


void setup() {
  pinMode(ledPinOpen  , OUTPUT);   
  pinMode(ledPinClosed, OUTPUT);   
  SPI.begin();
  Serial.begin(9600); //baurate là 115200 hoặc 9600
  Serial.println("Dang tim chip MFRC522.");
  nfc.begin();
  byte version = nfc.getFirmwareVersion();
  if (! version) {
    Serial.print("Khong thay chip MFRC522.");
    while(1); //halt
  }

  Serial.print("Da thay chip MFRC522 ");
  Serial.print("Firmware phien ban. 0x");
  Serial.print(version, HEX);
  Serial.println(".");
}

#define AUTHORIZED_COUNT 1 /*Xác định tổng số lượng thẻ mà ta đã lập trình nhận diện, nếu ta có 2 thì nhập 2,  */
byte Authorized[AUTHORIZED_COUNT][6] = {
            {0x62, 0x99, 0x7C, 0x6F, 0xFF, 0xFF}//Mã thẻ đã lập trình để nhận diện
          //,{0xD4, 0x4B, 0xAA, 0x72, 0xFF, 0xFF}
                             /*,{0x10, 0x14, 0x39, 0x2E, 0xFF, 0xFF, }*/  /*Ví dụ về cách thêm các thẻ cần được nhận diện*/                            
                          };
void printSerial(byte *serial);
boolean isSame(byte *key, byte *serial);
boolean isAuthorized(byte *serial);



void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];
  boolean Opening = false;  // bang LOW tat
  digitalWrite(ledPinOpen, Opening);
  digitalWrite(ledPinClosed, !Opening);
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);
    
    if(isAuthorized(serial))
    { 
      printSerial(serial);
      Serial.println("Ma the dung");
      Opening = true;
    }
    else
    { 
      printSerial(serial);
      Serial.println("Ma the KHONG dung");
      Opening = false;
    }
    
    nfc.haltTag();
    digitalWrite(ledPinOpen, Opening);
    digitalWrite(ledPinClosed, !Opening);
    delay(10000);
  }//if (status == MI_OK)

  delay(500);

}
//void loop()

boolean isSame(byte *key, byte *serial)
{
    for (int i = 0; i < 4; i++) {
      if (key[i] != serial[i])
      { 
        return false; 
      }
    }
    
    return true;

}

boolean isAuthorized(byte *serial)
{
    for(int i = 0; i<AUTHORIZED_COUNT; i++)//vòng lập tương ứng với số thẻ.
    {
      if(isSame(serial, Authorized[i]))
        return true;
    }
   return false;
}
//
void printSerial(byte *serial)
{
        Serial.print("The:");
    for (int i = 0; i < 4; i++) 
    {
      Serial.print(serial[i], HEX);
      Serial.print(" ");
    }    
}
