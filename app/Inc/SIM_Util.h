#pragma once

#include <stdint.h>

#define SIM_RAW_BUF_SIZE  256

typedef struct{
  uint8_t sim_raw_buf[SIM_RAW_BUF_SIZE];
  uint16_t sim_raw_ptr;
}SIM_Util_t; 

typedef enum{
  SIM_OP_SUCCESS,
  SIM_OP_FAIL
}SIM_OP_RESULT; 

SIM_OP_RESULT SIM_SendCommand(const uint8_t* cmd,uint8_t* response);