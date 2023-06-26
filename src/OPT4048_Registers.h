#pragma once
#include "Arduino.h"

#define OPT4048_ADDR_HIGH 0x45 // Default
#define OPT4048_ADDR_LOW 0x44
#define OPT4048_ADDR_SDA 0x46
#define OPT4048_ADDR_SCL 0x45

/// @brief OPT4048 Register for Exponent and Result (MSB) for Channel 0
#define SFE_OPT4048_REGISTER_EXP_RES_CH0 0x00
typedef union {
    struct
    {
        uint8_t exponent_ch0 : 4;
        uint16_t result_msb_ch0 : 12;
    };
    uint16_t word;

} opt4048_reg_exp_res_ch0_t;

/// @brief OPT4048 Register for Result (LSB), Counter, and CRC for Channel 0
#define SFE_OPT4048_REGISTER_RES_CNT_CRC_CH0 0x01
typedef union {
    struct
    {
        uint8_t result_lsb_ch0 : 8;
        uint8_t counter_ch0 : 4;
        uint8_t crc_ch0 : 4;
    };
    uint16_t word;

} opt4048_reg_res_cnt_crc_ch0_t;

/// @brief OPT4048 Register for Exponent and Result (MSB) for Channel 1
#define SFE_OPT4048_REGISTER_EXP_RES_CH1 0x02
typedef union {
    struct
    {
        uint8_t exponent_ch1 : 4;
        uint16_t result_msb_ch1 : 12;
    };
    uint16_t word;

} opt4048_reg_exp_res_ch1_t;

/// @brief OPT4048 Register for Result (LSB), Counter, and CRC for Channel 1
#define SFE_OPT4048_REGISTER_RES_CNT_CRC_CH1 0x03
typedef union {
    struct
    {
        uint8_t result_lsb_ch1 : 8;
        uint8_t counter_ch1 : 4;
        uint8_t crc_ch1 : 4;
    };
    uint16_t word;

} opt4048_reg_res_cnt_crc_ch1_t;

/// @brief  OPT4048 Register for Exponent and Result (MSB) for Channel 2
#define SFE_OPT4048_REGISTER_EXP_RES_CH2 0x04
typedef union {
    struct
    {
        uint8_t exponent_ch2 : 4;
        uint16_t result_msb_ch2 : 12;
    };
    uint16_t word;

} opt4048_reg_exp_res_ch2_t;

/// @brief OPT4048 Register for Result (LSB), Counter, and CRC for Channel 2
#define SFE_OPT4048_REGISTER_RES_CNT_CRC_CH2 0x05
typedef union {
    struct
    {
        uint8_t result_lsb_ch2 : 8;
        uint8_t counter_ch2 : 4;
        uint8_t crc_ch2 : 4;
    };
    uint16_t word;

} opt4048_reg_res_cnt_crc_ch2_t;

/// @brief OPT4048 Register for Exponent and Result (MSB) for Channel 3
#define SFE_OPT4048_REGISTER_EXP_RES_CH3 0x06
typedef union {
    struct
    {
        uint8_t exponent_ch3 : 4;
        uint16_t result_msb_ch3 : 12;
    };
    uint16_t word;

} opt4048_reg_exp_res_ch3_t;

/// @brief  OPT4048 Register for Result (LSB), Counter, and CRC for Channel 3
#define SFE_OPT4048_REGISTER_RES_CNT_CRC_CH3 0x07
typedef union {
    struct
    {
        uint8_t result_lsb_ch3 : 8;
        uint8_t counter_ch3 : 4;
        uint8_t crc_ch3 : 4;
    };
    uint8_t word;

} opt4048_reg_res_cnt_crc_ch3_t;

/// @brief OPT4048 Register for Threshold  Exponent and Result - Low
#define SFE_OPT4048_REGISTER_THRESH_H_EXP_RES 0x08
typedef union {
    struct
    {
        uint8_t thresh_exp : 4;
        uint16_t thresh_result : 12;
    };
    uint16_t word;

} opt4048_reg_thresh_exp_res_low_t;

/// @brief OPT4048 Register for Threshold Exponent and Threshold Result - High
#define SFE_OPT4048_REGISTER_THRESH_L_EXP_RES 0x09
typedef union {
    struct
    {
        uint8_t thresh_exp : 4;
        uint16_t thresh_result : 12;
    };
    uint16_t word;

} opt4048_reg_thresh_exp_res_high_t;

/// @brief OPT4048 Register that controls the main functions of the device.
#define SFE_OPT4048_REGISTER_CONTROL 0x0A
typedef union {
    struct
    {
        uint8_t qwake : 1;
        uint8_t reserved : 1;
        uint8_t range : 4;
        uint8_t conversion_time : 4;
        uint8_t op_mode : 2;
        uint8_t latch : 1;
        uint8_t int_pol : 1;
        uint8_t fault_count : 2;
    };
    uint16_t word;
} opt4048_reg_control_t;

/// @brief OPT4048 Register with settings for the interrupt pin.
#define SFE_OPT4048_REGISTER_INT_CONTROL 0x0B
typedef union {
    struct
    {
        uint8_t threshold_ch_sel : 8;
        uint8_t int_dir : 1;
        uint8_t int_cfg : 2;
        uint8_t reserved : 1;
        uint8_t i2c_burst : 1;
    };
    uint16_t word;

} opt4048_reg_int_control_t;

/// @brief OPT4048 register containing various status flags.
#define SFE_OPT4048_REGISTER_FLAGS 0x0C
typedef union {
    struct
    {
        uint16_t reserved : 12;
        uint8_t overload_flag : 1;
        uint8_t conv_ready_flag : 1;
        uint8_t flag_high : 1;
        uint8_t flag_low : 1;
    };
    uint16_t word;

} opt4048_reg_flags_t;

/// @brief  OPT4048 Register containing the device ID.
#define SFE_OPT4048_REGISTER_DEVICE_ID 0x0D
typedef union {
    struct
    {
        uint16_t reserved : 2;
        uint8_t DIDL : 2;
        uint16_t DIDH : 12;
    };
    uint16_t word;

} opt4048_reg_device_id_t;

