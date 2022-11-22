/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#include <fwsign/test_utils/FileHandler.hpp>
#include <iostream>
#include <fstream>

namespace fwsign::test::utils
{

namespace fs = std::filesystem;

std::string_view FileHandler::fileRead(const std::filesystem::path& filePath)
{
	fileContent = "";
	if(!fs::exists(filePath))
		throw fs::filesystem_error("No such file or directory", filePath, std::error_code());
	if(!fs::is_regular_file(filePath))
		throw fs::filesystem_error("Path target is not a regular file", filePath, std::error_code());
	std::ifstream file;
	file.open(filePath);
	if(file.is_open())
	{
		while(file)
		{
			char c = file.get();
			if(c != EOF)
				fileContent += c;
		}
		if(fileContent.empty())
			printState(file);
		file.close();
	}

	return std::string_view(fileContent);
}

void FileHandler::fileWrite(const std::filesystem::path& filePath, std::string_view fileContent)
{
	this->fileContent = fileContent;
	fileWrite(filePath);
}

void FileHandler::fileWrite(const std::filesystem::path& filePath) const
{
	if(fs::exists(filePath) && !fs::is_regular_file(filePath))
		throw fs::filesystem_error("Path exists but is not a file", filePath, std::error_code());

	if(filePath.has_parent_path())
		fs::create_directories(filePath.parent_path());

	std::ofstream file;
	file.open(filePath, std::ios::out | std::ios::trunc);
	if(file.is_open())
		file << fileContent;
	file.close();
}

void FileHandler::printState(const std::ios& stream)
{
	std::cout << " good()=" << stream.good();
	std::cout << " eof()=" << stream.eof();
	std::cout << " fail()=" << stream.fail();
	std::cout << " bad()=" << stream.bad();
}
}
