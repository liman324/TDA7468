// rcl-radio.ru liman324@yandex.ru 


#ifndef TDA7468_H
#define TDA7468_H

#define TDA7468_address 0x44

//Sub addresses
#define TDA7468_INPUT_SELECT   0b00000000
#define TDA7468_INPUT_GAIN     0b00000001
#define TDA7468_SURROUND       0b00000010
#define TDA7468_VOLUME_LEFT    0b00000011
#define TDA7468_VOLUME_RIGHT   0b00000100
#define TDA7468_TREBLE_BASS    0b00000101
#define TDA7468_OUTPUT         0b00000110
#define TDA7468_BASS_ALC       0b00000111

#include <Arduino.h>
class TDA7468
{
  public:
    TDA7468();
	void setInput(int input);                                // 0...3 IN1...IN4
	void setGain(int gain);                                  // 0...7 0...14 dB // step 2dB
	void setSurround(int sur, int gain1, int mix, int buf);   // sur 1 on 0 off // gain 0...3 // mix 0...7 // buf 1 on 0 off
	void setVol_R(int vol_r);                                // 0...62 
	void setVol_L(int vol_l);                                // 0...62
	void setTreb_Bass(int treb, int bass);                   // -14...14 step 2 dB
        void setOutput(int output);                              // mute 0 on 1 off
        void setAlc(int mode, int detector, int circ, int attack, int tresh, int rez);
                 // mode 1 on 0 off 
                 // detector 1 on 0 off 
                 // circ 1 on 0 off 
                 // attack 12k5 25k 50k 100k 0...3
                 // tresh 700mVrms 485mVrms 320mVrms 170mVrms 0...3
                 // rez MODE 1: Fixed Resistor / MODE 2: Adaptive 0...1
  private:
	void writeWire(char a, char b);
};
	
#endif //TDA7468_H
