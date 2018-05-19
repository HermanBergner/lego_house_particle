#include <MFRC522.h>
#include <Adafruit_DHT.h>

#define SS_PIN D1
#define RST_PIN D2
#define DHTPIN 3
#define DHTTYPE DHT11
#define flower_light D0
#define photo_light D6

int humidity;
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
DHT dht(DHTPIN, DHTTYPE);

void setup(){

  dht.begin();

  pinMode(flower_light, OUTPUT);
  pinMode(photo_light, OUTPUT);

  mfrc522.setSPIConfig();
  mfrc522.PCD_Init(); // Init MFRC522 card

  RGB.control(true); // take control of onboard RGB led

  Particle.function("photo_light", pho_light);
  Particle.function("flower_light", flow_light);
  Particle.function("get_temp", getTemp);
  Particle.function("get_hum", getHum);
}

void blink() {
  RGB.color(0, 0, 255);
  delay(150);
  RGB.color(0, 0, 0);
  delay(100);
  RGB.color(0, 0, 255);
  delay(150);
  RGB.color(0, 0, 0);
}

void loop() {
  // Look for new cards
  if ( mfrc522.PICC_IsNewCardPresent()) {
    // Serial.println("New card present...");
    if ( mfrc522.PICC_ReadCardSerial()) {
      // Dump debug info about the card. PICC_HaltA() is automatically called.
      //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

      String UID = "";

      for (byte i = 0; i < mfrc522.uid.size; i++) {
        UID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
        UID += String(mfrc522.uid.uidByte[i], HEX);
      }

      mfrc522.PICC_HaltA();
      Serial.print("UID: ");
      Serial.println(UID);
      Particle.publish("rfid-read", UID, 5, PRIVATE); // publish UID to rest of system

      blink(); // visual feedback of read using onboard led
    }
  }
}

int flow_light(String command){
  if(command == "on"){
    digitalWrite(flower_light, HIGH);
    return digitalRead(flower_light);
  }else if(command == "off"){
    digitalWrite(flower_light, LOW);
    return digitalRead(flower_light);
  }else if(command == "status"){
    return digitalRead(flower_light);
  }
  return -1;
}



int pho_light(String command){
  if(command == "on"){
    digitalWrite(photo_light, HIGH);
    return digitalRead(photo_light);
  }else if(command == "off"){
    digitalWrite(photo_light, LOW);
    return digitalRead(photo_light);
  }
  return -1;
}

int getTemp(String command){
  return dht.getTempCelcius();
}

int getHum(String command){
  return dht.getHumidity();
}
