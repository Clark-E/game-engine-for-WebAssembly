#include "parser.h"
#include "room.h"
#include "gameManager.h"
#include "io.h"

#include <format>

bool Parser::isWhitespace(const char c){
	
	switch(c){
		
		case(' '):
		case('\t'):
			return(true);
		default:
			return(false);
		
	}
	
};

void Parser::advance(){
	
	//removes the next word from commandRemaining and puts in currentWord
	
	size_t startIndex = 0;
	
	while(startIndex < this->commandRemaining.size() && isWhitespace(this->commandRemaining[startIndex])){
		
		startIndex++;
		
	}
	
	if(startIndex >= this->commandRemaining.size()){
		
		this->currentWord = "";
		this->commandRemaining = "";
		return;
		
	}
	
	size_t endIndex = startIndex+1;
	
	while(endIndex < this->commandRemaining.size() && !isWhitespace(this->commandRemaining[endIndex])){
		
		endIndex++;
		
	}
	
	this->currentWord = this->commandRemaining.substr(startIndex,endIndex-startIndex);
	this->commandRemaining = this->commandRemaining.substr(endIndex);
	
};

Parser::Command Parser::wordToCommand(const std::string word){
	
	//match word to command
	
	if(word == "help" || word == "h") return(Command::HELP);
	if(word == "look" || word == "l") return(Command::LOOK);
	if(word == "move" || word == "m") return(Command::MOVE);
	
	return(Command::NONE);
	
};

Direction Parser::wordToDirection(const std::string word){
	
	//match word to direction
	
	if(word == "north" || word == "n") return(Direction::NORTH);
	if(word == "east"  || word == "e") return(Direction::EAST);
	if(word == "south" || word == "s") return(Direction::SOUTH);
	if(word == "west"  || word == "w") return(Direction::WEST);
	
	return(Direction::NONE);
	
};

void Parser::processCommand(const std::string str){
	
	//setup: set commandRemaining
	this->commandRemaining = str;
	
	for(size_t i = 0; i < this->commandRemaining.size(); i++){
		
		this->commandRemaining[i] = tolower(this->commandRemaining[i]);
		
	}
	
	//get the first currentWord
	advance();
	
	//switch on command
	switch(wordToCommand(this->currentWord)){
		
		case(Command::HELP):{
			
			advance();
			printHelp(wordToCommand(this->currentWord));
			
			break;
			
		}
		case(Command::LOOK):{
			
			parseLookCommand();
			
			break;
			
		}
		case(Command::MOVE):{
			
			advance();
					
			if(this->currentWord.size() == 0){
				
				println("Move where? (type \"help move\" for help.)");
				break;
				
			}
				
			Direction moveDirection = wordToDirection(this->currentWord);
			
			int32_t moveX = GameManager::currentRoomX+directionX(moveDirection);
			int32_t moveY = GameManager::currentRoomY+directionY(moveDirection);
			
			Room* moveRoom = Room::getRoomAt(moveX,moveY);
			
			if(moveRoom){
				
				GameManager::currentRoomX = moveX;
				GameManager::currentRoomY = moveY;
				
				//lookCommand(Direction::NONE);
				println(std::format("You move to the {}",moveRoom->name));
				println("");
				lookInDirection(Direction::NORTH);
				lookInDirection(Direction::WEST);
				lookInDirection(Direction::EAST);
				lookInDirection(Direction::SOUTH);
				
			}else{
				
				println("There's nothing but the ocean in that direction. Even if you wanted to sleep with the fishies, there's several millimeters of steel and reinforced glass in your way.");
				
			}
			
			break;
			
		}
		case(Command::NONE):{
			
			println("Unknown command. Type \"help\" for help.");
			
			break;
			
		}
		
	}
	
};

void Parser::parseLookCommand(){
	
	Room* lookRoom = nullptr;
	Direction lookDirection = Direction::NONE;
	
	advance();
	
	if(this->currentWord.size() == 0){
		
		lookInDirection(Direction::NONE);
		println("");
		lookInDirection(Direction::NORTH);
		lookInDirection(Direction::WEST);
		lookInDirection(Direction::EAST);
		lookInDirection(Direction::SOUTH);
		
	}else{
		
		lookDirection = wordToDirection(this->currentWord);
		
		if(lookDirection == Direction::NONE){
			
			println(std::format("Can't look {}; It isn't a direction. (Type \"help move\" for help.)",this->currentWord));
			return;
			
		}else{
			
			lookInDirection(lookDirection);
			
		}
		
	}
	
};
	
void Parser::lookInDirection(Direction lookDirection){
	
	int32_t lookX = GameManager::currentRoomX+directionX(lookDirection);
	int32_t lookY = GameManager::currentRoomY+directionY(lookDirection);
	
	Room* lookRoom = Room::getRoomAt(lookX,lookY);
	
	if(lookDirection == Direction::NONE){
		
		print("You're standing in ");
		
	}else{
		
		print(std::format("To the {} is ",directionName(lookDirection)));
		
	}
	
	if(lookRoom){
		
		println(std::format("the {}",lookRoom->name));
		
	}else{
		
		println("a window to the open ocean.");
		
	}
	
};

void Parser::printHelp(Command helpCommand){
	
	switch(helpCommand){
		
		case(Command::HELP):{
			
			println("The help command is used to learn about commands. usage: \"help\" or \"help [command]\"");
			
			break;
			
		}
		case(Command::LOOK):{
			
			println("The look command is used to examine your surroundings. usage: \"look\" or \"look [object]\" or \"look [north/east/south/west]\"");
			
			break;
			
		}
		case(Command::MOVE):{
			
			println("The move command is used to move to a different location. usage: \"move\" or \"move [north/east/south/west]\" or \"move [n/e/s/w]\"");
			
			break;
			
		}
		case(Command::NONE):{
			
			println("You can use following commands:\n\nHelp\nLook\nMove\n\nUse \"Help\" followed by a command for info that command.");
			
			break;
			
		}
		
	}
	
};