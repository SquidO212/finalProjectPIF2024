// LƯU Ý: ĐÂY LÀ CODE DÂY ĐEN. 



#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6_hHCajkI"
#define BLYNK_TEMPLATE_NAME "Smart Lock"
#define BLYNK_TEMPLATE_AUTH "-MGkzlmrHl5d-8hbpisqimzyavI4-myE"

#include<BlynkSimpleEsp32.h> 
#include<WiFi.h> 
#include<WiFiClient.h>
#include <BLEAdvertisedDevice.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEBeacon.h>
#include <BLEUtils.h>
#include <Arduino.h>
#include <BLEEddystoneURL.h>
#include <BLEEddystoneTLM.h>

String KEY_UUID = "2d7a9f0c-e0e8-4cc9-a71b-a21db2d034a1";
bool device_In_Family = false, changeStatusOpen = true, isSpamming = false; 


int count =-1,timeStarted, timeAllowedDangerous = 30000, timeAllowedSafe = 6000;

//
char ssid[] = "Connectify-me"; 
char pass[] = "qakimyw1"; 

const int PIN = 2;
const int CUTOFF = -60;

void setup() {
  Blynk.begin(BLYNK_TEMPLATE_AUTH,ssid,pass); 
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);
  BLEDevice::init("Long name works now");
  BLEServer *pServer = BLEDevice::createServer();
  BLEDevice::startAdvertising();
}
 
BLYNK_WRITE(V2)
{ 
    int buttonState = param.asInt(); 
    if ( buttonState && device_In_Family ) // Thay điều kiện ở đây thành nếu như ir sensor không cảm nhận được vật (tức cửa chưa đóng)
    {
      Serial.println("Time started changed"); 
      isSpamming = true; 
      timeStarted = millis(); 
      count =0 ; 
    }
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
          ENDIAN_CHANGE_U16(oBeacon.getMinor()), oBeacon.getProximityUUID().toString().c_str(), oBeacon.getSignalPower()
        );
      } 
      else 
      {
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
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  scan->setInterval(100);
  scan->setWindow(50);
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
  digitalWrite(PIN, best > CUTOFF ? HIGH : LOW);
  if( count == -1 )   Blynk.virtualWrite(V3, device_In_Family ? "Opening the door" : "Not success" ); 
  else 
  {
    if ( isSpamming && millis() - timeStarted > timeAllowedSafe ) 
    { 
      Serial.println("Theft Alert In Home"); 
      Blynk.logEvent("isdooropen","Theres someone has just opened the door"); 
      isSpamming = false; 
      timeStarted = millis(); 
    }
    if (!isSpamming && millis() - timeStarted > timeAllowedDangerous)
    {
      Serial.println("Is closing the door");
      changeStatusOpen = false; 
      Blynk.virtualWrite(V3,"Closing the door"); 

    }

  }
 

  
}
 
