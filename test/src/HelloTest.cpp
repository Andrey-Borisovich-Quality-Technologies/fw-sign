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

TEST(HelloTest, TomlParser)
{
	static constexpr std::string_view some_toml = R"(
		[library]
		name = "toml++"
		authors = ["Mark Gillard <mark.gillard@outlook.com.au>"]
		cpp = 17
	)";

	fwsign::World world;

	EXPECT_EQ(world.parse(some_toml), 0);
}

TEST(HelloTest, TomlParserBadFormat)
{
	static constexpr std::string_view some_toml = R"(
		[library]]
		name = "toml++"
		authors = ["Mark Gillard <mark.gillard@outlook.com.au>"]
		cpp = 17
	)";

	fwsign::World world;

	EXPECT_EQ(world.parse(some_toml), 1);
}

}


