# Duplicate File Finder

Duplicate File Finder is a C++17 application designed to scan specified drives and/or directories and identify files with identical content. It provides real-time progress updates during both the scanning and comparison phases.

It's relatively easy to do, and some paid apps want to pull you into other paid apps, etc.

This is just an example of what must be done, at minimum, using high-perf modern C++ code that is as blunt and correct as possible.

## Features

- Recursively scans specified directories to locate files.
- Calculates MD5 hashes to compare file contents.
- Displays progress bars for both scanning and comparison phases.
- Handles permission errors gracefully, skipping inaccessible files and directories.

## Prerequisites

- C++17 or higher
- CMake 3.10 or higher
- OpenSSL library (for MD5 hashing)

## Installation

### Clone the repository

```bash
$ git clone https://github.com/cschladetsch/duplicate-file-finder.git
$ cd duplicate-file-finder
```

### Create a build directory and navigate into it

```bash
$ mkdir build
$ cd build
```

### Build the project

```bash
$ make
```

## Usage

After building the project, you can run the Duplicate File Finder executable.

Note that with large drives etc, this can take some time. Obviously, I think.

```bash
./DuplicateFileFinder [directory1] [directory2] ...
```

### Example

```bash
$ ./DuplicateFileFinder /mnt/c/ /mnt/d/
$ # Note: Ensure you have the necessary permissions to access the specified directories. The application will skip any directories or files it cannot access due to permission restrictions.
```

### Error Handling

The application handles permission errors gracefully by skipping inaccessible files and directories. Error messages are displayed in the console to inform the user of any issues encountered during execution.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

OpenSSL for providing the MD5 hashing functionality.
