#include "parser.h"
#include "room.h"
#include "gameManager.h"
#include "io.h"

#include <format>

bool Parser::isWhitespace(const char c){
	
	//returns true if/only the current character is whitespace
	
	return(false);
	
};

void Parser::advance(){
	
	//removes the next word from commandRemaining and puts in currentWord
	
};

Parser::Command Parser::wordToCommand(const std::string word){
	
	//match word to command
	
	return(Command::NONE);
	
};

Direction Parser::wordToDirection(const std::string word){
	
	//match word to direction
	
	return(Direction::NONE);
	
};

void Parser::processCommand(const std::string str){
	
	//parse and react to user input
	
};

void Parser::parseMoveCommand(){
	
	//parse a move command
	
};

void Parser::parseLookCommand(){
	
	//parse look command
	
};
	
void Parser::lookInDirection(Direction lookDirection,bool onlyIfRoom){
	
	//prints room information for the room in the direction of lookDirection, relative to the current room.
	
};

void Parser::parseHelpCommand(){
	
	//print help information for the specified command.
	
};