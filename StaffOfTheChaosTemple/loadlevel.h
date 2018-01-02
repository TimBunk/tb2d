#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#include "level.h"
#include "textfile.h"

class Loadlevel
{
public:
	Loadlevel();
	~Loadlevel();

	Level* LoadFromFile(char* filename);

private:
	Textfile* textfile;
};

#endif // !LOADLEVEL_H
