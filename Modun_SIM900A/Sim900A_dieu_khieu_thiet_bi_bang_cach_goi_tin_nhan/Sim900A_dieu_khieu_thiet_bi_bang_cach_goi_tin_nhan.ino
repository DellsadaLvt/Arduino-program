//Sài Gòn ngày 13/3/2019, thân tặng code sim900A điều khiển bằng tin nhắn
//CHƯƠNG TRÌNH ĐIỀU KHIỂN THIẾT BỊ QUA TIN NHẮN ĐIỆN THOẠI DÙNG SIM900A MINI VERSION
//NGƯỜI VIẾT: HUỲNH MINH PHÚ
//CHÂN TX NỐI VỚI CHÃN 2, CHÂM RX NỐI VỚI CHÂN 3
//SẢN PHẨM NÀY ĐƯỢC BÁN TẠI: www.ktphuhung.com
//CHƯƠNG TRÌNH NÀY SỬ DỤNG THƯ VIỆN TẠI LINK:https://github.com/MarcoMartines/GSM-GPRS-GPS-Shield
#include "SIM900.h"
 
#include <SoftwareSerial.h>
 
#include "sms.h"
 
SMSGSM sms;
 
char number[]="+84xxxxxx";//số điện thoại của người nhắn tin, với xxxx là số điện thoại của người nhận tin nhắn, nhớ bỏ số 0.
char message[180];
 
char pos;
 
char *p;
 
void setup()
 
{
 
 Serial.begin(9600);
 Serial.begin(9600);
 pinMode(12,OUTPUT);
 digitalWrite(12,HIGH);
 if (gsm.begin(2400))
 
   Serial.println("\nstatus=READY");
 
 else Serial.println("\nstatus=IDLE");
 
};
 
void loop()
 
{
 
 pos=sms.IsSMSPresent(SMS_UNREAD);
 
 Serial.println((int)pos);
 
 if((int)pos>0&&(int)pos<=20){
 
   Serial.print("NUOVO MESSAGGIO, POS=");
 
   Serial.println((int)pos);
 
   message[0]='\0';
 
   sms.GetSMS((int)pos,number,message,180);
 
   p=strstr(message,"t");//cú pháp tin nhắn sẽ bắt đầu là t, các bạn có thể thay đổi
 //Các bạn nhắn tLEDON thì sẽ mở LED, các ban có thể tự đặt mật mã riêng cho mình
   if(p){
 
     Serial.println("PSWD OK");
 
     p=strstr(message,"ON");//kiểm tra từ sau chữ "t", nếu sau chữ "t" là LEDON thì mở led
 
     if(p){
 
       Serial.println("LED ON");
 
       digitalWrite(12,HIGH);
 
     }
 
     else{
 
       p=strstr(message,"OFF");//Nếu câu lệnh là tLEDOFF thì tắt led
 
       if(p){
 
         Serial.println("LED OFF");
 
         digitalWrite(12,LOW);
 
       }
 
     }
 
   }
 
   sms.DeleteSMS((int)pos);//xóa tin nhắn vừa nhận để tránh tràn bộ nhớ thẻ sim
 
 }
 
 delay(1000);
 
}
