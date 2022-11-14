/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#pragma once
#include <string_view>

namespace fwsign
{

class World
{
public:
	std::string_view greet();
	int parse(const std::string_view toml);

private:
	std::string_view greeting = {"Hello!"};
};

}
