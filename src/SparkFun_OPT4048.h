/* 
sfe_bus.cpp

SparkFun Tristimulus Color Sensor - OPT4048

Qwiic 1x1
* https://www.sparkfun.com/products/
Qwiic Mini
* https://www.sparkfun.com/products/

Repository:
* https://github.com/sparkfun/SparkFun_OPT4048_Arduino_Library

The MIT License (MIT)

Copyright (c) 2022 SparkFun Electronics
Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions: The
above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
"AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

License(http://opensource.org/licenses/MIT).

The following class defines Arduino specific class behavior for initializing 
devices. It inherits from the QwOpt4048 class wich defines the functions for 
interacting with the opt4048 IC. 
*/

#pragma once
#include "sfe_bus.h"
#include "sfe_opt4048.h"
#include <Wire.h>

class SparkFun_OPT4048 : public QwOpt4048
{

  public:
    SparkFun_OPT4048(){};

    /// @brief This method is called to initialize the QwOpt4048 library and connect to
    ///     the opt4048 device. This method must be called before calling any other method
    ///     that interacts with the device. This method follows the standard startup pattern 
    ///     in SparkFun Arduino libraries. This methond is overridden, implementing two versions.
    /// @param deviceAddress The I2C Address of the device if not provided, the default address is used.
    /// @return True on success, false on startup failure
    bool begin(uint8_t deviceAddress = OPT4048_ADDR_LOW)
    {
        // Setup  I2C object and pass into the superclass
        setCommunicationBus(_i2cBus, deviceAddress);

        // Initialize the I2C buss class i.e. setup default Wire port
        _i2cBus.init();

        // Initialize the system - return results
        return this->QwOpt4048::init();
    }

    /// @brief This method is called to initialize the QwOpt4048 library and connect to
    ///     the opt4048 device. This method must be called before calling any other method
    ///     that interacts with the device. This method follows the standard startup pattern 
    ///     in SparkFun Arduino libraries. This methond is overridden, implementing two versions.
    /// @param deviceAddress The I2C Address of the device if not provided, the default address is used.
    /// @wirePort The Wire port - Arduino specific. If not provided, the default port is used
    /// @return True on success, false on startup failure
    bool begin(TwoWire &wirePort, uint8_t deviceAddress = OPT4048_ADDR_LOW)
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
