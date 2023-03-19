#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "template_id"
#define BLYNK_DEVICE_NAME "device_name"

#include <BlynkSimpleEsp8266.h>

char auth[] = "auth";
BlynkTimer timer; 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WIFI_SSID";
char pass[] = "WIFI_PASS";

const int relay = 5;
//int temp;
void setup()
{
  // Debug console
  Serial.begin(11520);


// Set pin to OUTPUT LOW without going throught the OUTPUT HIGH state.
//digitalWrite(5, LOW); // do this first


pinMode(5, INPUT_PULLUP);
pinMode(5, OUTPUT);
//digitalWrite(5, LOW);

//
//pinMode(5, OUTPUT);
//digitalWrite(5, LOW);
  
//  pinMode(5, OUTPUT);
//  timer.setInterval(1000L, myTimer);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();

    // runs BlynkTimer
//  timer.run();

}

//void myTimer()
//{
//  temp = digitalRead(relay);
//  if ( temp == HIGH)
//  {
//    Blynk.virtualWrite(V3,temp);
//  }
//
//  else
//  {
//    Blynk.virtualWrite(V3,temp);
//  }
//  
// }



BLYNK_WRITE(V3) // Executes when the value of virtual pin 0 changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    Serial.print("HIGH");
    digitalWrite(5,HIGH);  // Set digital pin 2 HIGH
  }
  else
  {
    // execute this code if the switch widget is now OFF
    Serial.print("LOW");
    digitalWrite(5,LOW);  // Set digital pin 2 LOW    
  }
}
