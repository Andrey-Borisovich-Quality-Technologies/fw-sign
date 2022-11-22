#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies
#
# SPDX-License-Identifier: Apache-2.0
#

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.1)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(FwSignUnitTests)
set_target_properties(FwSignUnitTests PROPERTIES CXX_STANDARD 17)
target_link_libraries(FwSignUnitTests PUBLIC FwSignSources)
target_sources(FwSignUnitTests PRIVATE
	src/HelloTest.cpp)

target_link_libraries(FwSignUnitTests PRIVATE gtest gtest_main gmock)

include(GoogleTest)
gtest_discover_tests(FwSignUnitTests)

# Copy test resource files
configure_file(${PROJECT_SOURCE_DIR}/config/mtl.toml ${CMAKE_CURRENT_BINARY_DIR}/mtl.toml COPYONLY)
