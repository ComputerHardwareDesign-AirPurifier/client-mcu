volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);

}

void timer_init() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void time_count() {
  if (interruptCounter > 0) {
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);
    if (isAutoShutdown && timeShutdown > 0 && isOn) {
      totalInterruptCounter++;
      if (totalInterruptCounter > 59) {
        totalInterruptCounter = 0;
        timeShutdown--;
      }
      Serial.println(totalInterruptCounter);
    } else {
      totalInterruptCounter = 0;
    }
    if (timeShutdown <= 0 && isOn && isAutoShutdown) {
      timeShutdown = 1;
      isAutoShutdown = 0;
      isOn = 0;
    }
  }

}
