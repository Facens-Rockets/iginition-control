#ifndef INCLUDE_TASKS_PLOT_SERIAL_H__
#define INCLUDE_TASKS_PLOT_SERIAL_H__

#include "setup_tasks.hpp"

void plot_serial_code(void* parameters) {

  while (1) {
    vTaskDelay(1);
  }
}


#endif // INCLUDE_TASKS_PLOT_SERIAL_H__
