### Setup CMake ###
# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.22.1)

# Set the project name
project(DoodleJump VERSION 0.1 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install path
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF ()

### Options ###
# Option to enable logging
option(ENABLE_LOGGING "Enable or disable logging" ON)


### SFML ###
# Specify the SFML version
set(SFML_VERSION 2.5.1)

# Find SFML package
find_package(SFML ${SFML_VERSION} REQUIRED COMPONENTS graphics window system)

### Directories ###
# Include directories for header files
include_directories(include)

# Add subdirectories
add_subdirectory(src/logic)
add_subdirectory(src/game)
add_subdirectory(src/utils)

# Add the executable
add_executable(DoodleJump src/main.cpp)

# Link the libraries
target_link_libraries(DoodleJump PUBLIC game_component logic utils sfml-system sfml-graphics sfml-window)

### Installation ###
# Install the executable to a specified directory
install(TARGETS DoodleJump DESTINATION bin)

### Debug vs Release ###
# Set the build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

# Add custom flags for Debug and Release
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Configuring Debug Build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Configuring Release Build")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
endif ()
