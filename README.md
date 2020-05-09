Floating-Point Workbench
====================================================================================================

This repo is just a random assortment of test programs for exploring floating-point numbers (IEEE
754).

For an explanation of IEEE 754 floating point and how it works, see [_IEEE Standard 754 Floating
Point Numbers_][fp].


Building
----------
This project uses the CMake build tool. CMake is a meta-build system that locates and uses your
local development tools to build the project if possible.

To build, first install [CMake][https://cmake.org/]. Then go to the project root directory and run
the following command:

    cmake -B build

This will locate your installed development tools and configure your project build in the `build/`
directory. After that, whenever you want a new build, run this command:

    cmake --build build

This will build a debug version of the project, located in `build/Debug/`. To build a release
version, run

    cmake --build build --config release

You can find the built release executables in `build/Release/`.


----------------------------------------------------------------------------------------------------
Steve Hollasch <steve@hollasch.net><br>
https://github.com/hollasch/fpWorkbench

[fp]: https://steve.hollasch.net/cgindex/coding/ieeefloat.html
