#include <NewPing.h>

//For ultrasonic sensor1
#define TRIGGER_PIN_1 25 
#define ECHO_PIN_1 33
#define buzzer_PIN1 14
#define vibrant_PIN1 27

//For ultrasonic sensor2
#define TRIGGER_PIN_2 18  
#define ECHO_PIN_2 19 
#define buzzer_PIN2 12
#define vibrant_PIN2 26

#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup for sensor 1
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup for sensor 2

void setup() 
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see distance readings.
  pinMode(buzzer_PIN1, OUTPUT);
  pinMode(vibrant_PIN1, OUTPUT);
  pinMode(buzzer_PIN2, OUTPUT);
  pinMode(vibrant_PIN2, OUTPUT);
  
}

void loop() 
{
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  // Measure distance for sensor 1
  unsigned int distance1 = sonar1.ping_cm(); // Send ping, get distance in centimeters for sensor 1
  if (distance1 <= 100 && distance1 >= 5) 
  {   // If distance is between 5cm and 100cm
    digitalWrite(buzzer_PIN1, HIGH);
    digitalWrite(vibrant_PIN1, HIGH);
    Serial.print("Sensor 1: Object detected at ");
    Serial.print(distance1);
    Serial.println(" cm");
  } 
  else 
  {
     digitalWrite(buzzer_PIN1, LOW);
    digitalWrite(vibrant_PIN1, LOW);
  }
  
  // Measure distance for sensor 2
  unsigned int distance2 = sonar2.ping_cm(); // Send ping, get distance in centimeters for sensor 2
  if (distance2 <= 100 && distance2 >= 5) 
  {   // If distance is between 5cm and 100cm
    digitalWrite(buzzer_PIN2, HIGH);
    digitalWrite(vibrant_PIN2, HIGH);  
    Serial.print("Sensor 2: Object detected at ");
    Serial.print(distance2);
    Serial.println(" cm");
  } 
  else 
  {
   digitalWrite(buzzer_PIN2, LOW);
    digitalWrite(vibrant_PIN2, LOW);  
  }
}
