#include <Wire.h>
#include <TDA7468.h>
  TDA7468 tda;
  
void setup(){ 
  Serial.begin(9600);Wire.begin();
}

void loop(){
  audio();
  delay(1000);
}
// https://rcl-radio.ru/wp-content/uploads/2019/05/tda7468.pdf
void audio(){
  tda.setInput(0); 
  tda.setGain(0);
  tda.setSurround(0,0,0,0);
  tda.setVol_R(62);
  tda.setVol_L(62);
  tda.setTreb_Bass(0,0);
  tda.setOutput(1); // mute
  tda.setAlc(0,0,0,0,0,0);
}
