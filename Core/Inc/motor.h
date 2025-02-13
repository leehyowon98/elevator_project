/*
 * motor.h
 *
 *  Created on: Jan 14, 2025
 *      Author: user
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"
#include "delayus.h"
#include <stdbool.h>

typedef enum {
    MOTOR_STOPPED =0,  // 모터 정지 상태
    MOTOR_RUNNING   // 모터 회전 중 상태
} MotorState;

#define STEP_PER_RESOLUTION 4096
// 시계방향
#define DIR_CW              0
// 반시계 방향
#define DIR_CCW             1

// 모터 구조체 정의
typedef struct {
    GPIO_TypeDef* in1_port;
    uint16_t in1_pin;
    GPIO_TypeDef* in2_port;
    uint16_t in2_pin;
    GPIO_TypeDef* in3_port;
    uint16_t in3_pin;
    GPIO_TypeDef* in4_port;
    uint16_t in4_pin;
    MotorState state;
} StepperMotor;

static const uint8_t HALF_STEP_SEQ[8][4] =
    {
        {1, 0, 0, 0 },
        {1, 1, 0, 0 },
        {0, 1, 0, 0 },
        {0, 1, 1, 0 },
        {0, 0, 1, 0 },
        {0, 0, 1, 1 },
        {0, 0, 0, 1 },
        {1, 0, 0, 1 }
    };

void stepMotor(StepperMotor* motor, uint8_t step);
void rotateSteps(StepperMotor* motor, uint16_t steps, uint8_t direction);
void rotateDegrees(StepperMotor* motor, uint16_t degrees, uint8_t direction);
void rotateMotorContinuous(StepperMotor* motor, uint8_t direction);
void stopMotor(StepperMotor* motor);
// 모터 초기화 함수 추가
void initMotor(StepperMotor* motor,
               GPIO_TypeDef* in1_port, uint16_t in1_pin,
               GPIO_TypeDef* in2_port, uint16_t in2_pin,
               GPIO_TypeDef* in3_port, uint16_t in3_pin,
               GPIO_TypeDef* in4_port, uint16_t in4_pin);

#endif /* INC_MOTOR_H_ */
