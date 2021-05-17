#ifndef INCLUDE_BUTTONS_H__
#define INCLUDE_BUTTONS_H__

#include "Arduino.h"

#define security_button 13
#define ignition_button 12

void setup_buttons(void){
  pinMode(security_button, INPUT_PULLUP);
  pinMode(ignition_button, INPUT_PULLUP);
}

#endif // INCLUDE_BUTTONS_H__
