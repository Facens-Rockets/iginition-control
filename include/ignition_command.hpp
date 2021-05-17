#ifndef INCLUDE_IGNITiON_COMMAND_H__
#define INCLUDE_IGNITiON_COMMAND_H__

#include "heltec.h"
#include "setup_lora_packet.hpp"

#define DESTINATION 0xF2

extern uint8_t count_ignition;

String ignition_command = "ignite";

void populate_lora_packet() {
  message.destination = DESTINATION;
  message.local_address = 0XF1;
  message.message_length = ignition_command.length();
  message.payload = ignition_command;
}

void send_ignition_command(void) {
  // populate_lora_packet();
  LoRa.beginPacket();
  LoRa.write(0xF2);
  LoRa.write(0xF1);
  LoRa.write(0x0A);
  LoRa.write(count_ignition);
  LoRa.endPacket();
}

#endif // INCLUDE_IGNITiON_COMMAND_H__
