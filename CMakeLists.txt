#
# Copyright (c) 2022 Andrey Borisovich Quality Technologies
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required (VERSION 3.22)

project(FwSign DESCRIPTION "Firmware image creation and signing tool" LANGUAGES CXX)

add_executable(fwsign)

set_property(TARGET fwsign PROPERTY CXX_STANDARD 17)

target_include_directories(fwsign PRIVATE include)

add_subdirectory(src)
