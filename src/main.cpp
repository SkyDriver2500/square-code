#include <iostream>
#include <cstdlib>
#include <cstring>

#include "bitmap.hpp"
#include "sourceparser.hpp"

using namespace std;

void printUsage(char **args) {
	cout << "Usage:" << endl;
	cout << args[0] << " file dest.bmp" << endl;
}

int main(int argc, char **argv) {
	Bitmap bitmap;
	char* path;
	path = (char*) malloc (1024);
	
	strcpy(path, getenv("HOME"));
	strcat(path, "/Pictures/");
	strcat(path, argv[1]);
	
	if(bitmap.createbmp(path)) {
		cout << "[ + ] Bitmap created. Saving under " 
			<< path << endl;
	} else {
		cout << "[ - ] Failed to create bitmap." << endl;
	}
	return 0;
}
