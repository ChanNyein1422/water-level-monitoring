#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

// Wi-Fi credentials
const char* ssid = "Conor_Kim";
const char* password = "Neolde142";

const char* serverName = "http://172.20.10.3:3000/save_data";


// Time variables
time_t now;
struct tm timeinfo;


void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  configTime(0, 0, "pool.ntp.org"); // Get UTC time
  while (!time(nullptr)) {
    Serial.println("Waiting for time sync...");
    delay(1000);
  }
  connectToWifi(ssid, password);
}

long readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2; // Calculate distance in cm
}

String getCurrentTime() {
  time(&now);
  localtime_r(&now, &timeinfo);
  char timeStr[30];
  strftime(timeStr, sizeof(timeStr), "%FT%TZ", &timeinfo);  // ISO 8601 format
  return String(timeStr);
}
void loop() {
  // Read the ultrasonic distance and get the current timestamp
  long distance = readUltrasonicDistance();
  String timestamp = getCurrentTime();

  sendToServer(timestamp,distance);
  delay(600);//delay 0.6 seconds
 
}

void connectToWifi(char* ssid, char* password)
{
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print ESP32's local IP address
  
}

void sendToServer(String timestamp, long distance) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(serverName);
    http.begin(url);

    // Set the content type to application/json
    http.addHeader("Content-Type", "application/json");

    // Prepare the JSON data
    String payload = "{\"timestamp\":\"" + timestamp + "\",\"distance\":" + distance + "}";

    // Send the POST request with JSON data
    int httpResponseCode = http.POST(payload);
  Serial.print("HTTP Response Code: ");
  Serial.println(httpResponseCode);
    if (httpResponseCode == 200) {
      Serial.println("Data sent successfully.");
    } else {
      Serial.println("Error sending data.");
    }

    // Close the connection
    http.end();
  } else {
    Serial.println("WiFi not connected.");
  }
}
