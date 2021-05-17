#include <Arduino.h>
#include <soc/rtc_wdt.h>

#include "heltec.h"
#include "buttons.hpp"
#include "setup_lora.hpp"
#include "setup_lora_packet.hpp"
#include "setup_tasks.hpp"
#include "lora_callback.hpp"

void setup() {
  Heltec.begin(true, true, true, true, LORA_BAND);

  Heltec.display->init();
  Heltec.display->flipScreenVertically();   
  Heltec.display->setFont(ArialMT_Plain_10);

  setup_lora();
  setup_lora_packet();
  setup_buttons();

  setup_tasks();
}

void loop() {
  // put your main code here, to run repeatedly:
}