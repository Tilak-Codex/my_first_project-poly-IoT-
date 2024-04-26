void setup()
{
  pinMode(4,INPUT_PULLUP);
  pinMode(2,OUTPUT);
  Serial.begin(115200);
}
void loop()
{
  int s;
  s=digitalRead(4);
  if(s==LOW)
  {
    Serial.println("pressed");
    digitalWrite(2,HIGH);
    
  }
  else
  {
      Serial.println("not pressed");
      digitalWrite(2,LOW);
   
  }
  
}
