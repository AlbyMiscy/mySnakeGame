cmake_minimum_required(VERSION 3.28)

# Forza clang/clang++
set(CMAKE_C_COMPILER "clang"  CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "" FORCE)

project(CMakeSFMLProject LANGUAGES CXX)

# Output eseguibili nella build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# SFML 3.0 via FetchContent (niente esempi/test)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
    GIT_SHALLOW    ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
set(SFML_BUILD_EXAMPLES   OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

find_package(Threads REQUIRED)

# --- Steps del gioco ---
set(STEPS
    step01
)

foreach(step IN LISTS STEPS)
    # Sorgenti dello step (ricorsivo)
    file(GLOB_RECURSE SOURCES "${step}/*.cpp")

    # Target con lo stesso nome della cartella (es. step01)
    add_executable(${step} ${SOURCES})

    # C++17 "puro" per il target
    target_compile_features(${step} PRIVATE cxx_std_17)
    set_property(TARGET ${step} PROPERTY CXX_EXTENSIONS OFF)

    # Include della cartella dello step
    target_include_directories(${step} PRIVATE ${step})

    # Link a SFML 3 e Threads
    target_link_libraries(${step} PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        Threads::Threads
    )
endforeach()
