/*
 * delayus.c
 *
 *  Created on: Jan 8, 2025
 *      Author: user
 */
#include "delayus.h"

void delay_us(uint32_t us)
{
  HAL_TIM_Base_Start(&htim11);

  __HAL_TIM_SET_COUNTER(&htim11, 0);

  while(__HAL_TIM_GET_COUNTER(&htim11) < us);

  HAL_TIM_Base_Stop(&htim11);
}
