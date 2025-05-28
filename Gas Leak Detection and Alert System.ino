//  It is an IoT-based embedded project designed to detect harmful gas leaks in real time using an MQ gas sensor interfaced with an ESP32 microcontroller. When dangerous gas levels are detected, the system automatically activates a PWM-controlled exhaust fan to ventilate the area and sends an email alert to the user using Wi-Fi connectivity. Additionally, it logs the analog gas concentration values and the digital status to the ThingSpeak cloud platform, enabling real-time remote monitoring. This system enhances safety in environments like kitchens, laboratories, and industrial areas by providing timely alerts and automated responses to gas leaks.

#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP_Mail_Client.h> 

const char* ssid = "SSID";
const char* password = "password";

const char* server = "https://api.thingspeak.com/update?api_key=3M3XUTOCEUWUMH6G&field1=0e";
const char* apiKey = "3M3XUTOCEUWUMH6G";

#define ANALOG_PIN 34
#define DIGITAL_PIN 25
#define ALERT_LED 2

//PWM settings
#define FAN_PIN 14  // GPIO connected to the gate of the MOSFET
#define PWM_FREQ 25000 // 25 kHz
#define PWM_CHANNEL 0
#define PWM_RESOLUTION 8 // 8-bit resolution (0-255)

// Email settings
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "rejinharidas123@gmail.com"         //  Gmail address
#define AUTHOR_PASSWORD "wavo owcf ragi ppaa"         // App password
#define RECIPIENT_EMAIL "rejinharidas999@gmail.com" // reciever email

// Email session
SMTPSession smtp;
ESP_Mail_Session session;
SMTP_Message message;

bool alertSent = false; // To avoid repeated emails

void setup() {
  Serial.begin(115200);

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION); // Configure PWM channel
  ledcAttachPin(FAN_PIN, PWM_CHANNEL);              // Attach GPIO to channel
  ledcWrite(PWM_CHANNEL,0);
  
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
  pinMode(ALERT_LED,OUTPUT);
  
  setupEmail();
}

void setupEmail() {
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  message.sender.name = "ESP32 Gas Detector";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "⚠️ Gas Leak Detected!";
  message.addRecipient("Home", RECIPIENT_EMAIL);
  message.text.content = "⚠️ ALERT: Dangerous gas levels have been detected . Contact the Emergency services!";
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
}

void sendEmailAlert() {
  if (!smtp.connect(&session)) {
    Serial.println("Failed to connect to SMTP server.");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.print("Error sending Email: ");
    Serial.println(smtp.errorReason());
  } else {
    Serial.println("✅ Alert email sent successfully.");
  }

  smtp.closeSession();
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
  
  int digital=digitalRead(DIGITAL_PIN);
  int analog=analogRead(ANALOG_PIN);

  float voltage=(analog / 4095.0) * 3.3;

  Serial.print("Analog Value  : ");
  Serial.print(analog);
  Serial.print(" | Voltage: "); 
  Serial.print(voltage, 2); 
  Serial.print("V");

  Serial.print(" | Digital Output: "); 
  Serial.println(digital);
  
  if (digital == 0){
      digitalWrite(2,HIGH);
      ledcWrite(PWM_CHANNEL, 254);     
      sendEmailAlert();
      alertSent = true;
      
  }
  else
  {
      digitalWrite(2,LOW);
      senddata(digital,voltage);
      alertSent = true;     
      for (int dutyCycle = 100; dutyCycle >= 50; dutyCycle -= 1) {
            ledcWrite(PWM_CHANNEL, dutyCycle);
            delay(100);
      }
  }
  delay(10000);
}
