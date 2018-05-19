// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

#define music_light D2
#define baller_light D3
//#define servo_pin D4

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 24
#define PIXEL_PIN D1
#define PIXEL_TYPE WS2812

#define PEACH 200,50,5
#define CYAN 10,150,70
#define PURPLE 180,3,180
#define BLUE 5,5,190
#define WHITE 150,150,150
#define GREEN 10,180,10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTime = 20;
int partyVsNormal = 1;
int i;
void spin(int R, int G, int B);


int servoPin = D0;
Servo cafeServo;
int servoPos = 0;

void setup(){
  pinMode(music_light, OUTPUT);
  pinMode(baller_light, OUTPUT);

  cafeServo.attach( D0 );
  Particle.function("door", door);

  Particle.function("pixel_light", tog_pixel);
  Particle.function("baller_light", tog_3_light);
  Particle.function("music_light", tog_2_light);

  strip.begin();
  strip.updateLength(24);
  strip.setBrightness(50);
  strip.show();

  lightMode(WHITE);

}

void loop() {
  if(partyVsNormal == 0){
    lightMode(0, 0, 0);
  } else if (partyVsNormal == 1){
    lightMode(WHITE);
  } else if (partyVsNormal == 2){
    lightMode (PEACH);
    lightMode (CYAN);
    lightMode (PURPLE);
    lightMode (BLUE);
    lightMode (WHITE);
    lightMode (GREEN);
  }
}

int tog_pixel(String command){
  if(command == "on"){
    partyVsNormal = 1;
    return partyVsNormal;
  } else if (command == "off"){
    partyVsNormal = 0;
    return partyVsNormal;
  } else if (command == "party"){
    partyVsNormal = 2;
    return partyVsNormal;
  }
}

int tog_2_light(String command){
  if(command == "on"){
    digitalWrite(music_light, HIGH);
    return digitalRead(music_light);
  }else if(command == "off"){
    digitalWrite(music_light, LOW);
    return digitalRead(music_light);
  }
  return -1;
}

int tog_3_light(String command){
  if(command == "on"){
    digitalWrite(baller_light, HIGH);
    return digitalRead(baller_light);
  }else if(command == "off"){
    digitalWrite(baller_light, LOW);
    return digitalRead(baller_light);
  }
  return -1;
}


int door(String command){
  int position = command.toInt();
  if(position >= 0 && position <= 180){
    return  servoControl(position);
  }else {
    return -1;
  }
}

int servoControl(int pos) {
  servoPos = constrain(pos, 0 , 180);
  cafeServo.write( servoPos );
  return servoPos;
}

void lightMode(int R, int G, int B){
  for(i=0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, R,G,B);
    strip.show();
    delay(waitTime);
  }
}

void partyMode(){
  lightMode (PEACH);
  lightMode (CYAN);
  lightMode (PURPLE);
  lightMode (BLUE);
  lightMode (WHITE);
  lightMode (GREEN);
}
