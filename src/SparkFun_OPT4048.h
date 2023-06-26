#pragma once
#include "sfe_bus.h"
#include "sfe_opt4048.h"
#include <Wire.h>

class SparkFun_OPT4048 : public QwOpt4048
{

  public:
    SparkFun_OPT4048(){};

    ///////////////////////////////////////////////////////////////////////
    // begin()
    //
    // This method is called to initialize the opt4048 library and connect to
    // the opt4048 device. This method must be called before calling any other method
    // that interacts with the device.
    //
    // This method follows the standard startup pattern in SparkFun Arduino
    // libraries.
    //
    //  Parameter   Description
    //  ---------   ----------------------------
    //  wirePort    optional. The Wire port. If not provided, the default port is used
    //  address     optional. I2C Address. If not provided, the default address is used.
    //  retval      true on success, false on startup failure
    //
    // This methond is overridden, implementing two versions.
    //
    // Version 1:
    // User skips passing in an I2C object which then defaults to Wire.
    bool begin(uint8_t deviceAddress = OPT4048_ADDR_HIGH)
    {
        // Setup  I2C object and pass into the superclass
        setCommunicationBus(_i2cBus, deviceAddress);

        // Initialize the I2C buss class i.e. setup default Wire port
        _i2cBus.init();

        // Initialize the system - return results
        return this->QwOpt4048::init();
    }

    // Version 2:
    // User passes in an I2C object and an address (optional).
    bool begin(TwoWire &wirePort, uint8_t deviceAddress = OPT4048_ADDR_HIGH)
    {
        // Setup  I2C object and pass into the superclass
        setCommunicationBus(_i2cBus, deviceAddress);

        // Give the I2C port provided by the user to the I2C bus class.
        _i2cBus.init(wirePort, true);

        // Initialize the system - return results
        return this->QwOpt4048::init();
    }

  private:
    // I2C bus class
    sfe_OPT4048::QwI2C _i2cBus;
};
