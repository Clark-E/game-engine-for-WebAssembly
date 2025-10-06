#pragma once

#include <string>
#include <utility> //for std::pair
#include <map>
#include <cstdint>

class Room{
	
	public:
	
	//Room(std::string _name, int32_t _x, int32_t _y):name(_name),x(_x),y(_y){};
	Room(std::string _name, int32_t _x, int32_t _y);
	
	std::string name;
	int32_t x;
	int32_t y;
	
	static void loadRooms();
	
	static std::map<std::pair<int32_t,int32_t>,Room> roomMap;
	static Room* getRoomAt(int32_t x, int32_t y);
	
};