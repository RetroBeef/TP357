#include "TP357.h"

namespace{
const uint8_t offsetInPayload = 19;
const uint8_t expectedPayloadSize = 39;
}

ThermoPro::ThermoPro(const char* address) : ScannableBleDevice(BLEAddress(address), 
  [this](BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getAddress() == this->address) {
      if (advertisedDevice.getPayloadLength() == expectedPayloadSize) {
        ble_temphumid_t* tempHumidData = (ble_temphumid_t*)(advertisedDevice.getPayload() + offsetInPayload);
        temperature = tempHumidData->temperature / 10.f;
        humidity = tempHumidData->humidity;
        lastSeen = millis();
      }
    }
  }){}

String ThermoPro::toList() {
  return "Air:\nTemperature: " + String(temperature, 2) + " °C\nHumidity: " + String(humidity) + "% rH\nlast seen: " + String(millis()-lastSeen) + "ms ago\n";
}

String ThermoPro::toJSON() {
    String jsonStr = "{";
    jsonStr += "\"add\":" + String(address.toString().c_str()) + ",";
    jsonStr += "\"air\":{";
    jsonStr += "\"temp\":{\"v\":" + String(temperature, 2) + ",\"u\":\"°C\"},";
    jsonStr += "\"hum\":{\"v\":" + String(humidity) + ",\"u\":\"% rH\"},";
    jsonStr += "}}";

    return jsonStr;
}
