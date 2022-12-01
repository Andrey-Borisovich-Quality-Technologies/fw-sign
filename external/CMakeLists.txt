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

include(ExternalProject)

# Additional tools are required to build OpenSSL on Windows, see
# https://github.com/openssl/openssl/blob/master/NOTES-WINDOWS.md#native-builds-using-visual-c++
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
	# Use timestamps generated from unpacking not downloading the archive
	cmake_policy(SET CMP0135 NEW)

	cmake_path(SET PERL_SOURCE_DIR NORMALIZE
		"${CMAKE_CURRENT_LIST_DIR}/strawberryperl/src/strawberryperl")
	cmake_path(SET PERL_INSTALL_DIR NORMALIZE "${CMAKE_CURRENT_LIST_DIR}/strawberryperl")
	cmake_path(APPEND PERL_INSTALL_DIR "perl/bin/perl.exe" OUTPUT_VARIABLE PERL_EXECUTABLE)

	ExternalProject_Add(strawberryperl
		URL		https://strawberryperl.com/download/5.32.1.1/strawberry-perl-5.32.1.1-64bit-portable.zip
		URL_HASH			SHA256=692646105b0f5e058198a852dc52a48f1cebcaf676d63bbdeae12f4eaee9bf5c
		DOWNLOAD_DIR		"${CMAKE_CURRENT_LIST_DIR}"
		PREFIX				"${CMAKE_CURRENT_LIST_DIR}/strawberryperl"
		CONFIGURE_COMMAND	""
		BUILD_COMMAND		""
		TEST_COMMAND		${PERL_SOURCE_DIR}/portableshell.bat
		INSTALL_COMMAND		cd ${CMAKE_CURRENT_LIST_DIR}
		COMMAND				${CMAKE_COMMAND} -E copy_directory ${PERL_SOURCE_DIR} ${PERL_INSTALL_DIR}
		STEP_TARGETS		install
		USES_TERMINAL_DOWNLOAD	True
		USES_TERMINAL_TEST		True
		USES_TERMINAL_INSTALL	True
	)

	cmake_path(SET NASM_SOURCE_DIR NORMALIZE "${CMAKE_CURRENT_LIST_DIR}/nasm/src/nasm")
	cmake_path(SET NASM_INSTALL_DIR NORMALIZE "${CMAKE_CURRENT_LIST_DIR}/nasm")

	ExternalProject_Add(nasm
		URL					https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/win64/nasm-2.15.05-win64.zip
		URL_HASH			SHA256=f5c93c146f52b4f1664fa3ce6579f961a910e869ab0dae431bd871bdd2584ef2
		DOWNLOAD_DIR		"${CMAKE_CURRENT_LIST_DIR}"
		PREFIX				"${CMAKE_CURRENT_LIST_DIR}/nasm"
		CONFIGURE_COMMAND	""
		BUILD_COMMAND		""
		INSTALL_COMMAND		${CMAKE_COMMAND} -E copy ${NASM_SOURCE_DIR}/nasm.exe
							${NASM_INSTALL_DIR}/nasm.exe
		COMMAND				${CMAKE_COMMAND} -E copy ${NASM_SOURCE_DIR}/rdoff
							${NASM_INSTALL_DIR}/rdoff
		STEP_TARGETS		install
		USES_TERMINAL_DOWNLOAD	True
		USES_TERMINAL_TEST		True
		USES_TERMINAL_INSTALL	True
	)
endif()

cmake_path(SET OPENSSL_SOURCE_DIR NORMALIZE "${CMAKE_CURRENT_LIST_DIR}/openssl/src/openssl")
cmake_path(ABSOLUTE_PATH OPENSSL_SOURCE_DIR)

cmake_path(SET OPENSSL_INTALL_DIR NORMALIZE "${CMAKE_CURRENT_LIST_DIR}/openssl")
cmake_path(ABSOLUTE_PATH OPENSSL_INTALL_DIR)
cmake_path(NATIVE_PATH OPENSSL_INTALL_DIR OPENSSL_INTALL_DIR)

cmake_path(APPEND OPENSSL_INTALL_DIR "SSL" OUTPUT_VARIABLE OPENSSL_CERT_STORE)

ExternalProject_Add(openssl
	GIT_REPOSITORY			https://github.com/openssl/openssl.git
	GIT_TAG					openssl-3.0.7
	PREFIX					"${CMAKE_CURRENT_LIST_DIR}/openssl"
	CONFIGURE_COMMAND		(cd ${OPENSSL_SOURCE_DIR} &&
							${PERL_EXECUTABLE} Configure VC-WIN64A
							--prefix=${OPENSSL_INTALL_DIR}
							--openssldir=${OPENSSL_CERT_STORE})
	BUILD_COMMAND			(cd ${OPENSSL_SOURCE_DIR} && nmake)
	TEST_COMMAND			(cd ${OPENSSL_SOURCE_DIR} && nmake test)
	INSTALL_COMMAND			(cd ${OPENSSL_SOURCE_DIR} && nmake install)
	STEP_TARGETS			install
	USES_TERMINAL_DOWNLOAD	True
	USES_TERMINAL_UPDATE	True
	USES_TERMINAL_PATCH		True
	USES_TERMINAL_BUILD		True
	USES_TERMINAL_CONFIGURE	True
	USES_TERMINAL_TEST		True
	USES_TERMINAL_INSTALL	True
)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
	ExternalProject_Add_StepDependencies(openssl configure
		strawberryperl-install nasm-install)
endif()

add_dependencies(FwSignSources openssl-install)
