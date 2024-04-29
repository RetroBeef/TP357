#pragma once
#include <BLEAddress.h>
#include <BLEAdvertisedDevice.h>

#include <functional>

class ScannableBleDevice{
private:
protected:
    BLEAddress address;
    std::function<void(BLEAdvertisedDevice)> scanCallback;
public:
    explicit ScannableBleDevice(const BLEAddress& address, std::function<void(BLEAdvertisedDevice)> scanCallback) : address(address), scanCallback(scanCallback){}
    virtual ~ScannableBleDevice(){}
    inline BLEAddress getAddress() const {
      return address;
    }
    inline std::function<void(BLEAdvertisedDevice)> getScanCallback(){
      return scanCallback;
    }
};
