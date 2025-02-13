/*
 * Ele_And_Door.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */


#include "Ele_And_Door.h"
#include "motor.h"
#include "i2c_lcd.h"
#include <stdio.h>

extern ElevatorStatus elevatorStatus;

// 문 열기 함수
void openDoors(void) {
    StepperMotor* doorMotor = (elevatorStatus.currentFloor == FLOOR_1) ? &stepmotot1 : &stepmotot2;

    if (!sysStatus.openingStarted) {
        sysStatus.openingStarted = true;
        sysStatus.doorFullyOpened = false;
        sysStatus.leftSensorDetected = false;
        sysStatus.rightSensorDetected = false;
        printf("Opening doors at floor %d\r\n", elevatorStatus.currentFloor);
        moveCursor(0, 0);
        lcdString("open door       ");
    }

    if (!sysStatus.rightSensorDetected) {
        rotateMotorContinuous(doorMotor, DIR_CW);
    }

    if (sysStatus.rightSensorDetected && !sysStatus.doorFullyOpened) {
        stopMotor(doorMotor);
        printf("Door fully opened at floor %d\r\n", elevatorStatus.currentFloor);
        moveCursor(0, 0);
        lcdString("Door fully open");
        sysStatus.doorFullyOpened = true;
        sysStatus.doorHoldStartTime = HAL_GetTick();
    }

    if (sysStatus.doorFullyOpened) {
        uint32_t holdTime = HAL_GetTick() - sysStatus.doorHoldStartTime;
        if (holdTime >= DOOR_OPEN_TIME_MS) {
            printf("Starting to close doors\r\n");
            elevatorStatus.state = CLOSE_DOORS;
            sysStatus.openingStarted = false;
            sysStatus.doorFullyOpened = false;
        }
    }
}

// 문 닫기 함수
void closeDoors(void) {
    StepperMotor* doorMotor = (elevatorStatus.currentFloor == FLOOR_1) ? &stepmotot1 : &stepmotot2;

    if (!sysStatus.doorClosingStarted) {
        sysStatus.doorClosingStarted = true;
        sysStatus.leftSensorDetected = false;
        sysStatus.rightSensorDetected = false;
        printf("Close doors at floor %d\r\n", elevatorStatus.currentFloor);
        moveCursor(0, 0);
        lcdString("Close door       ");
    }

    if (!sysStatus.leftSensorDetected) {
        rotateMotorContinuous(doorMotor, DIR_CCW);
    }

    if (sysStatus.leftSensorDetected) {
        stopMotor(doorMotor);
        printf("Door fully closed at floor %d\r\n", elevatorStatus.currentFloor);
        moveCursor(0, 0);
        lcdString("Door closed    ");
        sysStatus.doorClosingStarted = false;
        elevatorStatus.state = IDLE;
    }
}

// 엘리베이터 이동 함수
void moveElevatorTo(uint8_t floor) {
    if (stepmotot3.state != MOTOR_STOPPED || (floor != FLOOR_1 && floor != FLOOR_2)) {
        printf("Invalid movement request\r\n");
        return;
    }

    if (elevatorStatus.currentFloor == floor) {
        printf("Already at floor %d\r\n", floor);
        elevatorStatus.state = OPEN_DOORS;
        return;
    }

    printf("Moving to floor %d\r\n", floor);
    elevatorStatus.state = MOVING;
    
    if (floor == FLOOR_1) {
        printf("Rotating CCW\r\n");
        rotateDegrees(&stepmotot3, 1190, DIR_CCW);
    } else {
        printf("Rotating CW\r\n");
        rotateDegrees(&stepmotot3, 1190, DIR_CW);
    }

    elevatorStatus.currentFloor = floor;
    printf("Arrived at floor %d\r\n", floor);
}
