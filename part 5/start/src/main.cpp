#include "io.h"
#include "room.h"
#include "parser.h"

#include <iostream>
#include <string>

Parser gameParser;

#ifdef __EMSCRIPTEN__

	const bool IS_WEB_BUILD = true;
	
#else
	
	const bool IS_WEB_BUILD = false;
	
#endif

int main(){
	
	//program entry point
	
	//do initialization
	
	Room::loadRooms();
	
	//in native builds, we need to manually poll the input in the c code.
	
	if(!IS_WEB_BUILD){
	
		while(true){
			
			print("\n> ");
			
			std::string input;
			std::getline(std::cin, input);
			
			println("");
			
			processInput(input.c_str());
			
		}
		
	}
	
	return(0);

};

void processInput(const char* input){
	
	//process text input from the user.
	
	//in web builds, print input to output
	if(IS_WEB_BUILD){
		
		println("");
		print("> ");
		println(input);
		println("");
		
	}
	
	gameParser.processCommand(std::string(input));
	
};