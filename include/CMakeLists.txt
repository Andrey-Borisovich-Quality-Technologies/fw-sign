#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies.
#
# SPDX-License-Identifier: Apache-2.0
#

target_include_directories(FwSignSources INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# In CMake header files are also sources.
# CMake generates list of dependencies for every source file compiled
# and if header file changes then all compilation units including it will
# be rebuild.
target_sources(FwSignSources INTERFACE
	fwsign/World.hpp)
