#include "csv.h"

CsvParser::CsvParser(std::string data_):data(data_){};

std::string CsvParser::getString(){
	
	//get the next value from the csv file.
	//this is mostly compliant with https://www.rfc-editor.org/rfc/rfc4180#section-2
	//BUT there are a few differences. In technical terms:
	//- instead of [CRLF], this uses [LF] as the newline delimeter.
	//- \n is parsed into a newline ([LF]).
	//- \x gets turned into x for most values of x, except [LF] and "
	//In less technical terms:
	//- CRLF -> LF, you can escape a newline with \, and \ itself is escaped with \\.
	
	std::string returnValue = "";
	
	//check if value is quoted or not.
	bool quoted = !end() && this->data[this->currentIndex] == '\"';
	
	if(quoted) this->currentIndex++;
	
	while(!end()){
		
		char currentCharacter = this->data[this->currentIndex];
		
		if(!quoted && currentCharacter == ','){
			
			//move to next value (for next time), then stop parsing.
			this->currentIndex++;
			break;
			
		}else if(quoted && currentCharacter == '\"'){
			
			//to encode double quotes in a quoted value, it's escaped by... another double quote.
			
			if(this->currentIndex+1 < this->data.size() && this->data[this->currentIndex+1] == '\"'){
				
				//append a double quote.
				returnValue += '\"';
				this->currentIndex += 2;
				
			}else if(this->currentIndex+1 < this->data.size() && this->data[this->currentIndex+1] == '\n'){
				
				//move to next value (for next time), then stop parsing.
				this->currentIndex++;
				break;
				
			}else{
				
				//move to next value (for next time), then stop parsing.
				this->currentIndex += 2;
				break;
				
			}
			
		}else if(currentCharacter == '\n'){
			
			//stop parsing
			break;
			
		}else if(currentCharacter == '\\' && this->currentIndex+1 < this->data.size()){
			
			//parse escape character
			switch(this->data[this->currentIndex+1]){
				
				case('n'):{
					
					//the escape sequence encoded a newline.
					returnValue += '\n';
					this->currentIndex += 2;
					break;
					
				}
				case('\n'):{
					
					//the line suddenly ended.
					returnValue += '\\';
					this->currentIndex += 1;
					break;
					
				}
				case('\"'):{
					
					//don't treat this as an escape sequence at all for RFC compliance.
					returnValue += '\\';
					this->currentIndex += 1;
					break;
					
				}
				default:{
					
					//append the character after the slash.
					returnValue += this->data[this->currentIndex+1];
					this->currentIndex += 2;
					break;
					
				}
				
			}
			
		}else{
			
			//add character to returnValue
			returnValue += currentCharacter;
			this->currentIndex += 1;
			
		}
		
	}
	
	return(returnValue);
	
};

void CsvParser::nextLine(){
	
	while(!lineEnd()){
		
		this->currentIndex++;
		
	}
	
	if(!end()) this->currentIndex++;
	
};

bool CsvParser::end(){
	
	return(this->currentIndex >= this->data.size());
	
};

bool CsvParser::lineEnd(){
	
	return(end() || this->data[this->currentIndex] == '\n');
	
};