#include "config.h"
#include "screen.h"
#include "SPIFFS_functions.h"
/////////////////////
void setup() {
  Serial.begin(115200);
  delay(10);
  SPIFFS_init();
  delay(10);
  screen_init();
}
///////////////////////

void loop() {
  screen_controller();
}
