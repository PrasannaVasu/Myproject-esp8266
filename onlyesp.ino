#include <ESP8266WiFi.h> // ESP8266WiFi.h library
#include <DHT.h>
#include <ESP8266HTTPClient.h>
 

#define DHTPIN 2
#define DHTTYPE  DHT11

const char ssid[20]     = "Waiting";
const char password[20] = "dracule mihawk";
const char host[30] = "http://192.168.0.108";
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
  const int httpPort = 1337;
  if (!client.connect(host, httpPort)) {
    return;
  }

  String url = "/update/";
//  url+=writeAPIKey;
//  url+="field1=";
  url+=String(temperature);
  url+="/";
  url+=String(humidity);
  url+="/";
  url+=String(sm);
  url+="\r\n";
  
  // Request to the server
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://192.168.0.108:1337/storedata/12/34/45");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
  
    }
    else
     Serial.println("hai");
 
    http.end();   //Close connection
 
  }           
    delay(16000);
}

