# Aurix cmake code sample

This repository hosts Aurix code sample Blinky_LED_1_KIT_TC334_LK taken from
[Infineon/AURIX_code_examples](https://github.com/Infineon/AURIX_code_examples)
repository and adapted to be compiled with CMake build system.

## Prerequisites

This project provides configuration for building code with open source tricore
compiler, available at
[EEESlab/tricore-gcc-toolchain-11.3.0](https://github.com/EEESlab/tricore-gcc-toolchain-11.3.0). For any other compiler, manual configuration to
match needed settings may be required.

Before building, compiler executables must be available from PATH.

## Building

### Using default CMake presets

This repository ships some CMake presets to ease building on different machines
and to allow easy IDE integration.

To build from the command line, run following command from root folder of this
repo:

```
$ cmake --preset debug
$ cmake --build out/debug
```

To get a list of existing Configure presets:

```
$ cmake --list-presets
```

### Customize presets using local config

It's possible to customize cmake presets by defining a `CMakeUserPresets.json`
file with new presets, inheriting from the default one.

As an example, the following user config file creates a new `devel` preset
which enable cppcheck analysis and uses GNU Make as generator:

```json
{
    "version": 2,
    "cmakeMinimumRequired": {
        "major": 3,
        "minor": 14,
        "patch": 0
    },
    "configurePresets": [
        {
            "name": "devel",
            "displayName": "Custom Devel",
            "generator": "Unix Makefiles",
            "binaryDir": "${sourceDir}/out/${presetName}",
            "inherits": [
                "default-build",
                "cppcheck"
            ],
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        }
    ]
}
```

Then configure with the new preset:

```
$ cmake --preset devel
$ cmake --build out/devel
```

### Manual CMake build

Project can be built manually with cmake if preset feature cannot be used.

The following command should build software in debug mode with the open source
compiler:

```
$ cmake -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_TOOLCHAIN_FILE=cmake/tricore_opensource_toolchain.cmake \
    -B out/localbuild \
    .

-- The C compiler identification is GNU 11.3.1
-- The CXX compiler identification is GNU 11.3.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /home/user/Workspace/tricore-gcc-toolchain-11.3.0/INSTALL/bin/tricore-elf-gcc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /home/user/Workspace/tricore-gcc-toolchain-11.3.0/INSTALL/bin/tricore-elf-g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (3.7s)
-- Generating done (0.0s)
-- Build files have been written to: /home/user/Workspace/aurix-cmake-code-sample/out/localbuild
```