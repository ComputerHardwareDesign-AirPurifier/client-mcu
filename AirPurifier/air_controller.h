float dustLevel[3] = {20.0, 40.0, 60.0};
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
  if(fanLevel!=prevFanLevel){
    prevFanLevel=fanLevel;
    if(fanLevel==0){
      Serial2.write(fanLevel);
    }else{
      Serial2.write(50+((fanLevel-1)*25));
    }
  }
}
