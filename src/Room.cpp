#include "Room.h"

Room* createRoom(int roomNumber, float roomTreasure, bool roomSearched){
	Room* newRoom = new Room;
	newRoom->roomNumber = roomNumber;
	newRoom->treasure = roomTreasure;
	newRoom->searched = roomSearched;
	return newRoom;
}

