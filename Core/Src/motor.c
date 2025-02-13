/*
 * motor.c
 *
 *  Created on: Jan 14, 2025
 *      Author: user
 */


#include "motor.h"

StepperMotor stepmotot1;
StepperMotor stepmotot2;
StepperMotor stepmotot3;

void initMotor(StepperMotor* motor,
               GPIO_TypeDef* in1_port, uint16_t in1_pin,
               GPIO_TypeDef* in2_port, uint16_t in2_pin,
               GPIO_TypeDef* in3_port, uint16_t in3_pin,
               GPIO_TypeDef* in4_port, uint16_t in4_pin)
{
    motor->in1_port = in1_port;
    motor->in1_pin = in1_pin;
    motor->in2_port = in2_port;
    motor->in2_pin = in2_pin;
    motor->in3_port = in3_port;
    motor->in3_pin = in3_pin;
    motor->in4_port = in4_port;
    motor->in4_pin = in4_pin;
    motor->state = MOTOR_STOPPED;
}

void stepMotor(StepperMotor* motor, uint8_t step)
{
    HAL_GPIO_WritePin(motor->in1_port, motor->in1_pin, HALF_STEP_SEQ[step][0]);
    HAL_GPIO_WritePin(motor->in2_port, motor->in2_pin, HALF_STEP_SEQ[step][1]);
    HAL_GPIO_WritePin(motor->in3_port, motor->in3_pin, HALF_STEP_SEQ[step][2]);
    HAL_GPIO_WritePin(motor->in4_port, motor->in4_pin, HALF_STEP_SEQ[step][3]);
}

void rotateSteps(StepperMotor* motor, uint16_t steps, uint8_t direction)
{
    motor->state = MOTOR_RUNNING;
    
    for(uint16_t i = 0; i < steps; i++)
    {
        uint8_t step;
        if(direction == DIR_CW)
        {
            step = i % 8;
        }
        else
        {
            step = 7 - (i % 8);
        }
        stepMotor(motor, step);
        delay_us(1000);
    }
    
    motor->state = MOTOR_STOPPED;
}

void rotateDegrees(StepperMotor* motor, uint16_t degrees, uint8_t direction)
{
    uint16_t steps = (uint16_t)((uint32_t)degrees * STEP_PER_RESOLUTION / 360);
    rotateSteps(motor, steps, direction);
}

void rotateMotorContinuous(StepperMotor* motor, uint8_t direction) {
    motor->state = MOTOR_RUNNING;
    static uint8_t currentStep = 0;
    
    if(direction == DIR_CW) {
        currentStep = (currentStep + 1) % 8;
    } else {
        currentStep = (currentStep > 0) ? (currentStep - 1) : 7;
    }
    
    stepMotor(motor, currentStep);
    delay_us(1000);  // 속도 조절을 위한 딜레이
}

void stopMotor(StepperMotor* motor) {
    HAL_GPIO_WritePin(motor->in1_port, motor->in1_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor->in2_port, motor->in2_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor->in3_port, motor->in3_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(motor->in4_port, motor->in4_pin, GPIO_PIN_RESET);
    motor->state = MOTOR_STOPPED;
}
