#define RELAY1 26
#define RELAY2 25
#define RELAY3 32
#define RELAY4 33

void setup() {
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
}

void loop() {
  digitalWrite(RELAY1, HIGH);  
  delay(1000);                      
  digitalWrite(RELAY1, LOW);  
  delay(1000);                      
}
