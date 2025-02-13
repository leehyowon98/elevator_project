/*
 * common.h
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include "motor.h"

// 기본 타입과 공통 구조체만 정의
typedef struct {
    bool doorClosingStarted;
    bool doorFullyOpened;
    bool openingStarted;
    uint32_t doorHoldStartTime;
    uint32_t doorOperationStartTime;
    bool leftSensorDetected;
    bool rightSensorDetected;
    uint8_t targetFloor;
} SystemStatus;

// 기본적인 외부 참조만 선언
extern volatile SystemStatus sysStatus;
extern StepperMotor stepmotot1;
extern StepperMotor stepmotot2;
extern StepperMotor stepmotot3;

#endif /* COMMON_H_ */
