// Philly Code Camp IoT Workshop
// Allow users to give feedback by pressing buttons
// This version send temperature and humidity to Azure when the buttons are pressed
//
// Uses WiFiNINA https://www.arduino.cc/en/Reference/WiFiNINA
// Joël Gähwiler's MQTT Library https://github.com/256dpi/arduino-mqtt
// Adafruit DHT Sensor Library https://github.com/adafruit/DHT-sensor-library
// Adafruit Unified Sensor Library https://github.com/adafruit/Adafruit_Sensor
//

#include <SPI.h>
#include <WiFiNINA.h>
#include <MQTT.h>

WiFiSSLClient net;
MQTTClient mqtt(1024);

// Temperature and Humidity Sensor
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN  1
DHT dht(DHTPIN, DHTTYPE);

// Define pins for the buttons
#define GOOD_BUTTON_PIN 3
#define NEUTRAL_BUTTON_PIN 4
#define BAD_BUTTON_PIN 5

const char wifi_ssid[] = "workshop";
const char wifi_password[] = "wifi-password";

const char server[] = "workshop.azure-devices.net";
const char clientId[] = "arduino1010";
const char username[] = "workshop.azure-devices.net/arduino1010/api-version=2016-11-14";
const char password[] = "SharedAccessSignature sr=workshop.azure-devices.net%2Fdevices%2Farduino1010&sig=nxL8rIMF4BwN%2FQA0g5heScFKe2oOGTyFF6iBfffuTdI%3D&se=1686158854";

// Azure IoT Hub MQTT topics
// https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-mqtt-support#sending-device-to-cloud-messages
String feedbackTopic = "devices/arduino1010/messages/events/";
String ledTopic = "devices/arduino1010/messages/devicebound/#";

// limit publish to once every 2 seconds
unsigned long publishInterval = 2 * 1000;
unsigned long lastMillis = 0;

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);

  // Uncomment next line to wait for a serial connection
  // while (!Serial) { }
 
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize button pins as input.
  pinMode(GOOD_BUTTON_PIN, INPUT);
  pinMode(NEUTRAL_BUTTON_PIN, INPUT);
  pinMode(BAD_BUTTON_PIN, INPUT);

  // initialize temperature sensor
  dht.begin();   
 
  Serial.println("Connecting WiFi");
  connectWiFi();

  // Start the MQTT connection
  Serial.println("Setting up MQTT");
  mqtt.begin(server, 8883, net);

  // define function for incoming messages
  mqtt.onMessage(messageReceived);
}

// TODO break this up into smaller functions
void loop() {
  mqtt.loop();

  if (!mqtt.connected()) {
    connectMQTT();
  }
  
  if (millis() - lastMillis > publishInterval) {
    readButtons();
  }

}

void readButtons() {
  int bad = digitalRead(BAD_BUTTON_PIN);
  int neutral = digitalRead(NEUTRAL_BUTTON_PIN);
  int good = digitalRead(GOOD_BUTTON_PIN);

  if (bad + neutral + good > 1) {
    Serial.println("Multiple buttons are pressed. Ignoring.");
    lastMillis = millis();
    return;
  }

  float feedback;
  if (bad) {
    feedback = 0.0;
  } else if (neutral) {
    feedback = 0.5;
  } else if (good) {
    feedback = 1.0;
  } else {
    feedback = -1.0;
  }

  if (feedback > -1) {
    digitalWrite(LED_BUILTIN, HIGH);

    float temperature = dht.readTemperature(true);
    float humidity = dht.readHumidity();

    // manually build JSON for MQTT payload
    // {"temperature":"%%%", "humidity":"%%%", "vote":1, "device":"Cafe"}
    String payload = "{\"temperature\":";
    payload += String(temperature);
    payload += ", \"humidity\":";
    payload += String(humidity);
    payload += ", \"vote\":";
    payload += feedback;
    payload += ", \"device\": \"";
    payload += clientId;
    payload += "\"}";

    // Debug
    Serial.print("Sending ");
    Serial.print(payload);
    Serial.print(" to ");
    Serial.println(feedbackTopic);

    // Write to MQTT
    mqtt.publish(feedbackTopic, payload); 
    lastMillis = millis();
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void connectWiFi() {
  // Check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  Serial.print("WiFi firmware version ");
  Serial.println(WiFi.firmwareVersion());
  
  // attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(wifi_ssid);
    status = WiFi.begin(wifi_ssid, wifi_password);

    // wait 3 seconds for connection
    delay(3000);
  }
  Serial.println("Connected to WiFi");
  printWiFiStatus();

}

void connectMQTT() {
  Serial.print("Connecting MQTT...");
  while (!mqtt.connect(clientId, username, password)) {
    Serial.print(".");
    delay(500);
  }

  mqtt.subscribe(ledTopic);

  Serial.println("connected.");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (payload ==   "ON") {
    // turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (payload == "OFF") {
    // turn the LED off
    digitalWrite(LED_BUILTIN, LOW);    
  }
}

void printWiFiStatus() {
  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
