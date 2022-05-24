uint16_t dustLevel[3] = {20, 40, 60};
void air_controller() {
  if (isOn) {
    if (fanMode == 0) {
      if (dustValue > maxDust) {
        fanLevel = 3;
      } else if (dustValue < dustLevel[0]) {
        fanLevel = 1;
      } else if (dustValue < dustLevel[1]) {
        fanLevel = 2;
      } else if (dustValue < dustLevel[2]) {
        fanLevel = 3;
      }
    }

  } else {
    fanLevel = 0;
  }
}
