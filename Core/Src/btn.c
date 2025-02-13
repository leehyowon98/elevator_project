/*
 * btn.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */
#include "btn.h"
#include "Ele_And_Door.h"
#include "stdio.h"

extern volatile SystemStatus sysStatus;
extern ElevatorStatus elevatorStatus;

Button extBtn1 = {GPIOC, GPIO_PIN_9, BTN_IDLE, false};
Button extBtn2 = {GPIOB, GPIO_PIN_8, BTN_IDLE, false};
Button intBtn1 = {GPIOC, GPIO_PIN_6, BTN_IDLE, false};
Button intBtn2 = {GPIOC, GPIO_PIN_5, BTN_IDLE, false};

void HandleButtonPress(Button* btn) {
    uint8_t pinState = HAL_GPIO_ReadPin(btn->GPIOx, btn->GPIO_Pin);

    if (elevatorStatus.state == MOVING ||
        elevatorStatus.state == OPEN_DOORS ||
        elevatorStatus.state == CLOSE_DOORS) {
        printf("Elevator is busy, button press ignored\r\n");
        return;
    }

    if (pinState == GPIO_PIN_SET && !btn->is_pressed) {
        btn->is_pressed = true;
        printf("Button pressed\r\n");

        if (elevatorStatus.state == IDLE || elevatorStatus.state == OPEN_DOORS) {
            if ((btn == &extBtn1 || btn == &intBtn1) && elevatorStatus.currentFloor != FLOOR_1) {
                sysStatus.targetFloor = FLOOR_1;
                printf("Target floor set to 1\r\n");
                moveCursor(0, 0);
                lcdString("Target floor : 1    ");
                elevatorStatus.state = MOVING;
                moveElevatorTo(sysStatus.targetFloor);
            } else if ((btn == &extBtn2 || btn == &intBtn2) && elevatorStatus.currentFloor != FLOOR_2) {
                sysStatus.targetFloor = FLOOR_2;
                printf("Target floor set to 2\r\n");
                moveCursor(0, 0);
                lcdString("Target floor : 2     ");
                elevatorStatus.state = MOVING;
                moveElevatorTo(sysStatus.targetFloor);
            } else {
                printf("Opening doors on current floor\r\n");
                elevatorStatus.state = OPEN_DOORS;
            }
        }
    } else if (pinState == GPIO_PIN_RESET && btn->is_pressed) {
        btn->is_pressed = false;
    }
}
