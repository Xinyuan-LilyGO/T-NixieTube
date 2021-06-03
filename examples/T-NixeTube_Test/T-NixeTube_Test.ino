

#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <IRremote.h>
#include <pcf8563.h>

#include "NixietuberNumber_A.h"

#define TOUCH_PIN   15
#define TOUCH_PWR   32
#define RTC_SDA     26
#define RTC_SCL     25
#define IR_RECV     13


uint32_t timeStamp;

IRrecv irrecv(IR_RECV);
PCF8563_Class rtc;
decode_results results;


TFT_eSPI tft = TFT_eSPI(135, 240);

bool touched()
{
    delay(100);
    return digitalRead(TOUCH_PIN) == HIGH;
}

void readIrrecv(uint32_t prev_value){
    switch (prev_value) 
      {
      case 0xFFA25D://off       
          Serial.println("off");
          break;
      case 0xFFA21D://MENU
          Serial.println("menu");
          break;
      case 0xFF22DD://TEST       
          Serial.println("test");
          break;
      case 0xFF02FD://+
          Serial.println("+");
          break;
      case 0xFFc23D://BACK      
          tft.pushImage(0, 0,  135, 240, lilygo); 
          Serial.println("back");
          break;
      case 0xFFE01F://←
          Serial.println("←");
          break;
      case 0xFFA857://PLAY
          break;
      case 0xFF906F://→
          Serial.println("→");
          break;
      case 0xFF6897://0
          tft.pushImage(0, 0,  135, 240, ZeroA);
          Serial.println("0");
          break;
      case 0xFF9867://-
          Serial.println("-");
          break;
      case 0xFFB04F://C
          Serial.println("C");
          break;
      case 0xFF30CF://1
          tft.pushImage(0, 0,  135, 240, OneA);
          Serial.println("1");
          break;
      case 0xFF18E7://2
          tft.pushImage(0, 0,  135, 240, TwoA);
          Serial.println("2");
          break;
      case 0xFF7A85://3
          tft.pushImage(0, 0,  135, 240, ThreeA);
          Serial.println("3");
          break;
      case 0xFF10EF://4
          tft.pushImage(0, 0,  135, 240, FourA);
          Serial.println("4");
          break;
      case 0xFF38C7://5        
          tft.pushImage(0, 0,  135, 240, FiveA);
          Serial.println("5");
          break;
      case 0xFF5AA5://6        
          tft.pushImage(0, 0,  135, 240, SixA);
          Serial.println("6");
          break;
      case 0xFF42BD://7
          tft.pushImage(0, 0,  135, 240, SevenA);
          Serial.println("7");
          break;
      case 0xFF4AB5://8
          tft.pushImage(0, 0,  135, 240, EightA);
          Serial.println("8");
          break;
      case 0xFF52AD://9              
          tft.pushImage(0, 0,  135, 240, NineA);
          Serial.println("9");         
          break;
      }
 }


void setup() {
  
  Serial.begin(115200);
  Serial.println("Start");
  
  /*Set touch Pin as input*/
  pinMode(TOUCH_PIN, INPUT);
  /*Touch chip power control*/
  pinMode(TOUCH_PWR, PULLUP);
  digitalWrite(TOUCH_PWR, HIGH);  
  
  /*RTC init*/
  Wire.begin(RTC_SDA, RTC_SCL);
  
  rtc.begin();
  
  Serial.println("Enabling IRin");
  
  irrecv.enableIRIn(); // Start the receiver
  
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
  tft.pushImage(0, 0,  135, 240, lilygo);


  rtc.setDateTime(2021, 6, 1, 12, 0, 0);
  struct tm timeinfo;
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void loop() {

   if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    readIrrecv(results.value);
    irrecv.resume(); // Receive the next value
    Serial.println(rtc.formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD_H_M_S));
   }
   if (touched()) {
            tft.fillScreen(TFT_BLACK);
            tft.setCursor(15, 40, 4);
            tft.println(rtc.formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD));
            tft.setCursor(25, 80, 4);
            tft.println(rtc.formatDateTime(PCF_TIMEFORMAT_HMS));
   }   
   
}
