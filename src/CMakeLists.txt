#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies.
#
# SPDX-License-Identifier: Apache-2.0
#

target_sources(FwSign PRIVATE main.cpp)

# tests implement their own main function - not adding main.cpp here
target_sources(FwSignSources INTERFACE
	World.cpp
	TomlReader.cpp)
