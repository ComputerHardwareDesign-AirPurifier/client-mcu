#define timeDebounce 100
#define timeScreenSleep 5000
#define TFT_LED 15
//////////////////////
#include <JPEGDecoder.h>
#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
/////////////////////////////
#include "JPEG_functions.h"

////////////////////////////
uint8_t screenMode = 0;
uint8_t isScreenRendered = 0;
uint64_t prevMillis = 0;
bool pressed = false;
uint16_t x = 0, y = 0;

////////////////////////////////////////////////////////////////////////////////screen_init//////////////////////////////////////////////////////////////////////////////////////////////////////////
void screen_init() {
  tft.init();
  delay(10);
  tft.setRotation(0);
  tft.fillScreen(TFT_WHITE);
  uint16_t calData[5] = { 278, 3465, 398, 3443, 4 };
  tft.setTouch(calData);
  pinMode(TFT_LED,OUTPUT);
  digitalWrite(TFT_LED,HIGH);
}
/////////////////////////////////////////////////////////////////////////////////logic///////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t checkTouchInCircle(uint16_t x_pos, uint16_t y_pos, uint16_t x_circle,
                           uint16_t y_circle, uint16_t radius) {
  if (pow(x_pos - x_circle, 2) + pow(y_pos - y_circle, 2) <= pow(radius, 2)) {
    return 1;
  } else {
    return 0;
  }
}

uint8_t checkTouchInRectangle(uint16_t x_pos, uint16_t y_pos, uint16_t x_R1,
                              uint16_t y_R1, uint16_t x_R2, uint16_t y_R2) {
  if (x_pos >= x_R1 && x_pos <= x_R2 && y_pos >= y_R1 && y_pos <= y_R2) {
    return 1;
  } else {
    return 0;
  }
}
////////////////////////////////////////////////////////////////
void off_screen_logic() {
  if (pressed) {
    screenMode = 1;
    isScreenRendered = 0;
    prevMillis = millis();
    data_change();
  }
}

void on_screen_logic() {
  /////////////////////////check press////////////////////////
  if (pressed) {
    isOn = 1;
    screenMode = 2 + fanMode;
    isScreenRendered = 0;
    prevMillis = millis();
    data_change();
  }
  //////////////////////////auto off///////////////////
  if (millis() - prevMillis > timeScreenSleep) {
    screenMode = 0;
    isOn = 0;
    isScreenRendered = 0;
    prevMillis = millis();
    data_change();
  }
}

void main_screen_logic() {
  //auto mode
  uint16_t auto_button_x = 51;
  uint16_t auto_botton_y = 295;
  uint16_t auto_botton_radius = 15;

  //manual mode
  uint16_t manual_button_x = 120;
  uint16_t manual_botton_y = 295;
  uint16_t manual_botton_radius = 15;

  //adjust fan level
  uint16_t decrease_button_x = 51;
  uint16_t decrease_botton_y = 236;
  uint16_t decrease_botton_radius = 15;

  uint16_t increase_button_x = 189;
  uint16_t increase_botton_y = 236;
  uint16_t increase_botton_radius = 15;

  uint16_t settings_button_x = 194;
  uint16_t settings_botton_y = 295;
  uint16_t settings_botton_radius = 15;

  uint16_t off_button_x = 51;
  uint16_t off_botton_y = 175;
  uint16_t off_botton_radius = 15;
  ////////////////////////////////////
  if (pressed) {
    prevMillis = millis();
    if (checkTouchInCircle(x, y, off_button_x, off_botton_y, off_botton_radius) == 1) { /////////////press off/////////////////
      screenMode = 0;
      isOn = 0;
      isScreenRendered = 0;
      data_change();
    } else if (checkTouchInCircle(x, y, decrease_button_x,
                                  decrease_botton_y, decrease_botton_radius) == 1) {//////////decrease_button//////////
      if (screenMode == 2) {
        screenMode = 3;
        fanMode = 1;
        isScreenRendered = 0;
      }
      if (fanLevel > 0) {
        fanLevel -= 1;
        data_change();
      }
    } else if (checkTouchInCircle(x, y, increase_button_x,
                                  increase_botton_y, increase_botton_radius) == 1) {//////////////increase_button///////////
      if (screenMode == 2) {
        screenMode = 3;
        fanMode = 1;
        isScreenRendered = 0;
      }
      if (fanLevel < 3) {
        fanLevel += 1;
        data_change();
      }
    } else if (checkTouchInCircle(x, y, auto_button_x, auto_botton_y,
                                  auto_botton_radius) == 1) {/////////////////auto press///////////////
      if (screenMode == 3) {
        screenMode = 2;
        fanMode = 0;
        isScreenRendered = 0;
        data_change();
      }

    } else if (checkTouchInCircle(x, y, manual_button_x,
                                  manual_botton_y, manual_botton_radius) == 1) {/////////////////manual press///////////////
      if (screenMode == 2) {
        screenMode = 3;
        fanMode = 1;
        isScreenRendered = 0;
        data_change();
      }
    } else if (checkTouchInCircle(x, y, settings_button_x,
                                  settings_botton_y, settings_botton_radius) == 1) {/////////////////setting press///////////////
      //go to setting mode
      isScreenRendered = 0;
      screenMode = 4 + isAutoShutdown;
    }
  }

}

