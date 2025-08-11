cmake_minimum_required(VERSION 3.28)

# Forza clang/clang++
set(CMAKE_C_COMPILER "clang"  CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "" FORCE)

project(CMakeSFMLProject LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# SFML 3.0 via FetchContent (senza esempi/test)
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
    step02)

foreach(step IN LISTS STEPS)
  file(GLOB_RECURSE CPP_SOURCES
    "${step}/src/*.cpp"
    "${step}/functionHandler/**/*.cpp"
  )
  file(GLOB_RECURSE HDR_SOURCES "${step}/headers/*.hpp")

  add_executable(${step} ${CPP_SOURCES} ${HDR_SOURCES})

  # C++17 "puro"
  target_compile_features(${step} PRIVATE cxx_std_17)
  set_property(TARGET ${step} PROPERTY CXX_EXTENSIONS OFF)

  # include path dello step
  target_include_directories(${step} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${step}/headers
  )

  # link SFML 3 + Threads
  target_link_libraries(${step} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    Threads::Threads
  )
endforeach()

file(COPY ${CMAKE_SOURCE_DIR}/resources 
     DESTINATION ${CMAKE_BINARY_DIR})

# Aggiorna la cartella resources ad ogni build
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources to build directory"
)
