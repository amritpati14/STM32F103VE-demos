#include <string.h>
#include "SIM_Util.h"
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;

static SIM_Util_t sim_util;

SIM_OP_RESULT SIM_SendCommand(const uint8_t* cmd,uint8_t* response)
{
  HAL_UART_Receive_IT(&huart2,SIM7100_Raw+SIM7100_RawPtr,1);
  HAL_UART_Transmit_IT(&huart2,(uint8_t*)cmd,strlen(cmd));

  return SIM_OP_SUCCESS;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  SIM7100_RawPtr++;
  HAL_UART_Receive_IT(huart,SIM7100_Raw+SIM7100_RawPtr,1);
}