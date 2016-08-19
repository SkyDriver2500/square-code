#ifndef __SOURCEPARSER_H_INCLUDED__
#define __SOURCEPARSER_H_INCLUDED__
class SourceFile {
public:
	SourceFile(char *sourcefilename);
	bool readfile();
	char* getcontent();
private:
	char *sourcefilename;
	char *buffer;
};

#endif
