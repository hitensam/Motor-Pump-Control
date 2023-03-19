//CREDITS : https://www.youtube.com/watch?v=MXbsUYxTj6o&t=549s (FLUID SENSOR CODE)
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "template_id"
#define BLYNK_DEVICE_NAME "device_name"

#include <BlynkSimpleEsp8266.h>

char auth[] = "auth";
BlynkTimer timer; 


#define SENSOR  D3
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
//boolean ledState = LOW;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "WIFI_SSID", "WIFI_PASS");
  pinMode(SENSOR, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

    timer.setInterval(1000L, myTimer);
}
void myTimer()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval)
  {
    pulse1Sec = pulseCount;
    pulseCount = 0;
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space
    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");
  }
    Blynk.virtualWrite(V4, int(totalMilliLitres / 1000));
    Blynk.virtualWrite(V2,int(flowRate));
}


void loop()
{

    
  // Runs all Blynk stuff
  Blynk.run(); 

  // runs BlynkTimer
  timer.run();
}
