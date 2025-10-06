#pragma once
#include <string>

//print to the output
extern void print(const char*);
extern void print(std::string);

//print to the output and append a newline
extern void println(const char*);
extern void println(std::string);

//called whenever the user enters text
extern void processInput(const char*);