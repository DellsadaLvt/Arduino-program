#define AN A3
int DO = 3;

void setup()
{
  Serial.begin(9600);
  pinMode( DO, INPUT);
  pinMode( 9, OUTPUT);
}

void loop()
{
  //int  DO_signal = digitalRead(DO);
  float AN_signal = analogRead(AN);
 Serial.print("analog: ");
  Serial.println(AN_signal);
 /* Serial.print(" digital:");
  Serial.println(DO_signal);
  if (DO_signal == HIGH)*/
   // Serial.println("ok");
//int  light = map( AN_signal, 0,1023, 0, 100);
///Serial.print(" light");
//Serial.println(light);
  analogWrite( 9, AN_signal);
  delay(69);
}
