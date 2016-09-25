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

	if(argc != 3) {
		printUsage(argv);
		exit(EXIT_FAILURE);
	}
	
	Bitmap bitmap;
	SourceFile sfile(argv[1]);
	char* path;
	path = (char*) malloc (1024);

	strcpy(path, getenv("HOME"));
	strcat(path, "/Pictures/");
	strcat(path, argv[2]);

	if(sfile.readfile()) {
		cout << "[ + ] File read successfully." << endl;
	} else {
		cout << "[ - ] Couldn't read file." << endl;
		exit(2);
	}

	if(bitmap.createbmp(path, sfile.getcontent())) {
		cout << "[ + ] Bitmap created. Saving under "
			<< path << endl;
	} else {
		cout << "[ - ] Failed to create bitmap." << endl;
	}
	return 0;
}
