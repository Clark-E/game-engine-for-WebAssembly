#include "io.h"

#ifdef __EMSCRIPTEN__

	#include <emscripten.h>

	EM_JS(void, printJS,(const char* toPrint),{
   	 
    	const MAX_CHARS = 65536;

    	output = document.getElementById("output");
   	 
    	output.value += UTF8ToString(toPrint);
   	 
    	if(output.value.length > MAX_CHARS){
       	 
        	output.value = output.innerText.substr(-MAX_CHARS);
       	 
    	}
   	 
    	output.scrollTop = output.scrollHeight;
   	 
	});
    
	void print(const char* toPrint){
   	 
    	printJS(toPrint);
   	 
	};
    
#else
    
	#include <stdio.h>
    
	void print(const char* toPrint){
   	 
    	//some compilers *really* want you to use their "_s" variants of printf.
   	 
    	#ifndef printf_s
       	 
        	#define printf_s printf
       	 
    	#endif
   	 
    	printf_s("%s",toPrint);
		
	}
    
#endif

void println(const char* toPrint){
    
    print(toPrint);
    print("\n");
    
};

void print(std::string toPrint){
    
    print(toPrint.c_str());
    
}

void println(std::string toPrint){
    
    println(toPrint.c_str());
    
}

extern "C" {
    
    void onConsoleInput(const char* input){
     
     processInput(input);
     
    };
    
}