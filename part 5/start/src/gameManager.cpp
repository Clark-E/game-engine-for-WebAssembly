#include "gameManager.h"

int32_t GameManager::currentRoomX;
int32_t GameManager::currentRoomY;

Room* GameManager::getCurrentRoom(){
	
	return(Room::getRoomAt(GameManager::currentRoomX,GameManager::currentRoomY));
	
};