# fw-sign

Fw-sign is a DSP firmware image creation and signing tool targeting the DSP on certain Intel System-on-Chip (SoC).
Someday it will be used by the Sound Open Firmware (SOF) to generate binary image files
replacing existing [SOF/rimage](https://github.com/thesofproject/rimage) project (more documentation here - [Rimage SOF Project documentation](https://thesofproject.github.io/latest/developer_guides/rimage/index.html).

## How to build

Fw-sign uses [CMake presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) system to build and execute unit tests.  
Minimal requirements are:
- [CMake](https://cmake.org/download/) 3.22 or newer
- for Linux: gcc7+
- for Windows: MSVC 19.32+

Project uses C++17, language support table across compilers can be found [here](https://en.cppreference.com/w/cpp/compiler_support/17#C.2B.2B17_library_features).

Currently supported operating systems:
- Windows
```powershell
cmake --preset x64-debug-windows                             # Runs CMake configure step
cmake --build --preset x64-debug-windows                     # Runs CMake build
ctest --preset x64-debug-windows                             # Executes unit tests
```
- Linux (tested on Ubuntu latest)
```bash
cmake --preset x64-debug-linux                               # Runs CMake configure step
cmake --build --preset x64-debug-linux                       # Runs CMake build
ctest --preset x64-debug-linux                               # Executes unit tests
```
Tested generators:
- Ninja
- MSVC

## Code guidelines

Fw-sign defines set of style rules using [Editorconfig](https://editorconfig.org/) which is natively supported by Github.  
Among those, there are project rules related to C and C++ files:
- C++ source files have .cpp extension
- C++ header files have .hpp extension
- Headers with mixed C/C++ code or purely C headers have .h extension

Following those simple rules we can easily distinguish what headers should never be included from C headers  
(which are mostly external definitions to fw-sign project).
