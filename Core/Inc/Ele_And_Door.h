/*
 * Ele_And_Door.h
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#ifndef ELE_AND_DOOR_H_
#define ELE_AND_DOOR_H_

#include "common.h"
#include "motor.h"

#define DOOR_OPEN_TIME_MS 3000
#define FLOOR_1 1
#define FLOOR_2 2

typedef enum {
    IDLE = 0,
    MOVING,
    OPEN_DOORS,
    CLOSE_DOORS
} ElevatorState;

typedef struct {
    uint8_t currentFloor;
    ElevatorState state;
} ElevatorStatus;

extern ElevatorStatus elevatorStatus;

void openDoors(void);
void closeDoors(void);
void moveElevatorTo(uint8_t floor);

#endif /* ELE_AND_DOOR_H_ */
