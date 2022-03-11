#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "DHT.h"

#define DHTPIN 14

#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "510Gangz";
const char *password = "510510510";

String ip = "192.168.43.168";

String server = "http://" + ip + ":3000/";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000;

// led

const int output26 = 26;
const int output27 = 27;

void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200);

    pinMode(output26, OUTPUT);
    pinMode(output27, OUTPUT);

    digitalWrite(output26, LOW);
    digitalWrite(output27, LOW);

    WiFi.begin(ssid, password);
    Serial.print("");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println(F("DHT11 started!"));
    dht.begin();
}


String httpGETRequest(String url) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    String payload = "{}";
    if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        payload = http.getString();
        http.end();
        return payload;
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        http.end();
        return "";
    }
}

String httpPUTRequest(String url, String payload) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.PUT(payload);
    String response = "{}";
    if (httpCode > 0) {
        Serial.printf("[HTTP] PUT... code: %d\n", httpCode);
        response = http.getString();
        http.end();
        return response;
    } else {
        Serial.printf("[HTTP] PUT... failed, error: %s\n", http.errorToString(httpCode).c_str());
        http.end();
        return "";
    }
}

void loop() {
    // put your main code here, to run repeatedly:
    if (millis() - lastTime > timerDelay) {
        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        float h = dht.readHumidity();
        // Read temperature as Celsius (the default)
        float t = dht.readTemperature();

        // Check if any reads failed and exit early (to try again).
        if (isnan(h) || isnan(t)) {
            Serial.println(F("Failed to read from DHT sensor!"));
        } else {
//            Serial.print(F("Humidity: "));
//            Serial.print(h);
//            Serial.print(F("%  Temperature: "));
//            Serial.print(t);
//            Serial.print(F("°C "));
            String payload = "{\"temp\": " + String(t) + ", \"humd\": " + String(h) + "}";
            String response = httpPUTRequest(server + "dht11", payload);
//            Serial.println(response);   
        }
        
        if (WiFi.status() == WL_CONNECTED) {
            String serverLed = httpGETRequest(server + "led");
//            Serial.println(serverLed);
            JSONVar myObject = JSON.parse(serverLed);
            if (JSON.typeof(myObject) == "undefined") {
                Serial.println("Error");
            } else {
                JSONVar statusLed26 = myObject[0];
                JSONVar statusLed27 = myObject[1];
                if (statusLed26.hasOwnProperty("status")) {
                    bool status = (int)statusLed26["status"];
//                    Serial.println((int)statusLed26["status"] == 1);
                    if (status) {
                        Serial.println("Led 26 ON");
                        digitalWrite(output26, HIGH);
                    } else {
                        Serial.println("Led 26 OFF");
                        digitalWrite(output26, LOW);
                    }
                }
                if (statusLed27.hasOwnProperty("status")) {
                    bool status = (int)statusLed27["status"];
//                    Serial.println((int)statusLed27["status"] == 1);
                    if (status) {
                        Serial.println("Led 27 ON");
                        digitalWrite(output27, HIGH);
                    } else {
                        Serial.println("Led 27 OFF");
                        digitalWrite(output27, LOW);
                    }
                }
            }
            
        } else {
            Serial.println("Not connected to WiFi");
        }
        lastTime = millis();
    }
}
