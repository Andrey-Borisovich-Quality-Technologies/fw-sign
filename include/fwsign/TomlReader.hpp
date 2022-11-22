/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#pragma once
#include <toml++/toml.h>
#include <filesystem>
#include <optional>

namespace fwsign
{

class TomlReader
{
public:
	std::optional<toml::table> tomlFileRead(std::filesystem::path filePath);

private:
	bool resolveFilePath(std::filesystem::path& filePath);

	std::filesystem::path defaultConfigsDir = { "./config" };
};

}
