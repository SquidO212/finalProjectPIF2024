

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6_hHCajkI"
#define BLYNK_TEMPLATE_NAME "Smart Lock"
#define BLYNK_TEMPLATE_AUTH "-MGkzlmrHl5d-8hbpisqimzyavI4-myE"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEBeacon.h>
#include <BLEUtils.h>
#include <Arduino.h>
#include <BLEEddystoneURL.h>
#include <BLEEddystoneTLM.h>

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);  // same as the NONAME variant, but may solve the "every 2nd line skipped" problem

const int soundPin = 19;
const int MOTOR_IN1 = 25;
const int MOTOR_IN2 = 26;
//const int BTN = 26;
const int solenoidPin = 27;
const int TimeWaiting = 5000;
//const int rumblePin = 23;
const int IR_SENSOR = 35;
unsigned long LooptimeElasped;
unsigned long LooptimeLast;
unsigned long LooptimeCurrent;
int cycle = 15000;
int result;
int SAMPLE_TIME = 200;
int clapInx = 0;
int clapChecked[6];
int ADDRESS;
int SumUpValue = 0;
bool allowTrig = false;
bool solenoidOpen = false;
bool solenoidCloseAllow = false;
//bool knockAllow = false;
int averageValue = 0;
volatile unsigned long TRUE;
volatile unsigned long TEST;
unsigned long timer = 0;
unsigned long timer4 = 0;
unsigned long timeCurrent;
unsigned long timeLast = 0;
unsigned long timer5 = 0;
unsigned long timer6 = 0;
unsigned long averageCounting = 0;
unsigned long timeElapsed;
unsigned long LooptimeLastPass = 0;
unsigned long realTimeCurrent = 0;
unsigned long realTimeLast = 0;
unsigned long realTimeElasped = 0;
unsigned long motortiming = 0;
unsigned long REAL_TIME = 200;
unsigned long durationLast = 0;
unsigned long durationCurrent;
unsigned long durationElapsed = 0;
int accecptableTime = 2000;
int averageTestVal = 0;

bool passEqually = false;  // KIỂM TRA XEM PASSWORD CÓ GIỐNG NHAU KHÔNG

bool DEFAULT_ANI_ALLOW = true;
int Number_Of_Claps = 0;
int TimingArray[6];
int TimingTestArray[6];
int realbuffer;
int realValueSelf;
int realClapCount = 0;
unsigned long duration;
const int MIN_SENS = 350;
const int MAX_SENS = 900;
const int MIN_SENS_B = 901;
const int MAX_SENS_B = 1100;
const int KNOCK_MIN = 500;
const int KNOCK_MAX = 800;

// --------------------------------- KHAI BÁO BIẾN TOÀN CỤC CỦA APP + DETECT ESP32 NEARBY --------------------------------

String KEY_UUID = "2d7a9f0c-e0e8-4cc9-a71b-a21db2d034a1";  // KEY BLUETOOTH ESP32 PHÁT RA TÍN HIỆU.
bool device_In_Family = false, isSpamming = true;

int CountingToReset = 0;

int count = -1, timeAllowedDangerous = 30000, timeAllowedSafe = 6000;

//
char ssid[] = "Luan Tran 2.4G";
char pass[] = "luantran1997";

const int PIN = 2;
const int CUTOFF = -50;

// --------------------------------------------------------------------------------------------------

// --------------------------------- KHAI BÁO BIẾN TOÀN CỤC MỚI + BỊ THAY ĐỔI --------------------------------

bool isMotorClosing = false, isPossibleToCreate = false, motorDefault = true;

unsigned long DoorStateElapsed = 0;  // THỜI GIAN IR SENSOR PHÁT HIỆN CỬA CHƯA ĐƯỢC ĐÓNG

