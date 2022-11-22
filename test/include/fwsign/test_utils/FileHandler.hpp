/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#pragma once

#include <filesystem>
#include <string_view>
#include <string>

namespace fwsign::test::utils
{

class FileHandler final
{
public:
	FileHandler() = default;
	FileHandler(std::string_view fileContent) : fileContent(fileContent) {};
	std::string_view fileRead(const std::filesystem::path& filePath);
	void fileWrite(const std::filesystem::path& filePath) const;
	void fileWrite(const std::filesystem::path& filePath, std::string_view fileContent);
	void printState(const std::ios& stream);

private:
	std::string fileContent;
};

}
