/*
https://rcl-radio.ru/?p=58165 - пример использования, видео, фото
Alexander Liman
liman324@yandex.ru
*/
#include <Wire.h>
#include <TDA7468.h>
#include <MsTimer2.h>
#include <LiquidCrystal.h>
#include <Encoder.h>
#include <EEPROM.h>
  TDA7468 tda;
  Encoder myEnc(9, 8);//CLK, DT подключение энкодера
  LiquidCrystal lcd(7, 6, 2, 3, 4, 5);// RS,E,D4,D5,D6,D7 подключение LCD
   byte a1[8]={0b00000,0b11011,0b11011,0b11011,0b11011,0b11011,0b11011,0b00000};
  byte a2[8]={0b00000,0b11000,0b11000,0b11000,0b11000,0b11000,0b11000,0b00000};
   unsigned long newPosition,time,oldPosition  = -999;
   int vol,vol_d,menu,w,w1,z,mute=1,treb,treble_d,bass,bass_d,in,gain,gain1,gain2,gain3,gain4,balans;
 
void setup(){ 
  Serial.begin(9600);Wire.begin();
   lcd.begin(16, 2);lcd.createChar(0,a1); lcd.createChar(1,a2);
   pinMode(A0,INPUT);// КНОПКА ЭНКОДЕРA
   pinMode(12,INPUT);// IN 
     MsTimer2::set(1, to_Timer);MsTimer2::start();
     vol = EEPROM.read(0);treb = EEPROM.read(1)-7;bass = EEPROM.read(2)-7;in = EEPROM.read(3);
     gain1 = EEPROM.read(4);gain2 = EEPROM.read(5);gain3 = EEPROM.read(6);gain4 = EEPROM.read(7);
   audio();
}
 
void to_Timer(){ //функция таймера
 newPosition = myEnc.read()/4;}
 
 
