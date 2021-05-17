#ifndef INCLUDE_SETUP_LORA_PACKET_H__
#define INCLUDE_SETUP_LORA_PACKET_H__

#include "lora_struct/lora_struct.hpp"

#define LOCAL_ADDRESS 0xF1

struct lora_packet message;

void setup_lora_packet(void) {
  message.local_address = LOCAL_ADDRESS;
}

#endif // INCLUDE_SETUP_LORA_PACKET_H__
