#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies
#
# SPDX-License-Identifier: Apache-2.0
#

include(FetchContent)
FetchContent_Declare(
	tomlplusplus
	GIT_REPOSITORY	https://github.com/marzer/tomlplusplus.git
	GIT_TAG			v3.2.0
)
FetchContent_MakeAvailable(tomlplusplus)

target_compile_definitions(FwSignSources INTERFACE TOML_HEADER_ONLY)
target_include_directories(FwSignSources INTERFACE ${tomlplusplus_SOURCE_DIR}/include)
