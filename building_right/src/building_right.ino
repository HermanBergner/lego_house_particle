#define baker_light D4
#define flame_light D1
#define dent_light D2
#define family_light D3
#define flame_pin D5

int servoPin = D0;
Servo cafeServo;
int Flame = HIGH;  // HIGH when FLAME Exposed
int servoPos = 0;

void setup(){
  pinMode(baker_light, OUTPUT);
  pinMode(flame_light, OUTPUT);
  pinMode(dent_light, OUTPUT);
  pinMode(family_light, OUTPUT);
  pinMode(flame_pin, INPUT);

  cafeServo.attach( D0 );
  Particle.function("door", door);

  Particle.function("family_light", tog_3_light);
  Particle.function("dent_light", tog_2_light);
  Particle.function("baker_light", tog_1_light);
}

void loop() {
  Flame = digitalRead(flame_pin);
  if (Flame== HIGH){ 
    digitalWrite(flame_light, HIGH); 
  }
  else { 
    digitalWrite(flame_light, LOW); 
  }
}

int tog_1_light(String command){
  if(command == "on"){
    digitalWrite(baker_light, HIGH);
    return digitalRead(baker_light);
  }else if(command == "off"){
    digitalWrite(baker_light, LOW);
    return digitalRead(baker_light);
  }
  return -1;
}

int tog_2_light(String command){
  if(command == "on"){
    digitalWrite(dent_light, HIGH);
    return digitalRead(dent_light);
  }else if(command == "off"){
    digitalWrite(dent_light, LOW);
    return digitalRead(dent_light);
  }
  return -1;
}

int tog_3_light(String command){
  if(command == "on"){
    digitalWrite(family_light, HIGH);
    return digitalRead(family_light);
  }else if(command == "off"){
    digitalWrite(family_light, LOW);
    return digitalRead(family_light);
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

int servoControl(int pos)
{
  servoPos = constrain(pos, 0 , 180);
  cafeServo.write( servoPos );
  return servoPos;
}
