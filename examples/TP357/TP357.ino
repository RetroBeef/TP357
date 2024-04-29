#include <TP357.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <vector>

const char* tp357Address = "10:76:36:c1:72:0d";

uint8_t scanTime = 5;
BLEScan* pBLEScan;

std::vector<ScannableBleDevice*> scannableBleDevices;
ThermoPro* tp = 0;

class AdvertisedDeviceCallback: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      for(ScannableBleDevice* d : scannableBleDevices){
        d->getScanCallback()(advertisedDevice);
      }
    }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  tp = new ThermoPro(tp357Address);
  scannableBleDevices.push_back(tp);
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallback());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(40);
  pBLEScan->setWindow(30);
}

void loop() {
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  pBLEScan->clearResults();
  Serial.println(tp->toList());
}
