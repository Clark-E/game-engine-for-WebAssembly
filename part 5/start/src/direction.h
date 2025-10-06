#pragma once

#include <utility> //for std::pair
#include <cstdint>

enum Direction{
	
	NONE,
	
	NORTH,
	EAST,
	SOUTH,
	WEST
	
};

static int8_t directionX(Direction direction){
	
	switch(direction){
		
		case(EAST):
			return(1);
		case(WEST):
			return(-1);
		default:
			return(0);
		
	}
	
};

static int8_t directionY(Direction direction){
	
	switch(direction){
		
		case(NORTH):
			return(-1);
		case(SOUTH):
			return(1);
		default:
			return(0);
		
	}
	
};

static const char* directionName(Direction direction){
	
	switch(direction){
		
		case(NORTH):
			return("north");
		case(EAST):
			return("east");
		case(SOUTH):
			return("south");
		case(WEST):
			return("west");
		default:
			return("");
		
	}
	
};