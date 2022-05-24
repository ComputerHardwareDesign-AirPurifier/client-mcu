#include "config.h"
//#include "esp32_timer.h"
//#include "update_data.h"
//#include "screen.h"
//#include "SPIFFS_functions.h"
//#include "air_controller.h"
#include "read_sensor.h"
/////////////////////
void setup() {
  Serial.begin(115200);
//  delay(10);
//  timer_init();
//  delay(10);
//  SPIFFS_init();
//  delay(10);
//  screen_init();
//  delay(10);
  dust_sensor_init();
}
///////////////////////

void loop() {
//  screen_controller();
//  data_update();
//  time_count();
//  air_controller();
  dust_sensor_controller();

}
