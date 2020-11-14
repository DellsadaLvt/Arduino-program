// cảm biến siêu âm

#define trigger 4
#define echo 5


void setup()
{
 Serial.begin(9600);
  pinMode( trigger, OUTPUT);
  pinMode( echo, INPUT);
}

void loop()
{
  float s,t;
  digitalWrite( trigger, HIGH);
  delayMicroseconds(1000);
  digitalWrite( trigger, LOW);
  delayMicroseconds(1000);
  t = pulseIn( echo, HIGH);
  s = 0.0344*t/2;
  Serial.println(s);
}