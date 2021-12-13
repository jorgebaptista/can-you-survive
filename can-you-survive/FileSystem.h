#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

class FileSystem
{
public:
	static FileSystem &instance(); // singleton instance of FileSystem
	std::string ReadMapFile(std::string fileName); // read the contents of a file

private:
	FileSystem(); // constructor
};

