/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#include <fwsign/World.hpp>
#include <iostream>

int main()
{
	fwsign::World world;
	std::cout << world.greet() << std::endl;
	return 0;
}
