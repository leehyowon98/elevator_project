/*
 * 7SEG.h
 *
 *  Created on: Jan 14, 2025
 *      Author: user
 */

#ifndef INC_7SEG_H_
#define INC_7SEG_H_

#include "stm32f4xx_hal.h"

// 세그먼트 핀 정의
#define SEG_A_PIN  GPIO_PIN_7
#define SEG_B_PIN  GPIO_PIN_6
#define SEG_C_PIN  GPIO_PIN_8
#define SEG_D_PIN  GPIO_PIN_9
#define SEG_E_PIN  GPIO_PIN_7
#define SEG_F_PIN  GPIO_PIN_6
#define SEG_G_PIN  GPIO_PIN_5

#define SEGMENT_PORT GPIOA

// 0~9까지의 숫자에 해당하는 세그먼트 조합
extern const uint8_t segmentDigits[] ;

// 세그먼트 초기화 함수
void Segment_Init(void);

// 숫자 표시 함수
void Display_Number(uint8_t num);
void clearDisplay();
void display_0();
void display_1();
void display_2();

#endif /* INC_7SEG_H_ */
