/******************************* vARIABLES ************************/
String q;

/******************************* SETUP ***************************/
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}
/******************************* LOOP ***************************/
void loop()
{
  ReadSerialCommunitication();
  delay(500);
}
/*************************** SUBROUTINE ****************************/
void ReadSerialCommunitication( void )
{
  String readString;
  while (Serial.available())
  {
    delay(1);
    if (Serial.available() > 0)
    {
      char c = Serial.read();
      Serial.println(isControl(c));
      if( isControl(c))
        break;
      readString+=c;
      Serial.println(readString);
    }
  }
    q = readString;
    if( q== "on")
    digitalWrite(13, HIGH);
    if( q == "off")
    {
    digitalWrite(13, LOW);
    Serial.print((String)"h");
    }
    if( q =="send" )
      Serial.println("hi sen");
}
/******************/
void WriteSerialString( char x)
{
  Serial.println(x);
}
void serialPrint( void )
{
  Serial.print("serial available value: ");
  Serial.println(Serial.available());
}
