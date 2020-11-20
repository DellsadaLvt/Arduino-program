#define tinhieu 3
#define led 6

void setup()
{
  pinMode(tinhieu, INPUT);
  pinMode(led, OUTPUT);
  
}

void loop()
{
  int laytinhieu = digitalRead(tinhieu);
  if( laytinhieu == HIGH)   // nếu laytinhieu bằng 1 gặp màu đen
    {
      digitalWrite(led, HIGH);
      delay(1000);
    }
   else
   {
    digitalWrite(led, LOW);   // gặp màu trắng
    
   }
   delay(1500);
}
