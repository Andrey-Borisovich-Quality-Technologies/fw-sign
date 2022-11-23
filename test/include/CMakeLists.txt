#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies
#
# SPDX-License-Identifier: Apache-2.0
#

target_include_directories(FwSignUnitTests PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(FwSignUnitTests PRIVATE
	"fwsign/test_utils/Filehandler.hpp"
	"fwsign/test_utils/TomlReaderTestFixture.hpp")
