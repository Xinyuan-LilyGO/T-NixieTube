#include <TFT_eSPI.h>
#include <SPI.h>

//因为ESP32程序储存空间有限，为保证程序其他功能的正常运行//
//建议只选用一种辉光管字体类型，请注释掉其中一个.h文件//
#include "NixietuberNumber_A.h"
//#include "NixietuberNumber_B.h"

TFT_eSPI tft = TFT_eSPI(135, 240);

void LCDtest()
{
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("White text");
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.println("Red text");
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Green text");
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println("Blue text");
}


void NixieTubeNumber_A()
{
  tft.pushImage(0, 0,  135, 240, ZeroA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, OneA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, TwoA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, ThreeA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, FourA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, FiveA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, SixA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, SevenA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, EightA);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, NineA);
  delay(1000);
}
/*
void NixieTubeNumber_B()
{

  tft.pushImage(0, 0,  135, 240, ZeroB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, OneB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, TwoB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, ThreeB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, FourB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, FiveB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, SixB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, SevenB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, EightB);
  delay(1000);
  tft.pushImage(0, 0,  135, 240, NineB);
  delay(1000);
}*/

void setup() {

  Serial.begin(115200);
  Serial.println("Start");
  
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextDatum(MC_DATUM);
  tft.setCursor(0, 0, 4);
  tft.println("Intialised default\n");
  delay(500);
  //纠正图像字节顺序，确保颜色显示正常
  tft.setSwapBytes(true);
  LCDtest();
  delay(1000);
  
}

void loop() {
  
    NixieTubeNumber_A();
    //NixieTubeNumber_B();
  
}
