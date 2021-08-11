#ifndef INCLUDE_TASKS_IGNITION_BUTTONS_H__
#define INCLUDE_TASKS_IGNITION_BUTTONS_H__

#include "buttons.hpp"
#include "ignition_command.hpp"
#include "setup_tasks.hpp"
#include "lora_callback.hpp"

uint8_t count_ignition = 0;

void ignition_buttons_code(void* parameters) {
  bool ignition_lock = true;
  
  // while (true) {
  //   while (!digitalRead(ignition_button)) {
  //     vTaskDelay(1);
  //   }

  //   if (!digitalRead(security_button)) {
  //     uint64_t timer = xTaskGetTickCount();
  //     while (!digitalRead(security_button)) {
  //       if(xTaskGetTickCount() > timer + pdMS_TO_TICKS(2000)){
  //         ignition_lock = false;
  //         break;
  //       }
  //       vTaskDelay(1);
  //     }

  //     while (!digitalRead(security_button) && !ignition_lock) {
  //       if (!digitalRead(ignition_button) && !ignition_lock) {
  //         send_ignition_command();
  //         char* ignition_send = "send";
  //         xQueueSend(ignition_queue, &ignition_send, portMAX_DELAY);
  //         break;
  //       }
  //       vTaskDelay(1);
  //     }
  //     while(!digitalRead(ignition_button)){
  //       vTaskDelay(1);
  //     }
  //   }
  //   ignition_lock = false;
  //   vTaskDelay(1);
  // }
  while (true) {
    if (!digitalRead(security_button)) {
      uint64_t timer = xTaskGetTickCount();
      while (!digitalRead(security_button)) {
        if(xTaskGetTickCount() > timer + pdMS_TO_TICKS(1500)){
          ignition_lock = false;
          break;
        }
        vTaskDelay(1);
      }

      if (!ignition_lock) {
        while (!digitalRead(security_button)) {
          if (!digitalRead(ignition_button)) {
            Serial.println("send");
            xSemaphoreTake(lora_semaphore, portMAX_DELAY);
            count_ignition++;
            send_ignition_command();
            // while (!response) {
            //   send_ignition_command();
            //   vTaskDelay(pdMS_TO_TICKS(10));
            //   on_receive_lora_callback(LoRa.parsePacket());
            // }
            vTaskDelay(pdMS_TO_TICKS(5));
            xSemaphoreGive(lora_semaphore);
            xQueueSend(ignition_queue, &count_ignition, portMAX_DELAY);
            Serial.println("queue");

            while (!digitalRead(ignition_button)) {
              vTaskDelay(1);
            }
          }
          vTaskDelay(1);
        }
      }
    }

    vTaskDelay(1);
  }
}

#endif  // INCLUDE_TASKS_IGNITION_BUTTONS_H__
