cmake_minimum_required(VERSION 3.20)

project(TycoonGame LANGUAGES CXX)

option(TYCOON_BUILD_TESTS "Build unit tests" ON)

set(TYCOON_CORE_SOURCES
    src/Building.cpp
    src/BuildingFactory.cpp
    src/Production.cpp
    src/Resource.cpp
    src/resourceBuildings/CrystalMine.cpp
    src/resourceBuildings/DiamondMine.cpp
    src/resourceBuildings/Mine.cpp
    src/resourceBuildings/PowerPlant.cpp
    src/resourceBuildings/ResearchLab.cpp
    src/resourceBuildings/Woodcutter.cpp
    src/productionBuildings/Furniture.cpp
    src/productionBuildings/Jewelry.cpp
    src/productionBuildings/Railroads.cpp
    src/productionBuildings/Tools.cpp
)

add_library(tycoon_core STATIC ${TYCOON_CORE_SOURCES})
target_compile_features(tycoon_core PUBLIC cxx_std_20)
target_include_directories(tycoon_core PUBLIC include PRIVATE src)

if(MSVC)
    target_compile_options(tycoon_core PRIVATE /W4 /WX /permissive-)
else()
    target_compile_options(tycoon_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(WIN32)
    add_executable(tycoon_app WIN32
        lib/imgui.cpp
        lib/imgui_draw.cpp
        lib/imgui_tables.cpp
        lib/imgui_widgets.cpp
        lib/imgui_impl_dx11.cpp
        lib/imgui_impl_win32.cpp
        src/TycoonGame.cpp
        src/main.cpp
    )

    target_compile_features(tycoon_app PRIVATE cxx_std_20)
    target_include_directories(tycoon_app PRIVATE include src lib)
    target_link_libraries(tycoon_app PRIVATE tycoon_core d3d11 dxgi d3dcompiler)

    if(MSVC)
        target_compile_options(tycoon_app PRIVATE /W4 /WX /permissive-)
    else()
        target_compile_options(tycoon_app PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()

if(TYCOON_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
