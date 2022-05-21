#include "config.h"
#include "screen.h"

void setup() {
  Serial.begin(9600);
  screen_init();
}


void loop() {
  Serial.println(isOn);
  screen_controller();
  screenMode++;
  delay(3000);
}
