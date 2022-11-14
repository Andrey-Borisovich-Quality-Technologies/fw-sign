/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#include <gtest/gtest.h>
#include <fwsign/World.hpp>

namespace fwsign::unit_test
{

// Demonstrate some basic assertions.
TEST(HelloTest, HelloWorld)
{
	fwsign::World world;

	// Expect two strings not to be equal.
	EXPECT_STREQ(world.greet().data(), "Hello!");
}

}


