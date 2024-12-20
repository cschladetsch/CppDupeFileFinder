# Duplicate File Finder

![Icon](resources/icon.png)

## Description

This project is a **Duplicate File Finder** that helps you identify and remove duplicate files in a directory. It uses MD5 hashing to compare files and detect duplicates. The project includes functionality for traversing directories and checking files for duplication based on content, not just filenames.

## Features

- Detects duplicate files in one or more directories.
- Compares files based on MD5 hash.
- Supports subdirectories for recursive searching.
- Identifies identical files even with different names.
- Can handle empty directories gracefully.

## Project Structure

├── CMakeLists.txt       # CMake configuration for building the project
├── src/                 # Source code for the application
│   ├── FileUtils.cpp    # Utility functions for file handling
│   ├── ProgressBar.cpp  # Progress bar implementation for file scanning
│   └── DuplicateFinder.cpp # Main logic for finding duplicate files
├── include/             # Header files
│   ├── FileUtils.h      # Header for file utility functions
│   ├── ProgressBar.h    # Header for the progress bar
│   └── DuplicateFinder.h  # Header for the main logic
├── tests/               # Unit tests for the application
│   └── test\_DuplicateFinder.cpp  # Test file for DuplicateFinder functionality
└── b/                   # Possibly a test or experimental directory (can be reviewed further)

## Prerequisites

To build and run this project, you need to have the following installed:

- **CMake** (version 3.10 or higher)
- **g++** (or any compatible C++ compiler)
- **Google Test** (for unit testing)
- **OpenSSL** (for MD5 hashing)

## Installation

1. Clone the repository:
    ```bash
    git clone <repository_url>
    cd DuplicateFileFinder
    ```

2. Create a build directory and run CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3. Build the project:
    ```bash
    make
    ```

4. Run the tests:
    ```bash
    ./DuplicateFinderTest
    ```

## Usage

To run the Duplicate File Finder application, you can use the following command:

```bash
./DuplicateFinder <path_to_directory>
```

This will scan the directory and report any duplicate files found based on their MD5 hash.

### Example:
```bash
./DuplicateFinder /path/to/directory
```

### Running Tests:
To run the unit tests, use:

```bash
./DuplicateFinderTest
```

You can also use `ctest` to run the tests:

```bash
ctest
```

## Tests

The project includes a set of **unit tests** designed to verify the correctness of the duplicate file detection logic. The tests are implemented using the **Google Test** framework.

### Test Suite Overview:

- **DetectDuplicateFilesTest**: Verifies that duplicate files are detected when two files with identical content are compared.
- **GetAllFilesTest**: Tests that the function `getAllFiles()` correctly returns all files in a directory.
- **ComputeMD5Test**: Ensures that the MD5 hash computation works correctly for a file with known content.
- **CompareEmptyDirectories**: Verifies that the program correctly handles empty directories without errors.
- **IdenticalFilesDifferentNames**: Checks if files with identical content but different names are detected as duplicates.
- **DirectoryWithSubdirectory**: Tests if files in a subdirectory are correctly detected.
- **IdenticalFilesDifferentContent**: Verifies that files with different content are not incorrectly identified as duplicates.
- **CompareTextAndBinaryFiles**: Ensures that both text and binary files are handled correctly.

### Running the Tests:

After building the project, you can run the tests using the following commands:

- **To run all tests**:

    ```bash
    ./DuplicateFinderTest
    ```

- **To run specific tests**:

    You can filter which tests to run using the `--gtest_filter` option:

    ```bash
    ./DuplicateFinderTest --gtest_filter=DuplicateFinderTest.CompareEmptyDirectories
    ```

- **Using `ctest`**:

    If you have configured CTest, you can use the following command to run all tests:

    ```bash
    ctest
    ```

## Contributing

If you want to contribute to this project, feel free to fork it and submit a pull request. Here are the steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Write tests to cover your changes.
4. Run all tests to ensure everything works.
5. Submit a pull request with a detailed description of your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- [Google Test](https://github.com/google/googletest) for unit testing.
- [OpenSSL](https://www.openssl.org/) for MD5 hashing functionality.

