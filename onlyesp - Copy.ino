#include <ESP8266WiFi.h> // ESP8266WiFi.h library
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE  DHT11

const char ssid[20]     = "vj";
const char password[20] = "12345679";
const char host[30] = "192.168.43.20";
const char writeAPIKey[30] = "M3F8SR09YXXTVJ1G";

DHT dht(DHTPIN, DHTTYPE, 15);

void setup() {
  // Initialize sensor
 dht.begin();
  delay(1000);

//  Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();
 float sm = analogRead(0);

  if (isnan(humidity) || isnan(temperature)|| isnan(sm)) {
    return;
  }

// make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }

  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temperature);
  url+="&field2=";
  url+=String(humidity);
  url+="&field3=";
  url+=String(sm);
  url+="\r\n";
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");            
    delay(16000);
}