void loop(){
   if((analogRead(A0)<900)){menu++;cl();myEnc.write(0);time=millis();w1=1;if(menu>4){menu=0;}}// меню
   if(digitalRead(12)==HIGH){in++;if(in>3){in=0;}audio();lcd.clear();lcd.print("IN ");lcd.print(in+1);delay(1000);}
  //////////////////////////////////////// Volume -62 ... 0 дБ //////////////////////////////////////
 if(menu==0){
    if (newPosition != oldPosition) {
    oldPosition = newPosition;
    vol=vol+newPosition;myEnc.write(0);newPosition=0;audio();lcd.clear();time=millis();w1=1;if(vol>62){vol=62;}if(vol<1){vol=1;}}
 
   if(w==1){audio();cl();time=millis();w=0;w1=1;}
  lcd.setCursor(0,0);if(mute==1){lcd.print("Volume   ");}else{lcd.print("MUTE     ");}
  lcd.print(-62+vol);lcd.setCursor(13,0);lcd.print("dB");vol_d=vol/3;
   if(vol_d>=0){for(z=0;z<=vol_d;z++){lcd.setCursor(z/2,1);lcd.write((uint8_t)0);}}
   if((vol_d)%2==0){lcd.setCursor(z/2,1);lcd.write((uint8_t)1);}
  lcd.setCursor(13,1);lcd.print(vol);}
//////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////// индикация тембр HЧ -14...14 дБ ///////////////////
   if(menu==1){
     if (newPosition != oldPosition) {
    oldPosition = newPosition;
    treb=treb+newPosition;myEnc.write(0);newPosition=0;audio();lcd.clear();time=millis();w1=1;if(treb>7){treb=7;}if(treb<-7){treb=-7;}} 
 
   if(w==1){audio();cl();time=millis();w1=1;w=0;}
  lcd.setCursor(0,0);lcd.print("Treble   ");
  lcd.print(treb*2);lcd.setCursor(13,0);lcd.print("dB");treble_d=treb+7;
   if(treble_d>=0){for(z=0;z<=treble_d;z++){lcd.setCursor(z,1);lcd.write((uint8_t)0);}}
 }
/////////////////////////////////////////////////////////////////////////////////////
 
  /////////////////////// индикация тембр ВЧ -14...14 дБ ///////////////////
   if(menu==2){
     if (newPosition != oldPosition) {
    oldPosition = newPosition;
    bass=bass+newPosition;myEnc.write(0);newPosition=0;audio();lcd.clear();time=millis();w1=1;if(bass>7){bass=7;}if(bass<-7){bass=-7;}} 
 
   if(w==1){audio();cl();time=millis();w1=1;w=0;}
  lcd.setCursor(0,0);lcd.print("Bass     ");
  lcd.print(bass*2);lcd.setCursor(13,0);lcd.print("dB");bass_d=bass+7;
   if(bass_d>=0){for(z=0;z<=bass_d;z++){lcd.setCursor(z,1);lcd.write((uint8_t)0);}}
 }
/////////////////////////////////////////////////////////////////////////////////////
  // индикация баланс + управление кнопками +\- 4 дБ ///////
   if(menu==3){
     if (newPosition != oldPosition) {
    oldPosition = newPosition;
    balans=balans+newPosition;myEnc.write(0);newPosition=0;audio();lcd.clear();time=millis();w1=1;if(balans>4){balans=4;}if(balans<-4){balans=-4;}} 
  lcd.setCursor(0,0);
   if(balans>=0){lcd.print("-");}else{lcd.print("+");}
  lcd.print(abs(balans));lcd.print(" dB ");
  lcd.print(" <>  ");
   if(balans>=0){lcd.print("+");}else{lcd.print("-");}
  lcd.print(abs(balans));lcd.print(" dB ");
  lcd.setCursor(0,1);lcd.print("L");
  lcd.setCursor(15,1);lcd.print("R");
   if(balans<0){lcd.setCursor(balans+7,1);lcd.write((uint8_t)0);}
   if(balans>0){lcd.setCursor(balans+8,1);lcd.write((uint8_t)0);}
   if(balans==0){lcd.setCursor(7,1);lcd.write((uint8_t)0);lcd.setCursor(8,1);lcd.write((uint8_t)0);}
   if(w==1){audio();cl();time=millis();w1=1;w=0;}
 }
 /////////////////////////////////////////////////////////////
  /////////////////////// gain  ///////////////////
   if(menu==4){
      if(in==0){gain=gain1;}
      if(in==1){gain=gain2;}
      if(in==2){gain=gain3;}
      if(in==3){gain=gain4;}
    if (newPosition != oldPosition) {
    oldPosition = newPosition;
    gain=gain+newPosition;myEnc.write(0);newPosition=0;audio();lcd.clear();time=millis();w1=1;if(gain>7){gain=7;}if(gain<0){gain=0;}
} 
      if(in==0){gain1=gain;}
      if(in==1){gain2=gain;}
      if(in==2){gain3=gain;}
      if(in==3){gain4=gain;}
   if(w==1){audio();cl();time=millis();w1=1;w=0;}
  lcd.setCursor(0,0);lcd.print("IN ");lcd.print(in+1);lcd.print(" Gain ");lcd.print(gain*2);lcd.print(" dB");
 }
/////////////////////////////////////////////////////////////////////////////////////
 
 if(millis()-time>10000 && w1==1){
     EEPROM.update(0,vol);
     EEPROM.update(2,bass+7);
     EEPROM.update(1,treb+7);
     EEPROM.update(3,in);
     EEPROM.update(4,gain1);EEPROM.update(5,gain2);EEPROM.update(6,gain3);EEPROM.update(7,gain4);
  menu=0;w1=0;cl();
 }
}//loop
 void cl(){delay(300);lcd.clear();}
void audio(){
  tda.setInput(in); 
  tda.setGain(gain);
  tda.setSurround(1,0,3,1);// не менять
  tda.setVol_R(vol+balans-4);
  tda.setVol_L(vol-balans-4);
  tda.setTreb_Bass(treb,bass);
  tda.setOutput(1); // mute не менять
  tda.setAlc(0,0,0,0,0,0); // не менять
}
