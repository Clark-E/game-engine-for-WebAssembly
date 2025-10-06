#pragma once

#include "direction.h"

#include "room.h"

class GameManager{
	
	public:
	
	//where the player is
	static int32_t currentRoomX;
	static int32_t currentRoomY;
	
	static Room* getCurrentRoom();
	
};