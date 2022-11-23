/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#pragma once
#include <filesystem>
#include <vector>
#include <string>

namespace fwsign::test::unit_test
{

class TomlReaderTestFixture final
{
public:
	const std::filesystem::path exampleTomlFilename = {"mtl.toml"};
	const std::filesystem::path fwsignConfigDir = {"config"};
	const std::filesystem::path badTomlFilename = {"bad_mtl.toml"};
	const std::filesystem::path notAtomlFile = {"mtl.xml"};
	const std::string badTomlContent =
		"[[adsp.mem_zone]]\n"
		"type = \"ROM\"\n"
		"base = \"0x1FF80000\"\n"
		"size = \"0x400\"\n"
		"[[adsp.mem_zone]]\n"
		"type = \"IMR\"\n"
		"base = \"0xA104A000\"\n"
		"size = \"0x2000\"\n"
		"[[adsp.mem_zone]]]\n"
		"type = \"SRAM\"\n"
		"base = \"0xa00f0000\"\n"
		"size = \"0x100000\"\n";

	struct TomlTypesData
	{
		const std::filesystem::path matchingFormatTextFilename = {"formatted_data.toml"};

		/**
		 * @brief This text contains specially adjusted whitespaces to match
		 * toml content after parsing by tomlplusplus library.
		*/
		const std::vector<std::string> matchingFormatText =
		{
			"astring = 'some text'",
			"multilineString = '''\"starts\n"
			"here and goes\n"
			"here...\"'''",
			"literalString = 'some\\path\\with\\backslash'",
			"multilineLiteralString = '''something here\n"
			"and\\backslash\\path\n"
			"and termination'''",
			"positiveInt1 = 9993939",
			"positiveInt2 = 999993333",
			"negativeInt = -82134526",
			"positiveFloat1 = 3.5",
			"positiveFloat2 = 6.25",
			"negativeFloat = -995.921875",
			"bolean1 = true",
			"bolean2 = false",
			"offsetdatetime1 = 2020-02-20T06:10:20Z",
			"offsetdatetime2 = 2030-02-26T06:11:20Z",
			"localdatetime = 2020-02-20T06:10:20",
			"date-key = 2020-02-20",
			"time-key = 06:10:20",
			"numbers = [ 1, 2, 3, 4 ]",
			"strings = [ 'ONE', 'TWO', 'THREE' ]",
			"floats = [ 3.5, 3.75, 999999.75 ]",
			"mixed = [ 3, 999999.75, 'QWEQWE', false ]",
			"nested-array = [ [ 2, 3 ], [ 5, 6 ] ]",
			"[[somename]]\n"
			"val1 = 'VAL1'\n"
			"val2 = 'VAL2'"
		};

		const std::filesystem::path mixedFormatTexttFilename = {"mixed_format_data.toml"};

		/**
		 * @brief This text contains similar content to
		 * @var matchingFormatText however with mixed whitespaces,
		 * formatting styles and comments.
		*/
		const std::vector<std::string> mixedFormatText =
		{
			"astring=\"some text\"",
			"multilineString = \"\"\"\"starts\n"
			"here and goes\n"
			"here...\"\"\"\"",
			"literalString = 'some\\path\\with\\backslash'",
			"multilineLiteralString = '''something here\n"
			"and\\backslash\\path\n"
			"and termination'''",
			"positiveInt1 = +9993939",
			"positiveInt2 =+999993333",
			"negativeInt = -82134526",
			"positiveFloat1 = 3.5",
			"positiveFloat2=+6.25 # some comments here",
			"negativeFloat =-995.921875",
			"bolean1=true",
			"bolean2 = false",
			"offsetdatetime1= 2020-02-20T06:10:20Z",
			"offsetdatetime2=2030-02-26 06:11:20Z",
			"localdatetime =2020-02-20 06:10:20",
			"date-key =2020-02-20",
			"time-key= 06:10:20",
			"numbers= [1,2,3,4]",
			"strings =[\"ONE\",\"TWO\",\"THREE\"]",
			"floats=[+3.5,+3.75,999999.75 ]",
			"mixed= [ 3, 999999.75, 'QWEQWE', false ]",
			"nested-array = [ [2,3], [5,6]]",
			"[[  somename  ]]\n"
			"val1='VAL1'\n"
			"val2='VAL2'"
		};
	};

	TomlTypesData tomlTypesData;
};

}
