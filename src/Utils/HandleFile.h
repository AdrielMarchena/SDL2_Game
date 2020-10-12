#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace Utils
{

class HandleFile	
{
public:
	HandleFile(const std::string& pathfile);
	HandleFile();
	~HandleFile();
	

	void setPathFile(const std::string& pathfile);
	const std::string& getPathFile();

	std::stringstream read();

private:
	std::string pathFile;

};

}


