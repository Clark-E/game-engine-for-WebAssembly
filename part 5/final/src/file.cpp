#include "file.h"
#include "io.h"
#include <fstream>

std::string readFile(std::string fname){
	
	std::ifstream file;
	file.open(fname);
	
	if(file.is_open()){
		
		std::string fileContents;
		
		while(!file.eof()){
			
			std::string line;
			std::getline(file,line);
			if(line.size() > 0 && line[line.size()-1] == '\r') line.pop_back();
			
			fileContents += line;
			fileContents += '\n';
			
		}
		
		file.close();
		
		return(fileContents);
		
	}
	
	print("Internal error: cannot open file ");
	print(fname);
	println("");
	
	return("");
	
};