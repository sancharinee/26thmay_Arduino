#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define led1            D7
#define led2            D6
#define led3            D5

#define WLAN_SSID       "your_ssid"   // Your SSID
#define WLAN_PASS       "your_password"           // Your password


/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "sancharinee"
#define AIO_KEY       "aio_FFPa41YNWsosZ3ixEQ39jcBZLz0O"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe livingroomlight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Livingroom");
Adafruit_MQTT_Subscribe bedroomlight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Bedroom");
Adafruit_MQTT_Subscribe bathroomlight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Bathroom");


void MQTT_connect();

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

   // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&livingroomlight);
  mqtt.subscribe(&bedroomlight);
  mqtt.subscribe(&bathroomlight);

}

void loop() {
 
  MQTT_connect();
  

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &livingroomlight) {
      int led1_data = atoi((char *)livingroomlight.lastread);
      digitalWrite(led1, led1_data);
      
    }
    if (subscription == &bedroomlight) {
      int led2_data = atoi((char *)bedroomlight.lastread);
      digitalWrite(led2, led2_data);
    }
    if (subscription == &bathroomlight) {
      int led3_data = atoi((char *)bathroomlight.lastread);
      digitalWrite(led3, led3_data);
    }

  }

  
}

void MQTT_connect() {
  int8_t ret;

   // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
