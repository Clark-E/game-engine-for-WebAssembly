#include "main.h"
#include <emscripten.h>

EM_JS(void, printJS,(const char* toPrint),{
    
 //a javascript function which prints text to our console output
 //takes a const char* argument called toPrint, returns void
    
 //get the DOM element with id of "output"
 output = document.getElementById("output");
    
 //convert our (UTF8) c string into a javascript string.
 output.value += UTF8ToString(toPrint);
    
 //scroll down to view the newly printed text.
 output.scrollTop = output.scrollHeight;
    
});

void print(const char* toPrint){
    
 printJS(toPrint);
    
}

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