// --------------------------------------------------------------------------------------------------
int accecptableVal = 250;
int NewArray[0];
int clapCount = 0;
int clapArray[6];
int distance;
int SumUpTestVal = 0;
int samplebuffer;
int rumblebuffer;
int rumbleValue = 0;
int valueCheck;
const int echo = 33;
int valueSelf;
volatile int realvalue;
const int trig = 18;
int indexCompared = 0;
int MEASURE;
int TEST_MEASURE;
unsigned long OLED_DISPLAY = 0;
unsigned long OLED_TIME_B = 0;
unsigned long OLED_TIME_C = 0;
unsigned long OLED_TIME = 0;
const char FirstA[20] = "HELLO";
const char SecondA[20] = "WE";
const char ThirdA[20] = "ARE";
const char FourthA[20] = "GROUP";
bool isProcessing = true;
bool passIsCorrect = false;
// int duration = millis() - timer;
const char FifthA[20] = " 4 ";
const char SixthA[20] = "linh";
const char SeventhA[20] = "Welcome";
const uint8_t OLED_WIDTH = 128;
const uint8_t OLED_HEIGHT = 64;
const uint8_t CAL_VAL = 5;
uint8_t width = 0;
void setup() {
  Blynk.begin(BLYNK_TEMPLATE_AUTH, ssid, pass);
  pinMode(PIN, OUTPUT);
  BLEDevice::init("Long name works now");
  BLEServer *pServer = BLEDevice::createServer();
  BLEDevice::startAdvertising();
  u8g2.begin();
  pinMode(soundPin, INPUT);
  pinMode(IR_SENSOR, INPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  // pinMode(rumblePin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  // pinMode(BTN, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(soundPin), timeInterrupt, FALLING);
}
void welcomAnimationPlay() {


  if (millis() - OLED_TIME_C >= 0 && millis() - OLED_TIME_C <= 1200) {
    u8g2.clearBuffer();



    // Draw a diagonal line from top-left corner to bottom-right corner
    u8g2.drawLine(CAL_VAL, 1, OLED_WIDTH - CAL_VAL, 1);
    u8g2.drawLine(CAL_VAL, 2, OLED_WIDTH - CAL_VAL, 2);  //TOp
    u8g2.drawLine(CAL_VAL, OLED_HEIGHT - 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL, OLED_HEIGHT - 2, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 2);  //Bottom
    u8g2.drawLine(CAL_VAL, 1, CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL + 1, 1, CAL_VAL + 1, OLED_HEIGHT - 1);  //Left
    u8g2.drawLine(OLED_WIDTH - CAL_VAL, 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(OLED_WIDTH - CAL_VAL - 1, 1, OLED_WIDTH - CAL_VAL - 1, OLED_HEIGHT - 1);  //right
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SeventhA)) / 2, 22, SeventhA);


    u8g2.sendBuffer();




  } else if (millis() - OLED_TIME_C > 1200 && millis() - OLED_TIME_C <= 2500) {
    u8g2.clearBuffer();

    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 61, SixthA);

    u8g2.drawLine(34, 62, OLED_WIDTH - 34, 62);
    u8g2.drawLine(34, 63, OLED_WIDTH - 34, 63);
    // u8g2.drawLine

    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 2500 && millis() - OLED_TIME_C <= 2900) {
    u8g2.clearBuffer();
    //width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawLine(33, 12, 47, 12);
    u8g2.drawLine(33, 13, 47, 13);
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawLine(OLED_WIDTH - 47, 12, OLED_WIDTH - 33, 12);
    u8g2.drawLine(OLED_WIDTH - 47, 13, OLED_WIDTH - 33, 13);


    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 61, SixthA);

    u8g2.drawLine(34, 62, OLED_WIDTH - 34, 62);
    u8g2.drawLine(34, 63, OLED_WIDTH - 34, 63);
    // u8g2.drawLine

    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 2900 && millis() - OLED_TIME_C <= 3400) {
    u8g2.clearBuffer();
    //width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 61, SixthA);

    u8g2.drawLine(34, 62, OLED_WIDTH - 34, 62);
    u8g2.drawLine(34, 63, OLED_WIDTH - 34, 63);
    // u8g2.drawLine

    u8g2.sendBuffer();
  }

  else if (millis() - OLED_TIME_C > 3400 && millis() - OLED_TIME_C <= 3600) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 61, SixthA);
    // mouth
    u8g2.drawLine(34, 62, 54, 62);
    u8g2.drawLine(34, 63, 54, 63);
    u8g2.drawLine(OLED_WIDTH - 34, 62, 74, 62);
    u8g2.drawLine(OLED_WIDTH - 34, 63, 74, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 3600 && millis() - OLED_TIME_C <= 3800) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 61, SixthA);
    // mouth
    u8g2.drawLine(34, 62, 44, 62);
    u8g2.drawLine(34, 63, 44, 63);
    u8g2.drawLine(OLED_WIDTH - 34, 62, 84, 62);
    u8g2.drawLine(OLED_WIDTH - 34, 63, 84, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 3800 && millis() - OLED_TIME_C <= 4000) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 61, SixthA);
    // mouth
    // u8g2.drawLine(34, 62, 45, 62);
    // u8g2.drawLine(34, 63, 45, 63);
    // u8g2.drawLine(OLED_WIDTH - 34, 62,90, 62);
    // u8g2.drawLine(OLED_WIDTH - 34, 63,90, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 4000 && millis() - OLED_TIME_C <= 4200) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 65, SixthA);
    // mouth
    // u8g2.drawLine(34, 62, 45, 62);
    // u8g2.drawLine(34, 63, 3, 63);
    // u8g2.drawLine(OLED_WIDTH - 34, 62,90, 62);
    // u8g2.drawLine(OLED_WIDTH - 34, 63,90, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 4200 && millis() - OLED_TIME_C <= 4400) {
    u8g2.clearBuffer();
    width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 68, SixthA);
    // mouth
    // u8g2.drawLine(34, 62, 45, 62);
    // u8g2.drawLine(34, 63, 3, 63);
    // u8g2.drawLine(OLED_WIDTH - 34, 62,90, 62);
    // u8g2.drawLine(OLED_WIDTH - 34, 63,90, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 4400 && millis() - OLED_TIME_C <= 4600) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2, 75, SixthA);
    // mouth
    // u8g2.drawLine(34, 62, 45, 62);
    // u8g2.drawLine(34, 63, 3, 63);
    // u8g2.drawLine(OLED_WIDTH - 34, 62,90, 62);
    // u8g2.drawLine(OLED_WIDTH - 34, 63,90, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 4600 && millis() - OLED_TIME_C <= 4800) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    // u8g2.setFont(u8g2_font_ncenB10_tr);
    // u8g2.drawStr(width, 68, SixthA);
    // mouth
    // u8g2.drawLine(34, 62, 45, 62);
    // u8g2.drawLine(34, 63, 3, 63);
    // u8g2.drawLine(OLED_WIDTH - 34, 62,90, 62);
    // u8g2.drawLine(OLED_WIDTH - 34, 63,90, 63);
    u8g2.drawLine(34, 62, 44, 62);
    u8g2.drawLine(34, 63, 44, 63);
    u8g2.drawLine(OLED_WIDTH - 34, 62, 84, 62);
    u8g2.drawLine(OLED_WIDTH - 34, 63, 84, 63);


    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 4800 && millis() - OLED_TIME_C <= 5000) {
    u8g2.clearBuffer();
    // width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    // u8g2.setFont(u8g2_font_ncenB10_tr);
    // u8g2.drawStr(width, 61, SixthA);
    // mouth
    u8g2.drawLine(34, 62, 54, 62);
    u8g2.drawLine(34, 63, 54, 63);
    u8g2.drawLine(OLED_WIDTH - 34, 62, 74, 62);
    u8g2.drawLine(OLED_WIDTH - 34, 63, 74, 63);



    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 5000 && millis() - OLED_TIME_C <= 5500) {
    u8g2.clearBuffer();
    width = (OLED_WIDTH - u8g2.getStrWidth(SixthA)) / 2;
    // Draw a circle with center at (64, 32) and radius 20
    u8g2.drawCircle(40, 12, 7);  //eye
    u8g2.drawCircle(40, 12, 6);  //eye
    u8g2.drawCircle(40, 12, 1);  //eye
    u8g2.drawLine(OLED_WIDTH / 2 - 20, 1, OLED_WIDTH / 2 - 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 - 21, 1, OLED_WIDTH / 2 - 14, 6);

    u8g2.drawLine(OLED_WIDTH / 2 + 20, 1, OLED_WIDTH / 2 + 13, 6);
    u8g2.drawLine(OLED_WIDTH / 2 + 21, 1, OLED_WIDTH / 2 + 14, 6);

    u8g2.drawCircle(OLED_WIDTH - 40, 12, 7);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 6);  //eye
    u8g2.drawCircle(OLED_WIDTH - 40, 12, 1);  //eye

    // u8g2.setFont(u8g2_font_ncenB10_tr);
    // u8g2.drawStr(width, 61, SixthA);

    u8g2.drawLine(34, 62, OLED_WIDTH - 34, 62);
    u8g2.drawLine(34, 63, OLED_WIDTH - 34, 63);
    // u8g2.drawLine

    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_C > 5500) {
    u8g2.clearBuffer();

    OLED_TIME_C = millis();
  }
}  //done
void displayNumberAnimationPlay(int NumberOfClaps) {
  char IntergerToChar[2];
  String str;
  str = String(NumberOfClaps);
  str.toCharArray(IntergerToChar, 2);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB24_tr);
  u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(IntergerToChar)) / 2, 31, IntergerToChar);
  u8g2.sendBuffer();
}
void ProcessingWhileKnock() {
  if (isProcessing == true && millis() - OLED_TIME >= 0 && millis() - OLED_TIME <= 300) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth("In process")) / 2, 20, "In process");
    u8g2.sendBuffer();
  } else if (isProcessing == true && millis() - OLED_TIME > 300 && millis() - OLED_TIME <= 600) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth("In process.")) / 2, 20, "In process.");
    u8g2.sendBuffer();
  } else if (isProcessing == true && millis() - OLED_TIME > 600 && millis() - OLED_TIME <= 900) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth("In process..")) / 2, 20, "In process..");
    u8g2.sendBuffer();
  } else if (isProcessing == true && millis() - OLED_TIME > 900 && millis() - OLED_TIME <= 1200) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth("In process...")) / 2, 20, "In process...");
    u8g2.sendBuffer();
  } else {
    u8g2.clearBuffer();
    OLED_TIME = millis();
  }
}
void PassWordSetting() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth("Pass setting")) / 2, 22, "Pass setting");
  u8g2.sendBuffer();
}
void NotWelcomeAnimation() {
  if (millis() - OLED_TIME_B >= 0 && millis() - OLED_TIME_B <= 300 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" |")) / 2, 22, " |");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 300 && millis() - OLED_TIME_B <= 600 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth("  ")) / 2, 22, "  ");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 600 && millis() - OLED_TIME_B <= 900 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" |")) / 2, 22, " |");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 900 && millis() - OLED_TIME_B <= 1050 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" w|")) / 2, 22, " w|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1050 && millis() - OLED_TIME_B <= 1200 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wr|")) / 2, 22, " wr|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1200 && millis() - OLED_TIME_B <= 1350 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wro|")) / 2, 22, " wro|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1350 && millis() - OLED_TIME_B <= 1500 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wron|")) / 2, 22, " wron|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1500 && millis() - OLED_TIME_B <= 1650 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong|")) / 2, 22, " wrong|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1650 && millis() - OLED_TIME_B <= 1800 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong |")) / 2, 22, " wrong |");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1800 && millis() - OLED_TIME_B <= 1950 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong p|")) / 2, 22, " wrong p|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 1950 && millis() - OLED_TIME_B <= 2100 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong pa|")) / 2, 22, " wrong pa|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 2100 && millis() - OLED_TIME_B <= 2250 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong pas|")) / 2, 22, " wrong pas|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 2250 && millis() - OLED_TIME_B <= 2400 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong pass|")) / 2, 22, " wrong pass|");
    u8g2.sendBuffer();
  } else if (millis() - OLED_TIME_B > 2400 && millis() - OLED_TIME_B <= 3200 && passIsCorrect == false) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr((OLED_WIDTH - u8g2.getStrWidth(" wrong pass ")) / 2, 22, " wrong pass ");
    u8g2.sendBuffer();
  }

  else if (millis() - OLED_TIME_B > 3000) {
    u8g2.clearBuffer();
    OLED_TIME_B = millis();
  }
}
void DoorDetecting() {  // IR SENSOR DÙNG ĐỂ KIỂM TRA XEM CỬA CÓ ĐANG ĐÓNG HAY CHƯA

  unsigned long DoorOpeningTime = millis();

  if (!digitalRead(IR_SENSOR)) {  // KHÔNG CÓ VẬT CẢN PHÍA TRƯỚC ( CỬA MỞ )
    Serial.println("Cua mo");
    DoorStateElapsed = millis() - DoorOpeningTime;
  }
}

