//LẬP TRÌNH CẢM BIẾN LỰC VỚI ARDUINO
//NGƯỜI VIẾT: HUỲNH MINH PHÚ
//Download thư viện tại: https://github.com/bogde/HX711
 #include <HX711.h>//Sử dụng thư viện HX711
int led=12;
//Cách nối chân:
//Chân GND nối chân GND trên Arduino, chân VCC nối chân 5V trên Arduino
// Chân DT nối chân A1
//Chân SCK nối chân A0
//Đọc file READ ME trong file thư viện để hiểu hơn về thư viện, module HX711, cách thiết lập các thông số
 
HX711 scale(A1, A0);                        // Thông số độ lợi (gain) được bỏ qua, giá trị độ lợi mặc định được sử dụng trong thư viện là 128;
 
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  Serial.println("Thu HX711");
 
  Serial.println("Truoc khi set ti le:");
  Serial.print("doc: \t\t");
  Serial.println(scale.read());                            // In ra màn hình giá trị thô đọc được từ bộ chuyển đổi ADC
 
  Serial.print("doc gia tri trung binh: \t\t");
  Serial.println(scale.read_average(20));          // In ra màn hình giá trị trung bình của 20 lần đọc từ ADC
 
  Serial.print("lay gia tri: \t\t");
  Serial.println(scale.get_value(5));                 // In ra màn hình giá trị trung bình của 5 lần đọc từ bộ ADC trừ đi trọng lượng bao bì (trọng lượng bao bì tại thời điểm này chưa được thiết lập)
 
  Serial.print("lay don vi: \t\t");
  Serial.println(scale.get_units(5), 1);  // In ra màn hình giá trị trung bình của 5 lần đọc từ bộ ADC trừ trọng lượng bao bì (chưa được thiết lập) chia cho thông số tỉ lệ (chưa được thiết lập)
 
  scale.set_scale(624.28);                      
  // Thiết lập tỉ lệ, giá trị này đạt được bằng việc calib (thiết lập lại chuẩn) tỉ lệ với trọng số đã biết; xin đọc thêm phần README để hiểu rõ vấn đề;
  //bằng cách để cân trống rồi xóa giá trị trong ngoặc sau đó upload chương trình
  // ví dụ cục nặng 50g chạy chương trình lấy giá trị trung bình chia cho 50
  scale.tare();   // tính khối lượng bao bì                                             // Hàm này dùng để thiết lập trạng thái ban đầu có bao bì. Nếu ban đầu có bao bì thì chỉ cần đặt bao bì lên và khởi động, hàm sẽ bỏ qua giá trị bao bì
 
  Serial.println("Sau khi thiet lap ti le:");
 
  Serial.print("doc : \t\t");
  Serial.println(scale.read());                 // In ra màn hình một giá trị thô từ bộ ADC
 
  Serial.print("doc gia tri trung binh : \t\t"); //Đọc giá trị trung bình
  Serial.println(scale.read_average(20));       // In giá trị trung bình của bộ ADC trong 20 lần đọc
 
  Serial.print("lay gia tri: \t\t");      
  Serial.println(scale.get_value(5));                 // In ra màn hình giá trị trung bình của bộ ADC trừ khối lượng bao bì, được thiết lập trong hàm tare()
 
  Serial.print("lay don vi: \t\t");
  Serial.println(scale.get_units(5), 1);        // In giá trị trung bình của 5 lần đọc từ bộ ADC trừ khối lượng bao bì, chia thông số tỉ lệ với hàm set_scale
                                                           
  Serial.println();
  Serial.println("DOC GIA TRI:");//Bắt đầu quá trình đọc giá trị thật
}
 
void loop() {
  Serial.print("doc 1 lan:\t");
  Serial.print(scale.get_units(), 1);//một lần đọc đọc 1 giá trị
  Serial.print("\t| trung binh 10 lan doc:\t");
  Serial.println(scale.get_units(10), 1);//In ra màn hình giá trị trung bình của 10 lần đọc
if((scale.get_units(10)>60)&&(scale.get_units(10)<120))//Phần này tác giả thêm vào cho đèn led tắt mở trong một giới hạn từ 60g đến 120g
  {
    digitalWrite(led,HIGH);
  }
  else //nằm ngoài khoảng trên thì led tắt
  {
    digitalWrite(led,LOW);
  }
  scale.power_down();                                 // Đặt bộ ADC vào chế độ ngủ
 
  delay(2000);
  scale.power_up();                            //Khởi động lại bộ ADC
}
