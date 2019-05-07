#include <Arduino.h>
#include <Wire.h>
#include "TDA7468.h"

TDA7468::TDA7468(){
	Wire.begin();
}

void TDA7468::setInput(int input){
  switch (input) {
        case 0: input = 0b00101000;break;
	case 1: input = 0b00101001;break;
	case 2: input = 0b00101010;break;
	case 3: input = 0b00101011;break;
  }
  writeWire(TDA7468_INPUT_SELECT,input);	
  } 

void TDA7468::setGain(int gain){
  switch (gain) {
        case 0: gain = 0b00000000;break;
	case 1: gain = 0b00000001;break;
	case 2: gain = 0b00000010;break;
	case 3: gain = 0b00000011;break;
        case 4: gain = 0b00000100;break;
	case 5: gain = 0b00000101;break;
	case 6: gain = 0b00000110;break;
	case 7: gain = 0b00000111;break;
  }
  writeWire(TDA7468_INPUT_GAIN,gain);	
  } 

void TDA7468::setSurround(int sur, int gain1, int mix, int buf){
  switch (sur) {
        case 0: sur = 0b00000001;break;
	case 1: sur = 0b00000000;break;
  }
  switch (gain1) {
        case 0: gain1 = 0b00000000;break;
	case 1: gain1 = 0b00000010;break;
        case 2: gain1 = 0b00000100;break;
	case 3: gain1 = 0b00000110;break;
  }
  switch (mix) {
        case 0: mix = 0b00000000;break;
	case 1: mix = 0b00001000;break;
        case 2: mix = 0b00010000;break;
	case 3: mix = 0b00011000;break;
	case 4: mix = 0b00100000;break;
	case 5: mix = 0b00101000;break;
	case 6: mix = 0b00110000;break;
	case 7: mix = 0b00111000;break;
  }
  switch (buf) {
        case 0: buf = 0b01000000;break;
	case 1: buf = 0b00000000;break;
  }
        int sum_sur = sur + gain1 + mix + buf;
  writeWire(TDA7468_SURROUND,sum_sur);	
  } 

void TDA7468::setVol_R(int vol_r){
    vol_r = 63-vol_r;
  writeWire(TDA7468_VOLUME_RIGHT,vol_r);	
  } 

void TDA7468::setVol_L(int vol_l){
    vol_l = 63-vol_l;
  writeWire(TDA7468_VOLUME_LEFT,vol_l);	
  } 

void TDA7468::setTreb_Bass(int treb, int bass){
  switch (treb) {
        case -7: treb = 0b00000000;break;
	case -6: treb = 0b00000001;break;
	case -5: treb = 0b00000010;break;
	case -4:  treb = 0b00000011;break;
        case -3:  treb = 0b00000100;break;
	case -2:  treb = 0b00000101;break;
	case -1:  treb = 0b00000110;break;
	case  0:  treb = 0b00000111;break;
        
        case 7: treb = 0b00001000;break;
	case 6: treb = 0b00001001;break;
	case 5: treb = 0b00001010;break;
	case 4:  treb = 0b00001011;break;
        case 3:  treb = 0b00001100;break;
	case 2:  treb = 0b00001101;break;
	case 1:  treb = 0b00001110;break;
  }
  switch (bass) {
        case -7: bass = 0b00000000;break;
	case -6: bass = 0b00010000;break;
	case -5: bass = 0b00100000;break;
	case -4:  bass = 0b00110000;break;
        case -3:  bass = 0b01000000;break;
	case -2:  bass = 0b01010000;break;
	case -1:  bass = 0b01100000;break;
	case  0:  bass = 0b01110000;break;
        
        case 7: bass = 0b10000000;break;
	case 6: bass = 0b10010000;break;
	case 5: bass = 0b10100000;break;
	case 4:  bass = 0b10110000;break;
        case 3:  bass = 0b11000000;break;
	case 2:  bass = 0b11010000;break;
	case 1:  bass = 0b11100000;break;
  }
        int sum_treb_bass = treb + bass;
  writeWire(TDA7468_TREBLE_BASS,sum_treb_bass);	
  } 

void TDA7468::setOutput(int output){
  switch (output) {
        case 0: output = 0b00000000;break;
	case 1: output = 0b00000001;break;
  }
  writeWire(TDA7468_OUTPUT ,output);	
  } 

void TDA7468::setAlc(int mode, int detector, int circ, int attack, int tresh, int rez){
  switch (mode) {
        case 0: mode = 0b00000001;break;
	case 1: mode = 0b00000000;break;
  }
  switch (detector) {
        case 0: detector = 0b00000010;break;
	case 1: detector = 0b00000000;break;
  }
  switch (circ) {
        case 0: circ = 0b00000100;break;
	case 1: circ = 0b00000000;break;
  }
  switch (attack) {
        case 0: attack = 0b00000000;break;
	case 1: attack = 0b00001000;break;
        case 2: attack = 0b00010000;break;
	case 3: attack = 0b00011000;break;
  }
  switch (tresh) {
        case 0: tresh = 0b00000000;break;
	case 1: tresh = 0b00100000;break;
        case 2: tresh = 0b01000000;break;
	case 3: tresh = 0b01100000;break;
  }
  switch (rez) {
        case 0: rez = 0b00000000;break;
	case 1: rez = 0b00000001;break;
  }
        int sum_alc = mode + detector + circ + attack + tresh + rez;
  writeWire(TDA7468_BASS_ALC ,sum_alc);	
  } 


void TDA7468::writeWire(char a, char b){
  Wire.beginTransmission(TDA7468_address);
  Wire.write (a);
  Wire.write (b);
  Wire.endTransmission();
}
