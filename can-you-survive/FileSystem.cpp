#include "FileSystem.h"

FileSystem::FileSystem()
{
}

FileSystem& FileSystem::instance()
{
	static FileSystem *instance = new FileSystem(); // guaranteed to be destroyed
	// instantiated on first use

	return *instance;
}

std::string FileSystem::ReadMapFile(std::string fileName)
{
	std::ifstream t(fileName); // create ifstream variable to read file
	std::stringstream buffer; // create a buffer to pass the contents of the file inside
	buffer << t.rdbuf(); // pass the contents of the file inside buffer

	std::string map = buffer.str(); // convert buffer to string

	return map; // return the drawing (string)
}


