# Tycoon Game

Resource-management and business simulation game built with C++, Win32, DirectX11, and Dear ImGui.

## Overview

The player builds an industrial economy by:
- purchasing and upgrading buildings,
- managing production investments,
- trading resources in a dynamic market,
- growing reputation to unlock stronger opportunities.

## Project Structure

- `include/`: public headers
- `src/`: implementation files
- `tests/`: Catch2 unit tests for core simulation modules
- `lib/`: third-party dependencies (Dear ImGui)

## Build (Visual Studio)

1. Open `Tycoon.sln`.
2. Retarget toolset if prompted.
3. Build and run `Tycoon` from Visual Studio.

Notes:
- The project is configured for C++20.
- Warning level is set to strict (`/W4` and `/WX`).

## Build and Test (CMake)

This path builds the core simulation library and unit tests.

```powershell
cmake -S . -B build -DTYCOON_BUILD_TESTS=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

## Quality Checks

Format code:

```powershell
clang-format -i include/**/*.h src/**/*.cpp tests/**/*.cpp
```

Run static analysis:

```powershell
clang-tidy src/*.cpp src/**/*.cpp -- -Iinclude -Isrc -std=c++20
```

![image](https://github.com/user-attachments/assets/aee54590-bd64-4c0c-acb8-302f0524a2c8)