#include "config.h"
#include "esp32_timer.h"
#include "update_data.h"
#include "screen.h"
#include "SPIFFS_functions.h"
#include "air_controller.h"
#include "read_sensor.h"
#include <HardwareSerial.h>
#define RX2 16
#define TX2 17

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial2.begin(19200, SERIAL_8N1, RX2, TX2);
  delay(10);
  timer_init();
  delay(10);
  SPIFFS_init();
  delay(10);
  screen_init();
  delay(10);
  dust_sensor_init();
}
///////////////////////

void loop() {
  screen_controller();
  data_update();
  time_count();
  air_controller();
  dust_sensor_controller();

}
