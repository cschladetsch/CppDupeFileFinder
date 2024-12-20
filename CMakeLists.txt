cmake_minimum_required(VERSION 3.10)

# Set project name and C++ standard
project(DuplicateFileFinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find OpenSSL and ensure it's available
find_package(OpenSSL REQUIRED)

# Add Google Test subdirectory (make sure to download or clone googletest into external/googletest)
enable_testing()
add_subdirectory(external/googletest)

# Include directories for Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Define source files for the main project
set(SOURCES
    src/main.cpp
    src/FileUtils.cpp
    src/ProgressBar.cpp
    src/DuplicateFinder.cpp
)

# Create a library for the core application logic
add_library(DuplicateFileFinderLib ${SOURCES})

# Create the executable for the main application (links with OpenSSL and DuplicateFileFinderLib)
add_executable(DuplicateFileFinder ${SOURCES})
target_link_libraries(DuplicateFileFinder DuplicateFileFinderLib OpenSSL::Crypto)

# Add the test executable for Google Test
add_executable(DuplicateFinderTest tests/test_DuplicateFinder.cpp)

# Link the test executable with gtest, gtest_main, and your application library
target_link_libraries(DuplicateFinderTest gtest gtest_main DuplicateFileFinderLib OpenSSL::Crypto)

# Enable testing and add the test to CTest
add_test(NAME DuplicateFinderTest COMMAND DuplicateFinderTest)

