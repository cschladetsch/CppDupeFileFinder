cmake_minimum_required(VERSION 3.10)
project(DuplicateFileFinder)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/FileUtils.cpp
    src/ProgressBar.cpp
    src/DuplicateFinder.cpp
)

# Add executable
add_executable(DuplicateFileFinder ${SOURCES})

# Link external libraries if necessary
# For example, linking OpenSSL for MD5 hashing
find_package(OpenSSL REQUIRED)
target_link_libraries(DuplicateFileFinder OpenSSL::Crypto)

