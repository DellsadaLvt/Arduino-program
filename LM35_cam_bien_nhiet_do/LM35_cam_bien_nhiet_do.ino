/* lap trinh cam bien nhiet do LM35
 *  canh noi chan:
 *    Hai chân ngoài nối với nguồn 5V và GND; 
 *    chân giữa nối với chân analog
 */
int var,nhietdo;
void setup() {
  Serial.begin(9600);
}

void loop()
{
  var = analogRead(3);
  nhietdo = (var*5*1000/1024)/10;
  Serial.print(" nhietdo la:");
  Serial.print(nhietdo);
  Serial.println("cm");
  delay(1000);
}
