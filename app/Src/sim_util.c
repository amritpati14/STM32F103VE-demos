#include <string.h>
#include "sim_util.h"
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;

static uint8_t SIM7100_Raw[256] = {0};
static uint8_t SIM7100_RawPtr = 0;
static uint8_t new_echo = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(SIM7100_Raw[SIM7100_RawPtr]=='\n')
  {
    if(strnstr(SIM7100_Raw,"OK",SIM7100_RawPtr))
    {
      new_echo = 1;
      return;
    }
    if(strnstr(SIM7100_Raw,"ERROR",SIM7100_RawPtr))
    {
      new_echo = 2;
      return;
    }
  }
  SIM7100_RawPtr++;
  HAL_UART_Receive_IT(huart,SIM7100_Raw+SIM7100_RawPtr,1);
}

int8_t sim_send_command(const uint8_t* cmd,uint8_t** response)
{
  SIM7100_RawPtr = 0;
  new_echo = 0;
  HAL_UART_Receive_IT(&huart2,SIM7100_Raw+SIM7100_RawPtr,1);
  HAL_UART_Transmit_IT(&huart2,(uint8_t*)cmd,strlen(cmd));
  while(!new_echo);
  if(new_echo == 1)
  {
    *response = SIM7100_Raw;
    new_echo = 0;
    return 0;
  }else if(new_echo == 2)
  {
    *response = NULL;
    new_echo = 0;
    return -1;
  }
}