#include "room.h"
#include "io.h"
#include "csv.h"
#include "file.h"

#include <format>

std::map<std::pair<int32_t,int32_t>,Room> Room::roomMap;

Room::Room(std::string _name, int32_t _x, int32_t _y):name(_name),x(_x),y(_y){};

void Room::loadRooms(){
	
	//Load the map.csv file
	
	std::string roomData = readFile("build data/map.csv");
	
	CsvParser roomParser = CsvParser(roomData);
	
	int32_t currentY = 0;
	std::string currentRoomName;
	
	while(!roomParser.end()){
		
		int32_t currentX = 0;
		
		if(!roomParser.lineEnd()){
			
			do{
				
				std::string roomName = roomParser.getString();
				
				if(roomName.size() != 0){
					
					Room newRoom = Room(roomName,currentX,currentY);
					
					Room::roomMap.insert({std::pair<int32_t,int32_t>(currentX,currentY),std::move(newRoom)});
					
				}
				
				currentX++;
				
			}while(!roomParser.lineEnd());
		
		}
		
		println("");
		currentY++;
		roomParser.nextLine();
		
	}
	
};

Room* Room::getRoomAt(int32_t x, int32_t y){
	
	std::pair<int32_t,int32_t> roomCoordinates{x,y};
	
	auto roomIter = Room::roomMap.find(roomCoordinates);
	
	if(roomIter != Room::roomMap.end()){
		
		return(&(roomIter->second));
		
	}else{
		
		return(nullptr);
		
	}
	
};