void defaultAnimationPlay() {
  if (millis() - OLED_DISPLAY >= 0 && millis() - OLED_DISPLAY <= 1000) {
    u8g2.clearBuffer();


    // Draw a diagonal line from top-left corner to bottom-right corner
    u8g2.drawLine(CAL_VAL, 1, OLED_WIDTH - CAL_VAL, 1);
    u8g2.drawLine(CAL_VAL, 2, OLED_WIDTH - CAL_VAL, 2);  //TOp
    u8g2.drawLine(CAL_VAL, OLED_HEIGHT - 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL, OLED_HEIGHT - 2, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 2);  //Bottom
    u8g2.drawLine(CAL_VAL, 1, CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL + 1, 1, CAL_VAL + 1, OLED_HEIGHT - 1);  //Left
    u8g2.drawLine(OLED_WIDTH - CAL_VAL, 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(OLED_WIDTH - CAL_VAL - 1, 1, OLED_WIDTH - CAL_VAL - 1, OLED_HEIGHT - 1);  //right
    u8g2.setFont(u8g2_font_ncenB10_tr);
    width = (OLED_WIDTH - u8g2.getStrWidth(FirstA)) / 2;
    u8g2.drawStr(width, 22, FirstA);


    u8g2.sendBuffer();
  } else if (millis() - OLED_DISPLAY > 1000 && millis() - OLED_DISPLAY <= 1500) {

    u8g2.clearBuffer();


    // Draw a diagonal line from top-left corner to bottom-right corner
    u8g2.drawLine(CAL_VAL, 1, OLED_WIDTH - CAL_VAL, 1);
    u8g2.drawLine(CAL_VAL, 2, OLED_WIDTH - CAL_VAL, 2);  //TOp
    u8g2.drawLine(CAL_VAL + 20, OLED_HEIGHT - 10, OLED_WIDTH - CAL_VAL - 20, OLED_HEIGHT - 10);
    u8g2.drawLine(CAL_VAL + 20, OLED_HEIGHT - 9, OLED_WIDTH - CAL_VAL - 20, OLED_HEIGHT - 9);  //Bottom
    u8g2.drawLine(CAL_VAL, 1, CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL + 1, 1, CAL_VAL + 1, OLED_HEIGHT - 1);  //Left
    u8g2.drawLine(OLED_WIDTH - CAL_VAL, 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(OLED_WIDTH - CAL_VAL - 1, 1, OLED_WIDTH - CAL_VAL - 1, OLED_HEIGHT - 1);  //right
    u8g2.setFont(u8g2_font_ncenB10_tr);
    width = (OLED_WIDTH - u8g2.getStrWidth(SecondA)) / 2;
    u8g2.drawStr(width, 22, SecondA);


    u8g2.sendBuffer();
  } else if (millis() - OLED_DISPLAY > 1500 && millis() - OLED_DISPLAY <= 2500) {

    u8g2.clearBuffer();


    // Draw a diagonal line from top-left corner to bottom-right corner
    width = (OLED_WIDTH - u8g2.getStrWidth(ThirdA)) / 2;
    u8g2.drawLine(CAL_VAL, 1, OLED_WIDTH - CAL_VAL, 1);
    u8g2.drawLine(CAL_VAL, 2, OLED_WIDTH - CAL_VAL, 2);  //TOp
    u8g2.drawLine(CAL_VAL, OLED_HEIGHT - 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL, OLED_HEIGHT - 2, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 2);  //Bottom
    u8g2.drawLine(width - 2, 1, width - 2, OLED_HEIGHT - 1);
    u8g2.drawLine(width - 2 + 1, 1, width - 2 + 1, OLED_HEIGHT - 1);  //Left
    u8g2.drawLine((OLED_WIDTH - CAL_VAL - width) + 6, 1, (OLED_WIDTH - CAL_VAL - width) + 6, OLED_HEIGHT - 1);
    u8g2.drawLine((OLED_WIDTH - CAL_VAL - 1 - width) + 6, 1, (OLED_WIDTH - CAL_VAL - 1 - width) + 6, OLED_HEIGHT - 1);  //right
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(width, 22, ThirdA);


    u8g2.sendBuffer();
  } else if (millis() - OLED_DISPLAY > 2500 && millis() - OLED_DISPLAY <= 3000) {

    u8g2.clearBuffer();


    // Draw a diagonal line from top-left corner to bottom-right corner
    width = (OLED_WIDTH - u8g2.getStrWidth(FourthA)) / 2;
    u8g2.drawLine(CAL_VAL + 20, 9, OLED_WIDTH - CAL_VAL - 20, 9);
    u8g2.drawLine(CAL_VAL + 20, 10, OLED_WIDTH - CAL_VAL - 20, 10);  //TOp
    u8g2.drawLine(CAL_VAL + 20, OLED_HEIGHT - 10, OLED_WIDTH - CAL_VAL - 20, OLED_HEIGHT - 10);
    u8g2.drawLine(CAL_VAL + 20, OLED_HEIGHT - 9, OLED_WIDTH - CAL_VAL - 20, OLED_HEIGHT - 9);  //Bottom  //Bottom
    u8g2.drawLine(CAL_VAL, 1, CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(CAL_VAL + 1, 1, CAL_VAL + 1, OLED_HEIGHT - 1);  //Left
    u8g2.drawLine(OLED_WIDTH - CAL_VAL, 1, OLED_WIDTH - CAL_VAL, OLED_HEIGHT - 1);
    u8g2.drawLine(OLED_WIDTH - CAL_VAL - 1, 1, OLED_WIDTH - CAL_VAL - 1, OLED_HEIGHT - 1);  //right
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(width, 22, FourthA);


    u8g2.sendBuffer();
  } else if (millis() - OLED_DISPLAY > 3000 && millis() - OLED_DISPLAY <= 4000) {

    u8g2.clearBuffer();


    // Draw a diagonal line from top-left corner to bottom-right corner
    width = (OLED_WIDTH - u8g2.getStrWidth(FifthA)) / 2;
    u8g2.drawLine(width, 1, OLED_WIDTH - width, 1);
    u8g2.drawLine(width, 2, OLED_WIDTH - width, 2);  //TOp
    u8g2.drawLine(width, OLED_HEIGHT - 1, OLED_WIDTH - width, OLED_HEIGHT - 1);
    u8g2.drawLine(width, OLED_HEIGHT - 2, OLED_WIDTH - width, OLED_HEIGHT - 2);  //Bottom
    u8g2.drawLine(width - 2, 1, width - 2, OLED_HEIGHT - 1);
    u8g2.drawLine(width - 2 + 1, 1, width - 2 + 1, OLED_HEIGHT - 1);  //Left
    u8g2.drawLine((OLED_WIDTH - CAL_VAL - width) + 6, 1, (OLED_WIDTH - CAL_VAL - width) + 6, OLED_HEIGHT - 1);
    u8g2.drawLine((OLED_WIDTH - CAL_VAL - 1 - width) + 8, 1, (OLED_WIDTH - CAL_VAL - 1 - width) + 8, OLED_HEIGHT - 1);  //right
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(width, 22, FifthA);


    u8g2.sendBuffer();
  }

  else if (millis() - OLED_DISPLAY > 4000) {
    u8g2.clearBuffer();

    OLED_DISPLAY = millis();
  }
}  //done


void runmysensor() {  // GỬI VỀ KHOẢNG CÁCH LIÊN TỤC CỦA HC-SR04.
  if (millis() - timer4 > 250) {
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance, ");
    Serial.println(distance);
    timer4 = millis();
  }
  if (isSpamming && DoorStateElapsed > timeAllowedSafe) {
    Serial.println("Theft Alert In Home");
    Blynk.logEvent("isdooropen", "Theres someone has just opened the door");
    isSpamming = false;
    // timeStarted = millis();
  }
  if (!isSpamming && DoorStateElapsed > timeAllowedDangerous) {
    Serial.println("Is closing the door");
    isMotorClosing = true;
  }
}

void motorRunning() {  // ĐIỀU KHIỂN MOTOR

  if (motorDefault) {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    motortiming = millis();
  } else if (passEqually && motorDefault == false) {
    if (millis() - motortiming <= 2000) {
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
    } else {
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
    }
  } else if (passEqually == false && motorDefault == false) {
    if (millis() - motortiming <= 2000) {
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
    } else {
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, LOW);
      solenoidCloseAllow = true;
    }
  }
}

void setbackcounter() {
  if (device_In_Family == 0) {
    clapCount = 0;
  }
}

BLYNK_WRITE(V2) {
  isPossibleToCreate = param.asInt();
  Serial.println("Change value successful");
}

void manufactureDataPrint(BLEAdvertisedDevice device) {
  if (device.haveManufacturerData() == true) {
    String strManufacturerData = device.getManufacturerData();

    uint8_t cManufacturerData[100];
    memcpy(cManufacturerData, strManufacturerData.c_str(), strManufacturerData.length());

    if (strManufacturerData.length() == 25 && cManufacturerData[0] == 0x4C && cManufacturerData[1] == 0x00) {
      Serial.println("Found an iBeacon!");
      BLEBeacon oBeacon = BLEBeacon();
      oBeacon.setData(strManufacturerData);
      Serial.printf("iBeacon Frame\n");
      Serial.printf(
        "ID: %04X Major: %d Minor: %d UUID: %s Power: %d\n", oBeacon.getManufacturerId(), ENDIAN_CHANGE_U16(oBeacon.getMajor()),
        ENDIAN_CHANGE_U16(oBeacon.getMinor()), oBeacon.getProximityUUID().toString().c_str(), oBeacon.getSignalPower());
    } else {
      Serial.println("Found another manufacturers beacon!");
      Serial.printf("strManufacturerData: %d ", strManufacturerData.length());
      for (int i = 0; i < strManufacturerData.length(); i++) {
        Serial.printf("[%x]", cManufacturerData[i]);
      }
      Serial.printf("\n");
    }
  }
}


void loop() {
  Blynk.run();
  runmysensor();
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(99);
  scan->start(1);
  BLEScanResults *results = scan->getResults();
  int best = CUTOFF;

  // Serial.println();
  // Serial.print("Bluetooth count: ");
  // Serial.println(results->getCount());
  // Serial.println("#################################################################");
  for (int i = 0; i < results->getCount(); i++) {
    BLEAdvertisedDevice device = results->getDevice(i);
    int rssi = device.getRSSI();

    // Serial.println("--------------------------------------");
    String strManufacturerData = device.getManufacturerData();

    uint8_t cManufacturerData[100];
    BLEBeacon oBeacon = BLEBeacon();

    memcpy(cManufacturerData, strManufacturerData.c_str(), strManufacturerData.length());
    if (strManufacturerData.length() == 25 && cManufacturerData[0] == 0x4C && cManufacturerData[1] == 0x00) {
      // Serial.printf("Device's %d rssi: ", i);
      // Serial.println(rssi);
      // Serial.println("Found an iBeacon!");
      // Serial.print("Name: ");
      // Serial.println(device.getName());
      oBeacon.setData(strManufacturerData);
      //  Serial.printf("iBeacon Frame\n");
      //   Serial.printf(
      //     "ID: %04X Major: %d Minor: %d UUID: %s Power: %d\n", oBeacon.getManufacturerId(), ENDIAN_CHANGE_U16(oBeacon.getMajor()),
      //     ENDIAN_CHANGE_U16(oBeacon.getMinor()), oBeacon.getProximityUUID().toString().c_str(), oBeacon.getSignalPower());
      // }
      // Serial.println("--------------------------------------");
    }

    String KEY = oBeacon.getProximityUUID().toString();

    if (rssi > best && rssi > CUTOFF && KEY == KEY_UUID) {
      best = rssi;
      // Serial.println("RSSI > CUTOFF");
      // Serial.print("ADDRESS: ");
      // Serial.println(device.getAddress().toString());
      // Serial.print("Name: ");
      // Serial.println(device.getName());
      // Serial.println(device.getServiceData());
    }
  }
  // Serial.println("#################################################################");
  device_In_Family = best > CUTOFF ? true : false;
  scan->clearResults();

  digitalWrite(PIN, device_In_Family);
  Serial.println("It is running");
  runmysensor();
  setbackcounter();
  while (isPossibleToCreate) {  // BẮT ĐẦU CÀI MẬT KHẨU GÕ CỬA.
    Serial.println("Start to change password");
    LooptimeLast = 0;
    averageTestVal = 0;
    SumUpTestVal = 0;
    passEqually = false;
    realClapCount = 0;
    timeCurrent = millis();
    LooptimeCurrent = millis();
    durationCurrent = millis();
    timeElapsed = timeCurrent - timeLast;
    LooptimeElasped = LooptimeCurrent - LooptimeLastPass;
    PassWordSetting();
    runmysensor();
    if (LooptimeElasped > cycle) {
      for (int resets = 0; resets <= clapCount; resets++) {
        clapArray[resets] = 0;
        TimingArray[resets] = 0;
      }
      clapCount = 0;
      Number_Of_Claps = 0;
      //knockAllow = false;
      rumblebuffer = 0;
      SumUpValue = 0;
      MEASURE = 0;
      Serial.println("Pass lock resets");
      LooptimeLastPass = LooptimeCurrent;
    }
    // if (clapCount > 6) {
    //   for (int resets = 0; resets <= clapCount; resets++) {
    //     clapArray[resets] = 0;
    //     TimingArray[resets] = 0;
    //   }
    //   clapCount = 0;
    //   Number_Of_Claps = 0;
    //   SumUpValue = 0;
    //   MEASURE = 0;
    //   Serial.println("Pass lock resets");
    //   LooptimeLastPass = LooptimeCurrent;
    // }
    if (LooptimeElasped >= TimeWaiting && allowTrig == true) {
      averageValue = SumUpValue / Number_Of_Claps;
      for (int averageIndex = 0; averageIndex <= Number_Of_Claps; averageIndex++) {
        clapArray[averageIndex] = averageValue;
      }
      Serial.println(averageValue);
      Serial.println("mainIntensity");
      // Number_Of_Claps = 0;
      SumUpValue = 0;
      rumblebuffer = 0;
      samplebuffer = 0;
      allowTrig = false;
    }

    if (digitalRead(soundPin) == 0) {
      samplebuffer++;
    }
    // if (digitalRead(rumblePin) == 0) {
    //   rumblebuffer++;
    // }
    // if (rumblebuffer >= 400) {
    //   knockAllow = true;
    // }


    if (timeElapsed > SAMPLE_TIME) {
      if ((samplebuffer >= MIN_SENS && samplebuffer <= MAX_SENS && clapCount <= 5) || (samplebuffer >= MIN_SENS_B && samplebuffer <= MAX_SENS_B && clapCount <= 5)) {
        if (samplebuffer >= MIN_SENS_B && samplebuffer <= MAX_SENS_B) {
          samplebuffer = 900;
        }
        Serial.println(rumblebuffer);
        valueCheck = samplebuffer;
        realvalue = valueCheck;
        allowTrig = true;
        SumUpValue += realvalue;
        LooptimeLastPass = millis();
        //Serial.println(valueCheck);
        //Serial.print(" ");
        //Serial.print(realvalue);
        //Serial.print(TRUE);
        Serial.print(realvalue);
        Serial.println(" intensity");
        if (clapCount == 0) {
          TRUE = 0;
          durationLast = millis();
        }
        TimingArray[clapCount] = TRUE;
        Serial.print(TimingArray[clapCount]);
        Serial.println(" duration");
        clapCount += 1;
        displayNumberAnimationPlay(clapCount);
        if (clapCount != 0) {
          Number_Of_Claps = clapCount;
          //Serial.println(Number_Of_Claps);
        }
        Serial.println(clapCount);
        MEASURE = clapCount;
        ADDRESS = 69;
        //Serial.println(clapCount);
        //  knockAllow = false;
      }
      samplebuffer = 0;
      rumblebuffer = 0;
      timeLast = timeCurrent;
    }
  }


  while (distance <= 25 && device_In_Family) {
    // GÕ MẬT KHẨU && DETECT ESP32 NEARBY INCLUDED
    // if ( !device_In_Family ) break;
    Serial.println("Getting password");
    LooptimeLastPass = 0;
    averageValue = 0;
    allowTrig = false;
    runmysensor();
    setbackcounter();
    durationCurrent = millis();
    realTimeCurrent = millis();
    LooptimeCurrent = millis();
    realTimeElasped = realTimeCurrent - realTimeLast;
    LooptimeElasped = LooptimeCurrent - LooptimeLast;
    if (LooptimeElasped > cycle) {
      for (int resets = 0; resets < realClapCount; resets++) {
        TimingTestArray[resets] = 0;
        clapChecked[resets] = 0;
      }
      Serial.println("resets Counter");
      realbuffer = 0;
      realClapCount = 0;
      SumUpTestVal = 0;
      TEST_MEASURE = 0;
      rumblebuffer = 0;
      LooptimeLast = LooptimeCurrent;
      // knockAllow = false;
    }
    if (digitalRead(soundPin) == 0) {
      realbuffer++;
    }
    // if (digitalRead(rumblePin) == 0) {
    //   rumblebuffer++;
    // }
    // if (rumblebuffer >= 400) {
    //   knockAllow = true;
    // }
    if (realTimeElasped >= REAL_TIME) {
      valueSelf = realbuffer;
      if ((valueSelf >= MIN_SENS && valueSelf <= MAX_SENS) || (valueSelf >= MIN_SENS_B && valueSelf <= MAX_SENS_B) && realClapCount >= 0) {
        // if (knockAllow == true) {
        if (valueSelf >= MIN_SENS_B && valueSelf <= MAX_SENS_B) {
          valueSelf = 900;
        }
        DEFAULT_ANI_ALLOW = false;
        realValueSelf = valueSelf;
        SumUpTestVal += realValueSelf;
        //Serial.println(realValueSelf);
        LooptimeLast = millis();
        realClapCount += 1;
        displayNumberAnimationPlay(realClapCount);
        TEST_MEASURE = realClapCount;
        if (realClapCount == 1) {
          TEST = 0;
          durationLast = millis();
        }
        if (TEST_MEASURE == MEASURE) {
          averageTestVal = SumUpTestVal / realClapCount;
          for (int indexTestVal = 0; indexTestVal <= realClapCount; indexTestVal++) {
            clapChecked[indexTestVal] = averageTestVal;
          }
          Serial.print(clapChecked[0]);
          Serial.println(" mainintensity");
        }
        TimingTestArray[realClapCount - 1] = TEST;
        Serial.print(realValueSelf);
        Serial.println(" intensity");
        Serial.print(TimingTestArray[realClapCount - 1]);
        Serial.println(" duration");

        ADDRESS = 68;
      }
      // }
      // knockAllow = false;
      realbuffer = 0;
      realTimeLast = realTimeCurrent;
    }
    if (realClapCount > 6) {
      for (int resets = 0; resets < realClapCount; resets++) {
        TimingTestArray[resets - 1] = 0;
        clapChecked[resets - 1] = 0;
      }
      Serial.println("resets Counter");
      SumUpTestVal = 0;
      realbuffer = 0;
      rumblebuffer = 0;
      realClapCount = 0;
      TEST_MEASURE = 0;
      LooptimeLast = LooptimeCurrent;
    }
    // knockAllow = false;
  }




  while (distance > 25) {  // KHOẢNG CÁCH TRÊN 25CM && HÀM SO SÁNH MẬT KHẨU
    Serial.println("Checking password");
    OLED_TIME_C = millis();
    OLED_TIME_B = millis();
    OLED_TIME = millis();
    OLED_DISPLAY = millis();
    LooptimeLastPass = 0;
    averageTestVal = 0;
    averageValue = 0;
    allowTrig = false;
    SumUpTestVal = 0;
    LooptimeLast = 0;
    runmysensor();
    setbackcounter();
    durationCurrent = millis();
    if (MEASURE == TEST_MEASURE) {
      for (int AnimationLooping = 0; AnimationLooping <= 3; AnimationLooping++) {
        ProcessingWhileKnock();
      }
      for (; indexCompared < realClapCount;) {
        if (abs(clapChecked[indexCompared] - clapArray[indexCompared]) <= accecptableVal) {
          passEqually = true;
        } else {
          passEqually = false;
          break;
        }
        indexCompared++;
      }
      indexCompared = 0;
      if (passEqually == true) {
        for (; indexCompared < realClapCount;) {
          if (abs(TimingTestArray[indexCompared] - TimingArray[indexCompared]) <= accecptableTime) {
            passEqually = true;
          } else {
            passEqually = false;
            break;
          }
          indexCompared++;
        }
      } else {
        passEqually = false;
      }

    } else {
      passEqually = false;
    }
    // [unsigned long solenoid = millis();]
    if (passEqually == true) {
      durationCurrent = millis();
      welcomAnimationPlay();
      digitalWrite(solenoidPin, HIGH);
      motorDefault = false;
      motorRunning();
      DoorDetecting();
      OLED_DISPLAY = millis();
      TEST_MEASURE = 0;
      DEFAULT_ANI_ALLOW = true;
      if (millis() - timer6 > 1000) {
        CountingToReset += 1;
        Serial.println("Door unlocked");
        realClapCount = 0;
        timer6 = millis();
        if (CountingToReset >= 6) {  // thoi gian hoat dong mo cua
          motortiming = millis();
          CountingToReset = 0;
          passEqually = false;

        }
      }

      //code for the servo to unlock da door
    } else if (passEqually == false) {
      durationCurrent = millis();
      if (DEFAULT_ANI_ALLOW == false) {
        for (int AnimationLoop = 0; AnimationLoop <= 3; AnimationLoop++) {
          NotWelcomeAnimation();
        }
        OLED_DISPLAY = millis();
        DEFAULT_ANI_ALLOW = true;
      }
      defaultAnimationPlay();
      motorRunning();
      motorDefault = true;
      if (solenoidCloseAllow  == true) {
        digitalWrite(solenoidPin, LOW);
        solenoidCloseAllow = false;
      }
      if (millis() - timer6 > 1000) {
        Serial.println("Door locked");
        Serial.println(MEASURE);
        Serial.println(TEST_MEASURE);
        realClapCount = 0;
        timer6 = millis();
      }
      //code for the buzzer to send the wrong notification
    }
  }




  //clapArray[clapCount] = NewArray[0];
}
void timeInterrupt() {

  if (ADDRESS == 69) {
    durationElapsed = durationCurrent - durationLast;
    durationLast = durationCurrent;
    if (clapCount <= 5) {

      TRUE = durationElapsed;
    }
    ADDRESS = 67;
  }
  if (ADDRESS == 68) {
    durationElapsed = durationCurrent - durationLast;
    durationLast = durationCurrent;
    if (realClapCount <= 5) {

      TEST = durationElapsed;
    }
    ADDRESS = 67;
  }
}

// LƯU Ý: ĐÂY LÀ CODE DÂY ĐEN.
