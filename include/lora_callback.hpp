#ifndef INCLUDE_LORA_CALLBACK_H__
#define INCLUDE_LORA_CALLBACK_H__

#include "heltec.h"
#include "lora_struct/lora_struct.hpp"
#include "setup_tasks.hpp"

// extern QueueHandle_t load_queue;

// extern lora_packet message;

// extern QueueHandle_t relay_response_queue;

byte relay_message;
String load_as_string;
int received_load = 0;
float load_float = 0;

byte response = 0;
uint8_t ignition_response = 0;

void on_receive_lora_callback(int packet_size) {
  if (packet_size <= 0) return;
  int packet_rssi = 0;
  uint8_t buffer[sizeof(packet_rssi)];

  message.destination = LoRa.read();
  if (message.destination == 0xF1) {
    message.local_address = LoRa.read();
    if (message.local_address == 0xF2) { //
      // relay_message = LoRa.read();
      ignition_response = LoRa.read();

      LoRa.readBytes(buffer, sizeof(packet_rssi));
      packet_rssi = *((int*) buffer);
      
      xQueueSend(relay_response_queue, &ignition_response, portMAX_DELAY);
      xQueueSend(packet_rssi_queue, &packet_rssi, portMAX_DELAY);
      // if (relay_message == 0x0F) {
      //   response = 1;
      //   // xQueueSend(relay_response_queue, &relay_message, portMAX_DELAY);
      // }
    } else if (message.local_address == 0xF3) {
      message.payload = LoRa.readString();
      xQueueSend(load_queue, &message.payload, portMAX_DELAY);
    }
  } else {
    message.payload = LoRa.readString();
  }

  Serial.print(message.destination, HEX);
  Serial.print("\t");
  Serial.print(message.local_address, HEX);
  Serial.print("\t");
  Serial.print(packet_rssi);
  Serial.print("\t");
  Serial.println(message.payload);

  // xQueueSend(load_queue, &load_as_string, 1);
}

#endif  // INCLUDE_LORA_CALLBACK_H__
