# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DuplicateFileFinder)

# Enable C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages (OpenSSL and Threads)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# Add GoogleTest as a subdirectory
add_subdirectory(external/googletest)

# Include directories for GoogleTest and the rest of the project
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include  # Correct include path for GoogleTest
)

# Set the source files for the project
set(SOURCES
    src/main.cpp
    src/FileUtils.cpp      # Include FileUtils.cpp
    src/DuplicateFinder.cpp
    src/ProgressBar.cpp
)

# Create the executable from the sources
add_executable(DuplicateFileFinder ${SOURCES})

# Link the executable to the necessary libraries
target_link_libraries(DuplicateFileFinder PRIVATE
    OpenSSL::Crypto
    Threads::Threads
)

# Create a library for DuplicateFileFinderLib to be reused if needed
add_library(DuplicateFileFinderLib STATIC 
    src/DuplicateFinder.cpp
    src/FileUtils.cpp      # Include FileUtils.cpp in the library as well
    src/ProgressBar.cpp
)

# Link DuplicateFileFinderLib to the executable
target_link_libraries(DuplicateFileFinder PRIVATE DuplicateFileFinderLib)

# Set up tests
enable_testing()

# Add the test executable for DuplicateFinder
add_executable(DuplicateFinderTest
    tests/test_DuplicateFinder.cpp
    src/FileUtils.cpp  # Include FileUtils.cpp for the test executable
    src/DuplicateFinder.cpp
)

# Link the test executable to Google Test and DuplicateFileFinderLib
target_link_libraries(DuplicateFinderTest PRIVATE 
    DuplicateFileFinderLib
    gtest
    gtest_main
    pthread  # Google Test requires pthreads
    OpenSSL::Crypto  # Explicitly link OpenSSL to the test executable
)

# Add tests to CTest
add_test(NAME DuplicateFinderTest COMMAND DuplicateFinderTest)

