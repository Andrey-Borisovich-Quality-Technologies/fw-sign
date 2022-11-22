#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required (VERSION 3.22)

project(FwSign DESCRIPTION "Firmware image creation and signing tool" LANGUAGES CXX)

add_executable(FwSign)
set_target_properties(FwSign PROPERTIES CXX_STANDARD 17)

add_library(FwSignSources INTERFACE)
target_compile_options(FwSignSources INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(external)

enable_testing()
add_subdirectory(test)

target_link_libraries(FwSign PRIVATE FwSignSources)
