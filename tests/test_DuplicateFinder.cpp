#include <gtest/gtest.h>
#include "DuplicateFinder.h"
#include <fstream>
#include <filesystem>
#include <iostream>


// Test for duplicate file detection
TEST(DuplicateFinderTest, DetectDuplicateFilesTest) {
	std::cout << "DuplicateFinderTest FOO\n";

    // Setup: create two temporary files with identical content
    std::string temp_dir = "test_dir";
    std::filesystem::create_directory(temp_dir);

    std::string temp_file1 = temp_dir + "/file1.txt";
    std::string temp_file2 = temp_dir + "/file2.txt";

    // Create two identical files
    std::ofstream(temp_file1) << "Test content";
    std::ofstream(temp_file2) << "Test content";  // Same content as file1

    // Execute: Call the function to find all files
    std::vector<std::filesystem::path> files = getAllFiles(temp_dir);

    // Debug: Output the list of files found
    std::cout << "Files found: ";
    for (const auto& file : files) {
        std::cout << file.filename() << " ";
    }
    std::cout << std::endl;

    // Simulate the logic for detecting duplicates
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;

    for (const auto& file : files) {
        std::string md5 = computeMD5(file);

        // Debug: Output the MD5 hash and file name
        std::cout << "File: " << file.filename() << " MD5: " << md5 << std::endl;

        file_hashes[md5].push_back(file);
    }

    // Verify: Check if duplicate files are detected
    bool duplicates_found = false;
    for (const auto& entry : file_hashes) {
        if (entry.second.size() > 1) {
            duplicates_found = true;
            std::cout << "Duplicate files found with MD5: " << entry.first << ": ";
            for (const auto& file : entry.second) {
                std::cout << file.filename() << " ";
            }
            std::cout << std::endl;
            break;
        }
    }

    // Check the result
    EXPECT_TRUE(duplicates_found);  // Expect that duplicates are found

    // Cleanup: Remove the temporary files and directory
    // TODO std::filesystem::remove_all(temp_dir);
}

// Test for getAllFiles() function
TEST(DuplicateFinderTest, GetAllFilesTest) {
	std::cout << "DuplicateFinderTest GetAllFilesTest\n";
    // Setup: create a temporary directory and some files
    std::string temp_dir = "test_dir";
    std::filesystem::create_directory(temp_dir);
    std::ofstream(temp_dir + "/file1.txt") << "Test file 1";
    std::ofstream(temp_dir + "/file2.txt") << "Test file 2";

    // Execute: Call getAllFiles()
    std::vector<std::filesystem::path> files = getAllFiles(temp_dir);

    // Debug: Output the list of files found
    std::cout << "Files found in getAllFiles: ";
    for (const auto& file : files) {
        std::cout << file.filename() << " ";
    }
    std::cout << std::endl;

    // Verify: Check if the correct files are returned
    ASSERT_EQ(files.size(), 2);
    EXPECT_EQ(files[0].filename(), "file1.txt");
    EXPECT_EQ(files[1].filename(), "file2.txt");

    // Cleanup: Remove the temporary files and directory
    std::filesystem::remove_all(temp_dir);
}
// Test for computeMD5() function
// Test for computeMD5() function
TEST(DuplicateFinderTest, ComputeMD5Test) {
    std::cout << "DuplicateFinderTest ComputeMD5Test\n";

    // Setup: create a temporary file with known content
    std::string temp_file = "test_file.txt";

    // Open file in write mode, explicitly avoiding newlines
    std::ofstream file(temp_file, std::ios::out | std::ios::trunc);  
    file << "Test content";  // Write exactly "Test content" with no newline
    file.close();

    // Verify: Output file content to debug
    std::ifstream file_in(temp_file);
    std::string file_content((std::istreambuf_iterator<char>(file_in)), std::istreambuf_iterator<char>());
    std::cout << "File content in ComputeMD5Test: \"" << file_content << "\"\n";  // Debugging output

    // Execute: Call computeMD5()
    std::string md5_hash = computeMD5(temp_file);

    // Verify: Check if the MD5 hash is as expected (known hash for "Test content" without newline)
    EXPECT_EQ(md5_hash, "8bfa8e0684108f419933a5995264d150"); // MD5 for "Test content" without newline

    // Cleanup: Remove the temporary file
    std::filesystem::remove(temp_file);
}

