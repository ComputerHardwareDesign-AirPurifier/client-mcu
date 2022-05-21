#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

void screen_init(){
  tft.init();
  delay(10);
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
}

void screen_controller(){
  if(screenMode==0){
    tft.fillScreen(TFT_WHITE);
  }else if(screenMode==1){
    tft.fillScreen(TFT_BLACK);
  }else if(screenMode==2){
    tft.fillScreen(TFT_RED);
  }
}
