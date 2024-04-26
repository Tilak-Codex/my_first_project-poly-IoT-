#include <NewPing.h>
#include <WiFi.h> 
#include <ThingESP.h>

#include <TinyGPSPlus.h>
#define GPS_BAUDRATE 115200

TinyGPSPlus gps;
int s;
ThingESP32 thing("Tilak", "fetchloc", "neo6mgps");

unsigned long previousMillis = 0;
const long INTERVAL = 6000;  

//Defining pins for ultrasonic sensor 1.
#define TRIGGER_PIN1 25
#define ECHO_PIN1 33    
#define MAX_DISTANCE1 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//Defining pins for ultrasonic sensor 2.
#define TRIGGER_PIN2 18
#define ECHO_PIN2 19 
#define MAX_DISTANCE2 100

#define buzzer_pin1 14
#define buzzer_pin2 12

#define vibration_pin1 27
#define vibration_pin2 26

// NewPing setup of pins and maximum distance.
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE1); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2);

void setup() 
{
  Serial.begin(115200); 
  Serial2.begin(GPS_BAUDRATE);
  Serial.println(F("ESP32 - GPS module"));
  pinMode(4,INPUT_PULLUP);
  pinMode(2,OUTPUT);
  thing.SetWiFi("Tilak", "12345678");
  thing.initDevice();
   
  pinMode(buzzer_pin1,OUTPUT);
  pinMode(buzzer_pin2,OUTPUT);
  pinMode(vibration_pin1,OUTPUT);
  pinMode(vibration_pin2,OUTPUT);
}

String HandleResponse(String query)
{

 float h = gps.location.lat();
  // Read temperature as Celsius (the default)
  float t = gps.location.lng();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  Serial.println("longitude :");
  Serial.print(t);
  Serial.println("latitude");
  Serial.print(h);
  String humid = "latidue: " + String(h) + "\n";
  String temp = "longitude: " + String(t) + "\n";

  
  if (query == "location") {
   
    return "The user it at \n https://www.google.co.in/maps/place/KONGUNADU+POLYTECHNIC+COLLEGE/@11.0147879,78.2975865,17z/data=!4m14!1m7!3m6!1s0x3baa49fb6ae5125f:0x2a4b08e171565e03!2sKONGUNADU+POLYTECHNIC+COLLEGE!8m2!3d11.0147879!4d78.3001614!16s%2Fg%2F11gd__1w1p!3m5!1s0x3baa49fb6ae5125f:0x2a4b08e171565e03!8m2!3d11.0147879!4d78.3001614!16s%2Fg%2F11gd__1w1p?entry=ttu \n";
  }

  else if (query == "latitude") {
  
    return humid;
  }
 
  else return "Your query was invalid..";
  
}

void loop() 
{
  if (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      if (gps.location.isValid()) {
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat());

        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng());

        Serial.print(F("- altitude: "));
        if (gps.altitude.isValid())
          Serial.println(gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.kmph());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.print(F("- GPS date&time: "));
      if (gps.date.isValid() && gps.time.isValid()) {
        Serial.print(gps.date.year());
        Serial.print(F("-"));
        Serial.print(gps.date.month());
        Serial.print(F("-"));
        Serial.print(gps.date.day());
        Serial.print(F(" "));
        Serial.print(gps.time.hour());
        Serial.print(F(":"));
        Serial.print(gps.time.minute());
        Serial.print(F(":"));
        Serial.println(gps.time.second());
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  s=digitalRead(4);
  if(s==LOW)
  {
    Serial.println("pressed");
    thing.sendMsg("+919585198687","Hey!,There is an emergency\nThe user is at:\n https://www.google.co.in/maps/place/KONGUNADU+POLYTECHNIC+COLLEGE/@11.0147879,78.2975865,17z/data=!4m14!1m7!3m6!1s0x3baa49fb6ae5125f:0x2a4b08e171565e03!2sKONGUNADU+POLYTECHNIC+COLLEGE!8m2!3d11.0147879!4d78.3001614!16s%2Fg%2F11gd__1w1p!3m5!1s0x3baa49fb6ae5125f:0x2a4b08e171565e03!8m2!3d11.0147879!4d78.3001614!16s%2Fg%2F11gd__1w1p?entry=ttu");
    thing.sendMsg("+919585198687","https://www.google.co.in/maps/place/KONGUNADU+POLYTECHNIC+COLLEGE/@11.0147879,78.2975865,17z/data=!4m14!1m7!3m6!1s0x3baa49fb6ae5125f:0x2a4b08e171565e03!2sKONGUNADU+POLYTECHNIC+COLLEGE!8m2!3d11.0147879!4d78.3001614!16s%2Fg%2F11gd__1w1p!3m5!1s0x3baa49fb6ae5125f:0x2a4b08e171565e03!8m2!3d11.0147879!4d78.3001614!16s%2Fg%2F11gd__1w1p?entry=ttu");
    digitalWrite(2,HIGH);
  }
  thing.Handle();
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int distance1 = sonar1.ping_cm(); // Send ping, get distance in centimeters.
  unsigned int distance2 = sonar2.ping_cm();
  if (distance1 <= 100 && distance1 >=5) // If distance is 100 cm or less
  { 
     digitalWrite(buzzer_pin1,HIGH);
     digitalWrite(vibration_pin1,HIGH);
  }
  else
  {
    digitalWrite(buzzer_pin1,LOW);  
    digitalWrite(vibration_pin1,LOW);
  }
   if (distance2 <= 100 && distance2 >=5) // If distance is 100 cm or less
  { 
     digitalWrite(buzzer_pin2,HIGH);
     digitalWrite(vibration_pin2,HIGH);
  }
  else
  {
    digitalWrite(buzzer_pin2,LOW);   
    digitalWrite(vibration_pin2,LOW);
  }
}
