/**
 * @copyright Andrey Borisovich Quality Technologies
 * SPDX - License - Identifier: Apache - 2.0
*/

#include <fwsign/unit_test/TomlReaderTestFixture.hpp>
#include <fwsign/test_utils/FileHandler.hpp>
#include <fwsign/TomlReader.hpp>
#include <gtest/gtest.h>
#include <filesystem>
#include <optional>
#include <sstream>
#include <iostream>

namespace fwsign::test::unit_test
{

namespace fs = std::filesystem;

class TomlReaderTest : public ::testing::TestWithParam<fs::path>, public ::testing::EmptyTestEventListener
{
public:
	virtual void SetUp()
	{
		// write config/formatted_data.toml file
		const fs::path tomlFileInConfigDir(fixture.fwsignConfigDir /
			fixture.tomlTypesData.matchingFormatTextFilename);
		std::string textToWrite;
		for(auto& entry : fixture.tomlTypesData.matchingFormatText)
		{
			textToWrite += entry + "\n";
		}
		fileHandler.fileWrite(tomlFileInConfigDir, textToWrite);
		ASSERT_FALSE(fs::is_empty(tomlFileInConfigDir));

		// write config/bad_mtl.toml
		fileHandler.fileWrite(fixture.fwsignConfigDir / fixture.badTomlFilename,
			fixture.badTomlContent);
		ASSERT_FALSE(fs::is_empty(fixture.fwsignConfigDir / fixture.badTomlFilename));

		// copy mtl.toml as mtl.xml
		const fs::path xmlFile = fixture.fwsignConfigDir / fixture.notAtomlFile;
		fs::copy_file(fixture.fwsignConfigDir / fixture.exampleTomlFilename, xmlFile,
			fs::copy_options::overwrite_existing);
		ASSERT_FALSE(fs::is_empty(xmlFile));

		// write config/mixed_format_data.toml
		textToWrite = "";
		const fs::path mixedFormatToml = fixture.fwsignConfigDir / fixture.tomlTypesData.mixedFormatTexttFilename;
		for(auto& entry : fixture.tomlTypesData.mixedFormatText)
		{
			textToWrite += entry + "\n";
		}
		fileHandler.fileWrite(mixedFormatToml, textToWrite);
		ASSERT_FALSE(fs::is_empty(mixedFormatToml));
	}

	virtual void OnTestEnd(const ::testing::TestInfo& test_info)
	{
		if(test_info.result()->Failed())
		{
			std::cout << test_info.test_case_name() << "   failed   " << test_info.name() << std::endl;
		}
	}

	TomlReaderTestFixture fixture;
	fwsign::test::utils::FileHandler fileHandler;
};

INSTANTIATE_TEST_CASE_P(TomlReaderParamTest, TomlReaderTest, ::testing::Values(
	fs::path("config/formatted_data.toml"),		// relative path
	fs::path("formatted_data.toml"),				// only filename - search in config directory
	fs::path("mixed_format_data.toml"),				// same data but with different whitespaces and comments
	fs::path("config"),								// directory name - expect error
	fs::path("mtl.xml"),							// wrong file extension - expect error
	fs::path("in/nonexistant.toml")				// file does not exist - expect error
));

/**
 * @brief This recursive test validates how TomlFileReader behaves
 * when different paths are passed to tomlFileRead function and
 * different formats of toml is provided.
 * @param  Test class name used by GTest.
 * @param  Test name used by GTest.
*/
TEST_P(TomlReaderTest, readingTomlFileFormattedData)
{
	fs::path pathTested = GetParam();
	fwsign::TomlReader tomlReader;
	std::optional<toml::table> result = tomlReader.tomlFileRead(pathTested);

	if(!fs::exists(pathTested) && !fs::exists(fixture.fwsignConfigDir / pathTested))
	{
		ASSERT_FALSE(result.has_value());
		return;
	}

	if(!fs::is_regular_file(pathTested) && !fs::is_regular_file(fixture.fwsignConfigDir / pathTested))
	{
		ASSERT_FALSE(result.has_value());
		return;
	}

	if(pathTested.extension() != ".toml")
	{
		ASSERT_FALSE(result.has_value());
		return;
	}

	std::ostringstream temp;
	temp << result.value();
	std::string stringResult = temp.str();

	// toml content after parsing is unordered - check for substrings
	for(auto& entry : fixture.tomlTypesData.matchingFormatText)
	{
		ASSERT_TRUE(stringResult.find(entry) != std::string::npos) <<
			"Did not find:\n" << entry << "\nin:\n" << stringResult << std::endl;
	}
}

/**
 * @brief This test reads original MTL platform TOML file.
*/
TEST_F(TomlReaderTest, readingTomlMtlFile)
{
	const fs::path tomlFileInConfigDirRelative = (fixture.fwsignConfigDir / fixture.exampleTomlFilename);
	std::string_view fileContent = fileHandler.fileRead(tomlFileInConfigDirRelative);
	ASSERT_FALSE(fileContent.empty());

	fwsign::TomlReader tomlReader;
	std::optional<toml::table> result = tomlReader.tomlFileRead(fixture.exampleTomlFilename);
	ASSERT_TRUE(result.has_value());
}

}
