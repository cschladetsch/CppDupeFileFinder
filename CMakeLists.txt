cmake_minimum_required(VERSION 3.10)
project(DuplicateFileFinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/FileUtils.cpp
    src/ProgressBar.cpp
    src/DuplicateFinder.cpp
)

add_executable(DuplicateFileFinder ${SOURCES})

# linking OpenSSL for MD5 hashing
find_package(OpenSSL REQUIRED)
target_link_libraries(DuplicateFileFinder OpenSSL::Crypto)

