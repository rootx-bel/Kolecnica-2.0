#include <Wiegand.h>
WIEGAND wg;
int c;
const int addr[50]={4786353, 10161325, 11869255, 7294923, 4782139, 4800309, 4875728, 8916074, 2062392, 8084904, 8064882};
void setup() {
  Serial.begin(9600);  
  wg.begin();
pinMode(7,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,INPUT_PULLUP);
  digitalWrite(7,1);
}

void loop() {
  digitalWrite(7,1);
  
  if(wg.available())
  {
    c=wg.getCode();
    Serial.println(wg.getCode());
    for(int i=0;i<100;i++){
      if(c==addr[i]){
        Serial.println(1);
        digitalWrite(7,0);
        delay(3000);
  digitalWrite(7,1);
      }
    } 
  }
  if(digitalRead(6)==0){
    Serial.println(1);
    digitalWrite(7,0);
    digitalWrite(4,0);
    digitalWrite(5,0);
    delay(3000);
    digitalWrite(7,1);
    digitalWrite(4,1);
    digitalWrite(5,1);
  }
  
}
