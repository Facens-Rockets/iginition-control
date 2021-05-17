#ifndef INCLUDE_SETUP_TASKS_H__
#define INCLUDE_SETUP_TASKS_H__

TaskHandle_t ignition_task;
TaskHandle_t plot_oled_task;
TaskHandle_t receiver_lora_task;
TaskHandle_t plot_serial_task;

QueueHandle_t ignition_queue;
QueueHandle_t load_queue;
QueueHandle_t relay_response_queue;
QueueHandle_t packet_rssi_queue;

SemaphoreHandle_t lora_semaphore;

#include "tasks/ignition_buttons.hpp"
#include "tasks/plot_oled.hpp"
#include "tasks/receiver_lora.hpp"
#include "tasks/plot_serial.hpp"

void core_zero(int core = 0) {
  xTaskCreatePinnedToCore(ignition_buttons_code, "ignition", 1000, NULL, 1, &ignition_task, core);
  xTaskCreatePinnedToCore(recever_lora_code, "receiver", 1000, NULL, 2, &receiver_lora_task, core);
}
void core_one(int core = 1) {
  xTaskCreatePinnedToCore(plot_oled_code, "oled", 2000, NULL, 1, &plot_oled_task, core);
  xTaskCreatePinnedToCore(plot_serial_code, "serial", 1000, NULL, 1, &plot_serial_task, core);
}

void setup_tasks() {
  ignition_queue = xQueueCreate(1, sizeof(uint8_t));
  load_queue = xQueueCreate(5, sizeof(char[8]));
  relay_response_queue = xQueueCreate(1, sizeof(byte));
  packet_rssi_queue = xQueueCreate(2, sizeof(int));

  lora_semaphore = xSemaphoreCreateMutex();

  core_zero();
  core_one();
}

#endif // INCLUDE_SETUP_TASKS_H__