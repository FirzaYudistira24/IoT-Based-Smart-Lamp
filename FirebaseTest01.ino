#include <WiFi.h>
#include <WiFiMulti.h>

#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "..." //your username
#define WIFI_PASSWORD "..." //your password

#define API_KEY "..." //your API
#define DATABASE_URL "..." //your Database url

#define RELAY1 26
#define RELAY2 25
#define RELAY3 32
#define RELAY4 33

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

WiFiMulti WiFiMulti;

bool signupOK = false;
unsigned int din01 = 0;
unsigned int din02 = 0;
unsigned long sendDataPrevMillis = 0;

void setup() {
  
  
  Serial.begin(115200);
  delay(10);

  WiFiMulti.addAP("username", "password");

  Serial.println();
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);


  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if(Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("signUp OK");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
 

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
}

void loop() {
  Serial.println("test-loop");
  if(Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

  }
  if(Firebase.RTDB.getBool(&fbdo, "/relay-10/Ch01")) { 
    Serial.println("test-baca-firebase");
    if(fbdo.dataType() == "int") {
      din01 = fbdo.intData();
      Serial.println("Successful Read from " + fbdo.dataPath() + ": " + din01 + " (" + fbdo.dataType() + ")");
      if(din01 == 1) {
        digitalWrite(RELAY1, HIGH);  
        Serial.println("Nilai din01 = 1");
      } else {
        digitalWrite(RELAY1, LOW);
        Serial.println("Nilai din01 = 0");
      }
    }
  }
}

