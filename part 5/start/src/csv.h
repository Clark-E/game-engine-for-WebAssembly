#pragma once
#include <string>

class CsvParser{
	
	public:
	
	CsvParser(std::string);
	
	std::string data;
	size_t currentIndex = 0; //points to the start of the next string.
	
	std::string getString();
	void nextLine();
	
	bool end();
	bool lineEnd();
	
};