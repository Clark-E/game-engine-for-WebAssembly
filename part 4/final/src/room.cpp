#include "room.h"
#include "io.h"
#include "csv.h"
#include "file.h"
#include <format>

void Room::loadRooms(){
	
	//Load the map.csv file
	
	std::string roomData = readFile("build data/map.csv");
	
	CsvParser roomParser = CsvParser(roomData);
	
	int currentFloor = 1;
	std::string currentRoom;
	
	while(!roomParser.end()){
		
		if(!roomParser.lineEnd()){
		
			print(std::format("Rooms on floor negative {}:\n",currentFloor));
			
			do{
				
				currentRoom = roomParser.getString();
				println(currentRoom);
				
			}while(!roomParser.lineEnd());
		
		}
		
		println("");
		currentFloor++;
		roomParser.nextLine();
		
	}
	
};