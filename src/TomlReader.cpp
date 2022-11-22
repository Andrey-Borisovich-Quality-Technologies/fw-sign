
#include <fwsign/TomlReader.hpp>
#include <iostream>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace fwsign
{

std::optional<toml::table> TomlReader::tomlFileRead(fs::path filePath)
{
	if(!resolveFilePath(filePath))
		return std::nullopt;

	toml::table result;
	try
	{
		result = toml::parse_file(filePath.c_str());
	}
	catch(const toml::parse_error& e)
	{
		std::cerr << e.what() << std::endl;
		return std::nullopt;
	}

	return result;
}

bool TomlReader::resolveFilePath(fs::path& filePath)
{
	// if only filename passed use defaultConfigDir
	if(filePath.has_filename() &&
		filePath.has_extension() &&
		!filePath.has_parent_path())
	{
		filePath = defaultConfigsDir / filePath;
		filePath = filePath.lexically_normal();
	}

	if(!fs::exists(filePath))
	{
		std::cerr << "File or directory not found: " << filePath << std::endl;
		return false;
	}

	if(fs::is_symlink(filePath))
	{
		filePath = fs::read_symlink(filePath);
	}

	if(!fs::is_regular_file(filePath))
	{
		std::cerr << "Provided path: " << filePath << " is not a regular file!" << std::endl;
		return false;
	}

	if(fs::is_empty(filePath))
	{
		std::cerr << "File is empty: " << filePath << std::endl;
		return false;
	}

	if(!filePath.has_extension() || filePath.extension() != ".toml")
	{
		std::cerr << "File does not have .toml extension: " << filePath << std::endl;
		return false;
	}

	filePath = fs::absolute(filePath);

	return true;
}

}
