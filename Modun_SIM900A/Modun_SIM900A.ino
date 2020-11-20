#include<SoftwareSerial.h>
SoftwareSerial SIM900A(3,4);// chan TX noi chan3 ,chan RX noi chan so 4
#define buttonsms 7 // chan tin hieu cam bien do am
String textSMS = "HET NUOC";// NOI DUNG TIN NHAN
char tempchar;
void setup()
{
  pinMode(buttonsms, INPUT);
  digitalWrite(buttonsms,LOW);
  Serial.begin(9600);
  SIM900A.begin(9600);
}

void loop()
{
  if(digitalRead(buttonsms) == HIGH)// neu dat kho
  {
    delay(20);
    if(digitalRead(buttonsms) == HIGH)
    {
      sendSMS(textSMS); // goi tin nhan
      Serial.print("goi");
      delay(30);
    }
  }
  
  
}

void sendSMS(String message)
{
  SIM900A.print("AT+CSCS=\"GSM\r\n");// lenh AT de goi tin nhan
  SIM900A_response(500);
  SIM900A.print("AT+CMGF=1\r\n");// bat dau goi tin
  SIM900A_response(500);
  SIM900A.print("AT+CMGS=\"+84363713203\"\r");// so dien thoai goi tin nhan
  SIM900A_response(500);
  SIM900A.print(message);// goi tin nhan
  SIM900A_response(500);
  SIM900A.print((char)26); //ket thuc lenh goi
  SIM900A_response(500);
}

void SIM900A_response(int time)
{
  int tnow = millis();
  while((millis()-tnow)< time)
  {
    if(SIM900A.available())
    {
      tempchar = (char)SIM900A.read();
      if(tempchar == '\r')
      {
        Serial.print("/R/");
        
      }
      else if(tempchar == '\n')
      {
        Serial.print("/N/");
      }
      else Serial.print(tempchar);
    }
  }
}
