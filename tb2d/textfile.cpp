#include "textfile.h"

Textfile::Textfile()
{
	// Initialize variables
	eof = false;
}

Textfile::~Textfile()
{
	// Close the file
	file.close();
}

void Textfile::Create(const char * filename)
{
	// Close previous file then create a new one and open it
	file.close();
	file.open(filename, std::ios::out);
	Open(filename);
}

bool Textfile::Open(const char * filename)
{
	// Close previous file
	file.close();
	// Open the file
	file.open(filename, std::ios::out | std::ios::in);
	// If the file could not be opened return false
	if (!file.is_open()) {
		return false;
	}
	return true;
}

void Textfile::Write(std::string text)
{
	// Write a line of text to the textfile
	file.write(text.c_str(), text.size());
	// Start a new line
	file.write("\n", 1);
}

void Textfile::StartReading()
{
	// Set a pointer to the first line of the textfile
	file.seekg(0);
	eof = false;
}

std::string Textfile::ReadLine()
{
	// Read a line of text from the textfile and return it
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
