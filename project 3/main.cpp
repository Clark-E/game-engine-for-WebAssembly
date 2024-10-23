#include "main.h"
#include <iostream>

int main(){
    
	println("Hello, world!");
    
	#ifndef __EMSCRIPTEN__
   	 
    	while(true){
       	 
        	std::string input;
        	std::getline(std::cin, input);
       	 
        	processInput(input.c_str());
       	 
    	}
   	 
	#endif
    
	return(0);

};

void processInput(const char* input){
    
    println(input);
    
    //pretend we're running game logic...
    
    println("Pretend this is the game’s text output.");
    
};