void setting_screen_logic() {
  uint16_t decrease_max_dust_x = 40;
  uint16_t decrease_max_dust_y = 115;
  uint16_t decrease_max_dust_radius = 20;

  uint16_t inrease_max_dust_x = 172;
  uint16_t inrease_max_dust_y = 115;
  uint16_t inrease_max_dust_radius = 20;

  uint16_t decrease_time_x = 40;
  uint16_t decrease_time_y = 212;
  uint16_t decrease_time_radius = 20;

  uint16_t inrease_time_x = 151;
  uint16_t inrease_time_y = 212;
  uint16_t inrease_time_radius = 20;

  uint16_t back_button_x_R1 = 20;
  uint16_t back_button_y_R1 = 19;
  uint16_t back_button_x_R2 = 58;
  uint16_t back_button_y_R2 = 49;

  uint16_t auto_shutdown_x_R1 = 110;
  uint16_t auto_shutdown_y_R1 = 157;
  uint16_t auto_shutdown_x_R2 = 151;
  uint16_t auto_shutdown_y_R2 = 182;
  /////////////////////////////////////////////
  if (pressed) {
    prevMillis = millis();
    if (checkTouchInRectangle(x, y, back_button_x_R1,
                              back_button_y_R1, back_button_x_R2, back_button_y_R2)
        == 1) {//back press
      screenMode = 2 + fanMode;
      isScreenRendered = 0;
      ;
    } else if (checkTouchInCircle(x, y, decrease_max_dust_x,
                                  decrease_max_dust_y, decrease_max_dust_radius) == 1) {//decrease_max_dust
      if (maxDust > 1) {
        maxDust -= 1;
        data_change();
      }

    } else if (checkTouchInCircle(x, y, inrease_max_dust_x,
                                  inrease_max_dust_y, inrease_max_dust_radius) == 1) {//inrease_max_dust
      if (maxDust < 999) {
        maxDust += 1;
        data_change();
      }
    } else if (checkTouchInRectangle(x, y, auto_shutdown_x_R1,
                                     auto_shutdown_y_R1, auto_shutdown_x_R2, auto_shutdown_y_R2)
               == 1) {//auto_shutdown
      isScreenRendered = 0;
      isAutoShutdown += 1;
      isAutoShutdown %= 2;
      screenMode = 4 + isAutoShutdown;
      data_change();
    } else if (checkTouchInCircle(x, y, decrease_time_x,
                                  decrease_time_y, decrease_time_radius) == 1
               && isAutoShutdown == 0) {
      if (timeShutdown > 1) {
        timeShutdown -= 1;
        data_change();
      }
    } else if (checkTouchInCircle(x, y, inrease_time_x,
                                  inrease_time_y, inrease_time_radius) == 1
               && isAutoShutdown == 0) {
      if (timeShutdown < 1440) {
        timeShutdown += 1;
        data_change();
      }
    }
  }

}
///////////////////////////////////////////////////////////////////////////////////setting update///////////////////////////////////////////////////////////////////////////////////////////////
void main_screen_update() {
  uint16_t fan_level_x = 113;
  uint16_t fan_level_y = 231;
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK, tft.color24to16(0xDCD9D9));
  tft.drawString(String(fanLevel), fan_level_x, fan_level_y);
  //////
  uint16_t dust_value_x = 89;
  uint16_t dust_value_y = 63;
  char dustData[10];
  sprintf(dustData, "%03d", dustValue);
  tft.setTextSize(4);
  tft.setTextColor(TFT_WHITE, tft.color24to16(0x6CE278));
  tft.drawString(dustData, dust_value_x, dust_value_y);
}
//////////////////
void setting_screen_update() {
  ///////////////max dust///////////////
  uint16_t max_dust_x = 70;
  uint16_t max_dust_y = 107;
  char dustData[10];
  sprintf(dustData, "%03d", maxDust);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK, tft.color24to16(0xDCD9D9));
  tft.drawString(dustData, max_dust_x, max_dust_y);
  ///////////////time////////////////
  char timeData[10];
  sprintf(timeData, "%02d:%02d", timeShutdown / 60, timeShutdown % 60);
  if (!isAutoShutdown) {
    uint16_t time_x = 64;
    uint16_t time_y = 208;
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK, tft.color24to16(0xDCD9D9));
    tft.drawString(timeData, time_x, time_y);
  } else {
    uint16_t time2_x = 134;
    uint16_t time2_y = 196;
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.drawString(timeData, time2_x, time2_y);
  }

}
/////////////////////////////////////////////////////////////////////////////////off_screen/////////////////////////////////////////////////////////////////////////////////////////////////////////
void off_screen() {
  if (!isScreenRendered) {
    tft.fillScreen(TFT_BLACK);
    isScreenRendered = 1;
    digitalWrite(TFT_LED,LOW);
  }
  off_screen_logic();
}
///////////////////////////////////////////////////////////////////////////////on_screen///////////////////////////////////////////////////////////////////////////////////////////////////////////
void on_screen() {
  if (!isScreenRendered) {
    tft.fillScreen(TFT_WHITE);
    drawJpeg("/on_screen.jpg", 0 , 0);
    isScreenRendered = 1;
    digitalWrite(TFT_LED,HIGH);
  }
  on_screen_logic();
}
///////////////////////////////////////////////////////////////////////////main_screen_auto///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main_screen_auto() {
  if (!isScreenRendered) {
    tft.fillScreen(TFT_WHITE);
    drawJpeg("/main_screen_auto.jpg", 0 , 0);
    isScreenRendered = 1;
    digitalWrite(TFT_LED,HIGH);
  }
  main_screen_logic();
  main_screen_update();
}
/////////////////////////////////////////////////////////////////////////////main_screen_manual/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void main_screen_manual() {
  if (!isScreenRendered) {
    tft.fillScreen(TFT_WHITE);
    drawJpeg("/main_screen_manual.jpg", 0 , 0);
    isScreenRendered = 1;
    digitalWrite(TFT_LED,HIGH);
  }
  main_screen_logic();
  main_screen_update();
}
///////////////////////////////////////////////////////////////////////////setting_screen_disable///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setting_screen_disable() {
  if (!isScreenRendered) {
    tft.fillScreen(TFT_WHITE);
    drawJpeg("/setting_screen_disable.jpg", 0 , 0);
    isScreenRendered = 1;
  }
  setting_screen_logic();
  setting_screen_update();
}
//////////////////////////////////////////////////////////////////////////setting_screen_enable////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setting_screen_enable() {

  if (!isScreenRendered) {
    tft.fillScreen(TFT_WHITE);
    drawJpeg("/setting_screen_enable.jpg", 0 , 0);
    isScreenRendered = 1;
  }
  setting_screen_logic();
  setting_screen_update();
}
///////////////////////////////////////////////////////////////////////////screen_controller///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void screen_controller() {
  pressed = false;

  if (millis() - prevMillis > timeDebounce) {
    pressed = tft.getTouch(&x, &y);
  }
  //////////////////////////////////check screen mode//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (isOn == 0) {
    if (screenMode == 0) {
      off_screen();
    } else if (screenMode == 1) {
      on_screen();
    }
  } else {
    if (screenMode == 2) {
      main_screen_auto();
    } else if (screenMode == 3) {
      main_screen_manual();
    } else if (screenMode == 4) {
      setting_screen_disable();
    } else if (screenMode == 5) {
      setting_screen_enable();
    }
  }

/////////////set from another device/////////////
  if (isOn) {
    if (screenMode < 2) {
      screenMode = 2 + fanMode;
      isScreenRendered = 0;
    }
  }else{
    if (screenMode >= 2) {
      screenMode = 0;
      isScreenRendered = 0;
    }
  }
 //////////////////////
 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
