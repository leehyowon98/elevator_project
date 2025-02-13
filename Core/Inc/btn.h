/*
 * btn.h
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#ifndef INC_BTN_H_
#define INC_BTN_H_

#include "common.h"
#include "i2c_lcd.h"

typedef enum {
    BTN_IDLE=0,
    BTN_PRESSING,
    BTN_RELEASED
} ButtonState;

typedef struct {
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
    ButtonState state;
    bool is_pressed;
} Button;

extern Button extBtn1;
extern Button extBtn2;
extern Button intBtn1;
extern Button intBtn2;

void HandleButtonPress(Button* btn);

#endif /* INC_BTN_H_ */
