#include "io.h"
#include "room.h"
#include <iostream>

int main(){
    
	//program entry point
	
	//do initialization
	
	Room::loadRooms();
	
	#ifndef __EMSCRIPTEN__
		
		//in native builds, we need to manually poll the input in the c code.
		
    	while(true){
			
        	std::string input;
        	std::getline(std::cin, input);
			
        	processInput(input.c_str());
			
    	}
		
	#endif
    
	return(0);

};

void processInput(const char* input){
    
	//processes text input from the user.
	
};