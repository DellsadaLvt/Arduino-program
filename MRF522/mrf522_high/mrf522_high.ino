//Sài Gòn, ngày 11/05/2019
//Thân tặng cộng đồng, mã code free
//Người viết: Thạc Sĩ Huỳnh Minh Phú, chủ cửa hàng: http://www.ktphuhung.com
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
byte AAuthorized[6] = {0xE9, 0x5F, 0xCC, 0x54, 0xFF, 0xFF};//Mã thẻ đã lập trình để nhận diện
          //,{0xD4, 0x4B, 0xAA, 0x72, 0xFF, 0xFF}
                             /*,{0x10, 0x14, 0x39, 0x2E, 0xFF, 0xFF, }*/  /*Ví dụ về cách thêm các thẻ cần được nhận diện*/                            

                          //Thử thêm vào
byte BAuthorized[6] = {0xD4, 0x4B, 0xAA, 0x72, 0xFF, 0xFF};
                             /*,{0x10, 0x14, 0x39, 0x2E, 0xFF, 0xFF, }*/  /*Ví dụ về cách thêm các thẻ cần được nhận diện*/                            
                                                    
void printSerial(byte *serial);
boolean isSame(byte *key, byte *serial);
boolean isAuthorized(byte *serial);



void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];
  boolean Opening = false;
  digitalWrite(ledPinOpen, Opening);
  digitalWrite(ledPinClosed, !Opening);
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);
    if(isAAuthorized(serial))
    { 
      printSerial(serial);
      Serial.print(": Minh Phu. ");
      Serial.println("Ma the dung");
      Opening = true;
    }
    else if(isBAuthorized(serial))
    {
     printSerial(serial); 
     Serial.print(": Khach VIP. ");
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
    delay(2000);
  }//if (status == MI_OK)

  delay(500);

}//void loop()

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

boolean isAAuthorized(byte *serial)
{
     if(isSame(serial, AAuthorized))
        return true;
    else
   return false;
}
//Thử
boolean isBAuthorized(byte *serial)
{
    if(isSame(serial, BAuthorized))
        return true;
    else
   return false;
}
//
void printSerial(byte *serial)
{
        Serial.print("The:");
    for (int i = 0; i < 4; i++) {
      Serial.print(serial[i], HEX);
      Serial.print(" ");
    }    
}
 
