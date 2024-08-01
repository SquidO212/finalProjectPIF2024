/*

  HelloWorld.ino

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
//U8G2_NULL u8g2(U8G2_R0);	// null device, a 8x8 pixel display which does nothing
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 12, /* dc=*/ 4, /* reset=*/ 6);	// Arduboy (Production, Kickstarter Edition)
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_3W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* reset=*/ 8);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);  // same as the NONAME variant, but may solve the "every 2nd line skipped" problem


// End of constructor list
String command = "Thong Beo";
unsigned long OLED_DISPLAY = 0;
unsigned long OLED_TIME_B = 0;
unsigned long OLED_TIME = 0;
const char FirstA[20] = "HELLO";
const char SecondA[20] = "WE";
const char ThirdA[20] = "ARE";
const char FourthA[20] = "GROUP";
bool isProcessing = true;
bool passIsCorrect = false;
// int duration = millis() - timer;
const char FifthA[20] = " 4 ";  // phuoc
const char SixthA[20] = "linh";
const char SeventhA[20] = "Welcome";
const uint8_t OLED_WIDTH = 128;
const uint8_t OLED_HEIGHT = 64;
const uint8_t CAL_VAL = 5;
uint8_t width = 0;
void setup() {
  u8g2.begin();
}

void loop() {

  // for (int NumberOfClaps = 0; NumberOfClaps <= 6; NumberOfClaps++) {
  //   displayNumberAnimationPlay(NumberOfClaps);
  //   delay(500);
  // }
  NotWelcomeAnimation();
  // PassWordSetting() ;
}
void welcomAnimationPlay() {
  if (millis() - OLED_DISPLAY >= 0 && millis() - OLED_DISPLAY <= 1200) {
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




  } else if (millis() - OLED_DISPLAY > 1200 && millis() - OLED_DISPLAY <= 2500) {
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
  } else if (millis() - OLED_DISPLAY > 2500 && millis() - OLED_DISPLAY <= 2900) {
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
  } else if (millis() - OLED_DISPLAY > 2900 && millis() - OLED_DISPLAY <= 3400) {
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

  else if (millis() - OLED_DISPLAY > 3400 && millis() - OLED_DISPLAY <= 3600) {
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
  } else if (millis() - OLED_DISPLAY > 3600 && millis() - OLED_DISPLAY <= 3800) {
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
  } else if (millis() - OLED_DISPLAY > 3800 && millis() - OLED_DISPLAY <= 4000) {
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
  } else if (millis() - OLED_DISPLAY > 4000 && millis() - OLED_DISPLAY <= 4200) {
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
  } else if (millis() - OLED_DISPLAY > 4200 && millis() - OLED_DISPLAY <= 4400) {
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
  } else if (millis() - OLED_DISPLAY > 4400 && millis() - OLED_DISPLAY <= 4600) {
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
  } else if (millis() - OLED_DISPLAY > 4600 && millis() - OLED_DISPLAY <= 4800) {
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
  } else if (millis() - OLED_DISPLAY > 4800 && millis() - OLED_DISPLAY <= 5000) {
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
  } else if (millis() - OLED_DISPLAY > 5000 && millis() - OLED_DISPLAY <= 5500) {
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
  } else if (millis() - OLED_DISPLAY > 5500) {
    u8g2.clearBuffer();

    OLED_DISPLAY = millis();
  }
}
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

  else if (millis() - OLED_DISPLAY > 11000) {
    u8g2.clearBuffer();

    OLED_DISPLAY = millis();
  }
}
