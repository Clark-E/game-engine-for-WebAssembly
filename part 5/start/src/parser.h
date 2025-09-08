#pragma once

#include "direction.h"

#include <string>

class Parser{
	
	public:
	
	enum Command{
		
		NONE,
		
		HELP,
		LOOK,
		MOVE,
		
	};
	
	void processCommand(const std::string);
	void parseLookCommand();
	
	void printHelp(Command);
	void lookInDirection(Direction);
	
	private:
	
	Command wordToCommand(const std::string);
	Direction wordToDirection(const std::string);
	
	static bool isWhitespace(const char);
	
	void advance();
	
	//the current word (what the user typed) the parser is looking at
	std::string currentWord;
	
	//the rest of the command we have to parse
	std::string commandRemaining;
	
	
};