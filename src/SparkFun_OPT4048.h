#include "OPT4048_Registers.h"
#include "sfe_bus.h"
#include <Wire.h>

typedef struct 
{
   uint32_t x; 
   uint32_t y; 
   uint32_t z; 
   uint32_t l; 
   uint8_t counter; //Sample counter
   uint8_t CRC; 

} sfe_color_t;

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

        ///////////////////////////////////////////////////////////////////Device Settings
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

        bool getThresholdHigh(opt4048_exp_res_reg_high_t *threshold);
        bool getThresholdLow(opt4048_exp_res_reg_low_t *threshold);

        bool enableCRC(bool enable);

        ///////////////////////////////////////////////////////////////////Interrupt Settings
        bool setIntDirection(opt4048_int_control_t direction);
        bool getIntDirection(opt4048_int_control_t *direction);

        bool setIntMechanism(opt4048_int_control_t mechanism); 
        bool getIntMechanism(opt4048_int_control_t *mechanism); 

        bool setI2CBurst(opt4048_control_reg_t burst);
        bool getI2CBurst(opt4048_control_reg_t *burst);
        ///////////////////////////////////////////////////////////////////Color Information

        bool setOverflowFlag(opt4048_flags_t overflow);
        bool getOverflowFlag(opt4048_flags_t *overflow);

        bool setConvReadyFlag(opt4048_flags_t conversion);
        bool getConvReadyFlag(opt4048_flags_t *conversion);

        bool setTooBrightFlag(opt4048_flags_t bright);
        bool getTooBrightFlag(opt4048_flags_t *bright);

        bool setTooDimFlag(opt4048_flags_t dim);
        bool getTooDimFlag(opt4048_flags_t *dim);


        ///////////////////////////////////////////////////////////////////Color Information
        bool getADCCh0(uint32_t *chan0);
        bool getADCCh1(uint32_t *chan1);
        bool getADCCh2(uint32_t *chan2);
        bool getADCCh3(uint32_t *chan3);

        bool getLux(uint32_t *lux);

        bool getCIEx(uint32_t *CIEx);
        bool getCIEy(uint32_t *CIEx);

        bool getCCT(uint32_t *CCT);


    private:

		sfe_OPT4048::QwDeviceBus *_sfeBus; 
		uint8_t _i2cAddress;
        bool crcEnabled = false;
};