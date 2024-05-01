#pragma once
#include <Arduino.h>
#include "ScannableBleDevice.h"
#include <cstdint>

#pragma pack(push,1)
typedef struct {
  uint8_t unk1;
  uint16_t temperature;
  uint8_t humidity;
  uint8_t unk2;
  uint8_t unk3;
} ble_temphumid_t;
#pragma pack(pop)

class ThermoPro : public ScannableBleDevice{
private:
protected:
  float temperature;
  uint8_t humidity;
  uint32_t lastSeen;
public:
  ThermoPro(const char* address);
  inline float getTemperature() const {
    return temperature;
  }
  inline uint8_t getHumidity() const {
    return humidity;
  }
  inline uint32_t getLastSeen() const {
    return lastSeen;
  }
  virtual ~ThermoPro(){}
  String toList();
};
