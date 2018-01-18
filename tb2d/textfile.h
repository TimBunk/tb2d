/**
* @file textfile.h
*
* @brief The Textfile header file.
*/

#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

/**
* @brief The Textfile class
*/
class Textfile
{
public:
	/// @brief Constructor of the Textfile
	Textfile();
	/// @brief Destructor of the Textfile
	~Textfile();

	/// @brief Create a new textfile
	/// @param filename the name of the file
	/// @return void
	void Create(const char* filename);
	/// @brief Open open a already existing file and it will return true on succes
	/// @param filename the name of the file you want to open
	/// @return bool
	bool Open(const char* filename);
	/// @brief Write writes a line of text to the file
	/// @param text is the text you want to write in to the textfile
	/// @return void
	void Write(std::string text);
	/// @brief StartReading will set a pointer to the first line of the textfile
	/// @return void
	void StartReading();
	/// @brief ReadLine reads a line of text from the textfile
	/// @return string
	std::string ReadLine();
	/// @brief EndOfFile checks if the end of the file has been reacheds this is usefull for reading the textfile
	/// @return bool
	bool EndOfFile();
	/// @brief Close closes the textfile
	/// @return void
	void Close();

private:
	std::fstream file; ///< @brief file is the filestream for reading the textfile
	bool eof; ///< @brief eof stand for endOfFile and checks when the eof has been reached
};

#endif // !TEXTFILE_H
