#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "sourceparser.hpp"

using namespace std;

char *sourcefilename;
char *buffer;

SourceFile::SourceFile(char* sourcefilename) {
	this->sourcefilename = sourcefilename;
}

bool SourceFile::readfile() {
	FILE* sourcefile;
	unsigned int size;
	
	sourcefile = fopen(sourcefilename, "r");
	
	if(sourcefile == NULL) {
		return false;
	}
	
	buffer = (char*) malloc(2048000);	// 2MB buffer size.
	
	fseek (sourcefile, 0, SEEK_END);	// Point to the end of the file.
	size = ftell(sourcefile);
	rewind(sourcefile);	// Point to the start of the file.
	
	fread(buffer, sizeof(char), size, sourcefile);
	fclose(sourcefile);
	return true;
}

char* SourceFile::getcontent() {
	return buffer;
}
