#include "textfile.h"

Textfile::Textfile()
{
	eof = false;
}

Textfile::~Textfile()
{
	file.close();
}

void Textfile::Create(const char * filename)
{
	file.close();
	file.open(filename, std::ios::out);
	Open(filename);
}

bool Textfile::Open(const char * filename)
{
	file.close();
	file.open(filename, std::ios::out | std::ios::in);
	if (!file.is_open()) {
		std::cout << "Error opening the file: " << filename << std::endl;
		return false;
	}
	return true;
}

void Textfile::Write(std::string text)
{
	file.write(text.c_str(), text.size());
	file.write("\n", 1);
}

void Textfile::StartReading()
{
	file.seekg(0);
	eof = false;
}

std::string Textfile::ReadLine()
{
	std::string datastream;
	if (!std::getline(file, datastream)) {
		eof = true;
	}
	return datastream;
}

bool Textfile::EndOfFile()
{
	return eof;
}

void Textfile::Close()
{
	file.close();
}
