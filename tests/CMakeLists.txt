include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.6.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tycoon_core_tests
    core_tests.cpp
)

target_link_libraries(tycoon_core_tests PRIVATE tycoon_core Catch2::Catch2WithMain)
target_compile_features(tycoon_core_tests PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(tycoon_core_tests PRIVATE /W4 /WX /permissive-)
else()
    target_compile_options(tycoon_core_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(Catch)
catch_discover_tests(tycoon_core_tests)
