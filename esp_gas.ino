#include <WiFi.h>

#include <HTTPClient.h>

const char* ssid = "KERALAVISION";
const char* password = "1002003003";

const char* server = "https://api.thingspeak.com/update?api_key=3M3XUTOCEUWUMH6G&field1=0e";
const char* apiKey = "3M3XUTOCEUWUMH6G";

#define ANALOG_PIN 34
#define DIGITAL_PIN 25
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(ANALOG_PIN,INPUT);
  pinMode(DIGITAL_PIN,INPUT);
  pinMode(2,OUTPUT);

}
void senddata(int digital,float voltage){
  HTTPClient http;

  http.begin(server);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Prepare the data to be sent in the form of URL parameters
  String httpRequestData = "api_key=" + String(apiKey) + "&field1=" + String(voltage, 2) + "&field2=" + String(digital);

  // Send HTTP POST request and in return gets the response
  int httpResponseCode = http.POST(httpRequestData);

  // Print the response from ThingSpeak
  if (httpResponseCode > 0) { // it confirms data is sent
    Serial.print("Data sent to ThingSpeak. HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else { // data is not sent
    Serial.print("Error sending data to ThingSpeak. HTTP Response code: ");
    Serial.println(httpResponseCode);
  }

  // Close the HTTP connection
  http.end();
}


void loop() {
  // put your main code here, to run repeatedly:
  
  int digital=digitalRead(DIGITAL_PIN);
  int analog=analogRead(ANALOG_PIN);

  float voltage=(analog / 4095.0) * 3.3;
/*
  Serial.print("Analog Value  : ");
  Serial.print(analog);
  Serial.print(" | Voltage: "); 
  Serial.print(voltage, 2); 
  Serial.print("V");
  */
  Serial.print(" | Digital Output: "); 
  Serial.println(digital);
  if (digital == 0){
      digitalWrite(2,HIGH);
       
  }
  else
      digitalWrite(2,LOW);
  senddata(digital,voltage);
  
  delay(1000);
}
