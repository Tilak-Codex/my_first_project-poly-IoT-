void setup()
{
  pinMode(27,OUTPUT);
}

void loop()
{
  tone(27,1000);
  delay(5000);
  noTone(27);
  delay(2000);
}

/*CONNECTION*/

// BLACK WIRE TO GND

// RED WIRE TO DGPIO
