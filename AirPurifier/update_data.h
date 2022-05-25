#define delayUpdate  500
uint8_t isSettingUpdated = 0;
uint32_t prevTimeUpdate = 0;
void data_change() {
  isSettingUpdated = 0;
  prevTimeUpdate = millis();
}

void data_update() {
  if (isSettingUpdated == 0 && millis() - prevTimeUpdate > delayUpdate) {
    isSettingUpdated = 1;
    prevTimeUpdate = millis();
//        Serial.println("-------------------update data----------------------");
//        Serial.print("isOn: ");
//        Serial.println(isOn);
//        Serial.print("fanLevel: ");
//        Serial.println(fanLevel);
//        Serial.print("fanMode: ");
//        Serial.println(fanMode);
//        Serial.print("maxDust: ");
//        Serial.println(maxDust);
//        Serial.print("isAutoShutdown: ");
//        Serial.println(isAutoShutdown);
//        Serial.print("timeShutdown: ");
//        Serial.println(timeShutdown);
//        Serial.println();
    
  }

}
