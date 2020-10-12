#include "HandleFile.h"

namespace Utils 
{
	HandleFile::HandleFile(const std::string& pathfile)
	{
		this->pathFile = pathFile;
	}

	HandleFile::HandleFile()
	{
	}

	HandleFile::~HandleFile()
	{
	}

	void HandleFile::setPathFile(const std::string& pathFile)
	{
		this->pathFile = pathFile;
	}

	const std::string& HandleFile::getPathFile()
	{
		return pathFile;
	}
	std::stringstream HandleFile::read()
	{
		std::ifstream stream(pathFile);
		std::string line;
		std::stringstream stringReturn;
		if (!stream.is_open())
		{
			return (std::stringstream)"Not founded";
		}
		while (getline(stream, line)) {
			stringReturn << line + '\n';
		}
		stream.close();
		return stringReturn;
	}
	bool HandleFile::write(const std::string& line)
	{
		std::ofstream stream(pathFile, std::ios::app);
		if (stream.is_open()) {
			stream << line;
			stream.close();
			return true;
		}
		else {
			stream << "";
			stream.close();
			return false;
		}
	}
}


