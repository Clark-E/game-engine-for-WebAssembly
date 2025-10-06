#include "parser.h"
#include "room.h"
#include "gameManager.h"
#include "io.h"

#include <format>

bool Parser::isWhitespace(const char c){
	
	//returns true if/only the current character is whitespace
	
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
	
	//start index of next word
	size_t startIndex = 0;
	
	while(startIndex < this->commandRemaining.size() && isWhitespace(this->commandRemaining[startIndex])){
		
		startIndex++;
		
	}
	
	if(startIndex >= this->commandRemaining.size()){
		
		this->currentWord = "";
		this->commandRemaining = "";
		return;
		
	}
	
	//end index of next word
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
	
	//parse and react to user input
	
	//setup: set commandRemaining
	this->commandRemaining = str;
	
	for(size_t i = 0; i < this->commandRemaining.size(); i++){
		
		this->commandRemaining[i] = tolower(this->commandRemaining[i]);
		
	}
	
	//get the first word
	advance();
	
	//switch on command
	switch(wordToCommand(this->currentWord)){
		
		case(Command::HELP):{
			
			parseHelpCommand();
			
			break;
			
		}
		case(Command::LOOK):{
			
			parseLookCommand();
			
			break;
			
		}
		case(Command::MOVE):{
			
			parseMoveCommand();
			
			break;
			
		}
		case(Command::NONE):{
			
			println("Unknown command. Type \"help\" for help.");
			
			break;
			
		}
		
	}
	
};

void Parser::parseMoveCommand(){
	
	//parse a move command
	
	//get argument to move
	advance();
	
	if(this->currentWord.size() == 0){
		
		println("Move where? (type \"help move\" for help.)");
		return;
		
	}
	
	Direction moveDirection = wordToDirection(this->currentWord);
	
	if(moveDirection == Direction::NONE){
		
		println(std::format("Can't move {}; It isn't a direction. (Type \"help move\" for help.)",this->currentWord));
		return;
		
	}
	
	int32_t moveX = GameManager::currentRoomX+directionX(moveDirection);
	int32_t moveY = GameManager::currentRoomY+directionY(moveDirection);
	
	Room* moveRoom = Room::getRoomAt(moveX,moveY);
	
	if(moveRoom){
		
		GameManager::currentRoomX = moveX;
		GameManager::currentRoomY = moveY;
		
		println(std::format("You move to the {}",moveRoom->name));
		println("");
		lookInDirection(Direction::NORTH,true);
		lookInDirection(Direction::WEST,true);
		lookInDirection(Direction::EAST,true);
		lookInDirection(Direction::SOUTH,true);
		
	}else{
		
		println("There's nothing but the ocean in that direction. Even if you wanted to sleep with the fishies, there's several millimeters of steel and reinforced glass in your way.");
		
	}
	
};

void Parser::parseLookCommand(){
	
	//parse look command
	
	//get argument to look	
	advance();
	
	if(this->currentWord.size() == 0){
		
		lookInDirection(Direction::NONE,false);
		println("");
		lookInDirection(Direction::NORTH,true);
		lookInDirection(Direction::WEST,true);
		lookInDirection(Direction::EAST,true);
		lookInDirection(Direction::SOUTH,true);
		
	}else{
		
		Direction lookDirection = wordToDirection(this->currentWord);
		
		if(lookDirection == Direction::NONE){
			
			println(std::format("Can't look {}; It isn't a direction. (Type \"help look\" for help.)",this->currentWord));
			return;
			
		}else{
			
			lookInDirection(lookDirection,false);
			
		}
		
	}
	
};
	
void Parser::lookInDirection(Direction lookDirection,bool onlyIfRoom){
	
	//prints room information for the room in the direction of lookDirection, relative to the current room.
	
	//if onlyIfRoom is set, this method will do nothing if no such room exists.
	
	int32_t lookX = GameManager::currentRoomX+directionX(lookDirection);
	int32_t lookY = GameManager::currentRoomY+directionY(lookDirection);
	
	Room* lookRoom = Room::getRoomAt(lookX,lookY);
	
	if(onlyIfRoom && !lookRoom) return;
	
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

void Parser::parseHelpCommand(){
	
	//print help information for the specified command.
	
	//get argument
	advance();
	
	Command helpCommand = wordToCommand(this->currentWord);
	
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
			
			println("You can use following commands:\n\nHelp\nLook\nMove\n\nUse \"Help\" followed by a command for info on that command.");
			
			break;
			
		}
		
	}
	
};