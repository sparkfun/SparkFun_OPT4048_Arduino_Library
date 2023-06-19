#include "OPT4048_Registers.h"
#include "sfe_bus.h"
#include <Wire.h>


class QwOpt4048
{
    public:
    
        QwOpt4048() : _i2cAddress{0}, _i2cPort{nullptr} {};

        bool init();
        bool isConnected();
        uint16_t getDeviceID();

        void setCommunicationBus(sfe_OPT4048::QwDeviceBus *theBus, uint8_t i2cAddress);

        int32_t writeRegisterRegion(uint8_t address, uint8_t offset, const uint8_t *data, uint16_t length = 1);
        int32_t readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes = 1);

        bool setQwake(opt4048_control_reg_t mode);
        bool getQwake(opt4048_control_reg_t *mode);

        bool setRange(opt4048_control_reg_t range);
        bool getRange(opt4048_control_reg_t *range);

        bool setConversionTime(opt4048_control_reg_t time);
        bool getConversionTime(opt4048_control_reg_t *time);

        bool setOperationMode(opt4048_control_reg_t mode);
        bool getOperationMode(opt4048_control_reg_t *mode);

        bool setIntLatch(opt4048_control_reg_t latch);
        bool getIntLatch(opt4048_control_reg_t *latch);

        bool setIntPolarity(opt4048_control_reg_t polarity);
        bool getIntPolarity(opt4048_control_reg_t *polarity);

        bool setFaultCount(opt4048_control_reg_t count);
        bool getFaultCount(opt4048_control_reg_t *count);

        bool setThresholdChannel(opt4048_control_reg_t channel);
        bool getThresholdChannel(opt4048_control_reg_t *channel);

        bool setIntDirection(opt4048_int_control_t direction);
        bool getIntDirection(opt4048_int_control_t *direction);

        bool setIntMechanism(opt4048_int_control_t mechanism); 
        bool getIntMechanism(opt4048_int_control_t *mechanism); 

        bool setI2CBurst(opt4048_control_reg_t burst);
        bool getI2CBurst(opt4048_control_reg_t *burst);

        bool getColorCh0(uint16_t *color);

    private:

		sfe_OPT4048::QwDeviceBus *_sfeBus; 
		uint8_t _i2cAddress;
};