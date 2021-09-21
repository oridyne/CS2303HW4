/*
 * Room.h
 *
 *  Created on: May 22, 2020
 *      Author: Owen Aguirre
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>

typedef struct Room {
	int roomNumber;
	float treasure;
	bool searched;
} Room;

Room* createRoom(int roomNumber, float roomTreasure, bool roomSearched);

#endif /* ROOM_H_ */
