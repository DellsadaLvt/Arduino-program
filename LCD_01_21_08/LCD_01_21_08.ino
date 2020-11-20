//Thêm thư viện LiquitCrystal - nó có sẵn vì vậy bạn không cần cài thêm gì cả
#include <LiquidCrystal.h>
 
//Khởi tạo với các chân
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() {
  ​//Thông báo đây là LCD 160
  ​lcd.begin(16, 2);
  ​//In ra màn hình lcd dòng chữ Toi yeu Arduin
  ​lcd.print("Toi yeu Arduino!");
}
 
void loop() {
  ​// đặt con trỏ vào cột 0, dòng 
  ​// Lưu ý: dòng 1 là dòng thứ 2, lòng 0 là dòng thứ 1. Nôm na, nó đếm từ 0 từ không phải từ 
  ​lcd.setCursor(0, 1);
  ​// In ra dong ch
  ​lcd.print(" Arduino.VN");
}
