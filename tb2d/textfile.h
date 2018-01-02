#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

class Textfile
{
public:
	Textfile();
	~Textfile();

	void Create(char* filename);
	bool Open(char* filename);
	void Write(std::string text);
	void StartReading();
	std::string ReadLine();
	bool EndOfFile();

	void Close();

private:
	std::fstream file;
	bool eof;
};

#endif // !TEXTFILE_H
