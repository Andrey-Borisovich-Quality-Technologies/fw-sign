/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#include <fwsign/World.hpp>
#include <toml++/toml.h>
#include <iostream>
#include <sstream>

namespace fwsign
{

std::string_view World::greet()
{
	return greeting;
}

int World::parse(const std::string_view toml)
{
	try
	{
		// parse directly from a string view:
		{
			toml::table tbl = toml::parse(toml);
			std::cout << tbl << "\n";
		}

		// parse from a string stream:
		{
			std::stringstream ss{std::string{toml}};
			toml::table tbl = toml::parse(ss);
			std::cout << tbl << "\n";
		}
	}
	catch(const toml::parse_error& err)
	{
		std::cerr << "Parsing failed:\n" << err << "\n";
		return 1;
	}

	return 0;
}

}



