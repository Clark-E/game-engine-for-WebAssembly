import subprocess
import os

sourceFiles = [];

SRC_PATHS = {
	
	"./src",
	
};

for SRC_PATH in SRC_PATHS:
	for (dirpath, dirnames, filenames) in os.walk(SRC_PATH):
		#sourceFiles.extend(filenames);
		for file in filenames:
			if(not(len(file) >= 2 and file[-2:] == ".h")):
				sourceFiles.append("{0}/{1}".format(dirpath,file));

EMCC_COMMAND_START = """emcc -s WASM=1 -std=c++20 -o index.html --shell-file shell.html -sEXPORTED_FUNCTIONS=_onConsoleInput,_main -sEXPORTED_RUNTIME_METHODS=ccall,cwrap"""

fullCommand = EMCC_COMMAND_START;

for file in sourceFiles:
	fullCommand += " \"{0}\"".format(file);

print(fullCommand)
os.system(fullCommand)