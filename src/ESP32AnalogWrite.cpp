// ESP32AnalogWrite.c
// simple arduino like 8 bit analogWrite() using ESP32 ledc
// klin, 30.03.2020

#include "Arduino.h"
#include "ESP32AnalogWrite.h"

// max number of pwm channels - 8 like arduino
#define MAX_PWM_CHANNELS 8

// 8 resolution - values 0 .´. 255
#define LEDC_TIMER_BITS 8

// ledc pwm base frequency 5000 hz
#define LEDC_BASE_FREQ  5000

// array of pwm channels
static int _pwm_channels[MAX_PWM_CHANNELS] =
  { -1, -1, -1, -1, -1, -1, -1, -1 };

// index of first free channel in array
static int _channel_free = 0;

// simple arduino like analogWrite
void analogWrite(int pin, int value)
{
  int chan;

  // check channels for pin
  for(chan = 0; chan < _channel_free; chan++) {
    // found, write value to channel / pin
    if(_pwm_channels[chan] >= 0 && _pwm_channels[chan] == pin) {
      ledcWrite(chan, value & 0xff);
      return;
    } 
  }
  
  // not found - create a new channel for pin
  if(_channel_free < MAX_PWM_CHANNELS) {
    ledcSetup(chan, LEDC_BASE_FREQ, LEDC_TIMER_BITS);
    ledcAttachPin(pin, chan);
    _pwm_channels[chan] = pin;  
     _channel_free++;
    // write value to channel / pin
    ledcWrite(chan, value & 0xff);
  }
}
