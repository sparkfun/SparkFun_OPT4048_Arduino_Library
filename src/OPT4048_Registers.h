// read pdf and include register definitions
#ifndef SFE_OT4048_REGS_H
#define SFE_OT4048_REGS_H

#ifndef __BYTE_ORDER__
#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN 4321
#endif

#define OPT4048_ADDR_HIGH 0x45
#define OPT4048_ADDR_LOW 0x44
#define OPT4048_ADDR_SDA 0x46

#define SFE_OPT4048_EXP_RES_CH0 0x00

typedef union {
    struct
    {
        uint8_t exponent_ch0 : 4;
        uint16_t result_msb_ch0 : 12;
    };
    uint16_t expon_result_chan_zero_reg;

} opt4048_exp_res_ch0_reg_t;

#define SFE_OPT4048_RES_CNT_CRC_CH0 0x01

typedef union {
    struct
    {
        uint8_t result_lsb_ch0 : 8;
        uint8_t counter_ch0 : 4;
        uint8_t crc_ch0 : 4;
    };
    uint16_t channel_zero_reg;

} opt4048_res_cnt_crc_ch0_reg_t;

#define SFE_OPT4048_EXP_RES_CH1 0x02

typedef union {
    struct
    {
        uint8_t exponent_ch1 : 4;
        uint16_t result_msb_ch1 : 12;
    };
    uint16_t expon_result_chan_one_reg;

} opt4048_exp_res_ch1_reg_t;

#define SFE_OPT4048_RES_CNT_CRC_CH1 0x03

typedef union {
    struct
    {
        uint8_t result_lsb_ch1 : 8;
        uint8_t counter_ch1 : 4;
        uint8_t crc_ch1 : 4;
    };
    uint16_t channel_one_reg;

} opt4048_res_cnt_crc_ch1_reg_t;

#define SFE_OPT4048_EXP_RES_CH2 0x04

typedef union {
    struct
    {
        uint8_t exponent_ch2 : 4;
        uint16_t result_msb_ch2 : 12;
    };
    uint16_t expon_result_chan_two_reg;

} opt4048_exp_res_ch2_reg_t;

#define SFE_OPT4048_RES_CNT_CRC_CH2 0x05

typedef union {
    struct
    {
        uint8_t result_lsb_ch2 : 8;
        uint8_t counter_ch2 : 4;
        uint8_t crc_ch2 : 4;
    };
    uint16_t channel_two_reg;

} opt4048_res_cnt_crc_ch2_reg_t;

#define SFE_OPT4048_EXP_RES_CH3 0x06

typedef union {
    struct
    {
        uint8_t exponent_ch3 : 4;
        uint16_t result_msb_ch3 : 12;
    };
    uint16_t expon_result_chan_thr_reg;

} opt4048_exp_res_ch3_reg_t;

#define SFE_OPT4048_RES_CNT_CRC_CH3 0x07

typedef union {
    struct
    {
        uint8_t result_lsb_ch3 : 8;
        uint8_t counter_ch3 : 4;
        uint8_t crc_ch3 : 4;
    };
    uint16_t channel_thr_reg;

} opt4048_res_cnt_crc_ch3_reg_t;

#define SFE_OPT4048_THRESH_H_EXP_RES 0x08

typedef union {
    struct
    {
        uint8_t thresh_exp : 4;
        uint16_t thresh_result : 12;
    };
    uint16_t exp_thresh_reg;

} opt4048_thresh_exp_res_reg_l_t;

#define SFE_OPT4048_THRESH_L_EXP_RES 0x09

typedef union {
    struct
    {
        uint8_t thresh_exp : 4;
        uint16_t thresh_result : 12;
    };
} opt4048_thresh_exp_res_reg_h_t;

#define SFE_OPT4048_CONTROL 0x0A

typedef union {
    struct
    {
        uint8_t qwake : 1;
        uint8_t reserved : 1;
        uint8_t range : 1;
        uint8_t converstion_time : 1;
        uint8_t op_mode : 1;
        uint8_t latch : 1;
        uint8_t int_pol : 1;
        uint8_t fault_count : 1;
    };
} opt4048_control_reg_t;

#define SFE_OPT4048_INT_CONTROL 0x0B

typedef union {
    struct 
    {
        uint8_t threshold_ch_sel : 8;
        uint8_t int_dir : 2;
        uint8_t int_cfg : 2;
        uint8_t reserved : 1;
        uint8_t i2c_burst : 1;
    };
    
} opt4048_int_control_t;


#define SFE_OPT4048_FLAGS 0x0C

typedef union {
    struct 
    {
        uint16_t reserved : 12;
        uint8_t overload_flag : 2;
        uint8_t conv_ready_flag : 2;
        uint8_t flag_high : 1;
        uint8_t flag_low : 1;
    };
    
} opt4048_flags_t;

#define SFE_OPT4048_DEVICE_ID 0x0D

typedef union {
    struct 
    {
        uint16_t reserved : 2;
        uint8_t DIDL : 2;
        uint16_t DIDH : 12; 
    };
    
} opt4048_device_id_t;
#endif