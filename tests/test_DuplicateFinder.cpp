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
        }
    }

    EXPECT_TRUE(duplicates_found);  // Expect that duplicates are found

    // Cleanup: Remove the temporary files and directory
    std::filesystem::remove_all(temp_dir);
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
TEST(DuplicateFinderTest, ComputeMD5Test) {
    std::cout << "DuplicateFinderTest ComputeMD5Test\n";

    // Setup: create a temporary file with known content
    std::string temp_file = "test_file.txt";
    std::ofstream(temp_file) << "Test content";  // Ensure no extra characters here

    // Verify: Output file content to debug
    std::ifstream file(temp_file);
    std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::cout << "File content in ComputeMD5Test: \"" << file_content << "\"\n";  // Debugging output

    // Execute: Call computeMD5()
    std::string md5_hash = computeMD5(temp_file);

    // Verify: Check if the MD5 hash is as expected (known hash for "Test content")
    EXPECT_EQ(md5_hash, "8bfa8e0684108f419933a5995264d150"); // MD5 for "Test content"

    // Cleanup: Remove the temporary file
    std::filesystem::remove(temp_file);
}

// Test for empty directories
TEST(DuplicateFinderTest, CompareEmptyDirectories) {
    std::cout << "DuplicateFinderTest CompareEmptyDirectories\n";

    // Setup: create two empty temporary directories
    std::string dir1 = "empty_dir1";
    std::string dir2 = "empty_dir2";
    std::filesystem::create_directory(dir1);
    std::filesystem::create_directory(dir2);

    // Execute: Call the function to find all files in both directories
    std::vector<std::filesystem::path> files_dir1 = getAllFiles(dir1);
    std::vector<std::filesystem::path> files_dir2 = getAllFiles(dir2);

    // Simulate the logic for detecting duplicates across the directories
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;

    for (const auto& file : files_dir1) {
        std::string md5 = computeMD5(file);
        file_hashes[md5].push_back(file);
    }

    for (const auto& file : files_dir2) {
        std::string md5 = computeMD5(file);
        file_hashes[md5].push_back(file);
    }

    // Verify: No duplicates should be found as both directories are empty
    EXPECT_TRUE(file_hashes.empty());  // No files in the directories

    // Cleanup: Remove the temporary directories
    std::filesystem::remove_all(dir1);
    std::filesystem::remove_all(dir2);
}

// Test for identical files with different names
TEST(DuplicateFinderTest, IdenticalFilesDifferentNames) {
    std::cout << "DuplicateFinderTest IdenticalFilesDifferentNames\n";

    // Setup: create two files with identical content but different names
    std::string dir = "dir_identical";
    std::filesystem::create_directory(dir);
    std::ofstream(dir + "/file1.txt") << "Identical content";
    std::ofstream(dir + "/file2.txt") << "Identical content";  // Same content

    // Execute: Call the function to find all files in the directory
    std::vector<std::filesystem::path> files = getAllFiles(dir);

    // Simulate the logic for detecting duplicates
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;
    for (const auto& file : files) {
        std::string md5 = computeMD5(file);
        file_hashes[md5].push_back(file);
    }

    // Verify: The files with identical content should be grouped as duplicates
    bool duplicates_found = false;
    for (const auto& entry : file_hashes) {
        if (entry.second.size() > 1) {
            duplicates_found = true;
            std::cout << "Duplicate files found with MD5: " << entry.first << ": ";
            for (const auto& file : entry.second) {
                std::cout << file.filename() << " ";
            }
            std::cout << std::endl;
        }
    }

    EXPECT_TRUE(duplicates_found);  // Duplicate files should be found

    // Cleanup: Remove the temporary files and directory
    std::filesystem::remove_all(dir);
}

// Test for directory with subdirectory
TEST(DuplicateFinderTest, DirectoryWithSubdirectory) {
    std::cout << "DuplicateFinderTest DirectoryWithSubdirectory\n";

    // Setup: create two directories, one containing a subdirectory
    std::string dir = "dir_with_subdir";
    std::filesystem::create_directory(dir);
    std::filesystem::create_directory(dir + "/subdir");
    std::ofstream(dir + "/file1.txt") << "File in main directory";
    std::ofstream(dir + "/subdir/file2.txt") << "File in subdirectory";

    // Execute: Call the function to find all files in the directory, including subdirectories
    std::vector<std::filesystem::path> files = getAllFiles(dir);

    // Verify: Check that both files exist
    bool file1_found = false;
    bool file2_found = false;
    for (const auto& file : files) {
        if (file.filename() == "file1.txt") {
            file1_found = true;
        }
        if (file.filename() == "file2.txt") {
            file2_found = true;
        }
    }

    EXPECT_TRUE(file1_found);
    EXPECT_TRUE(file2_found);

    // Cleanup: Remove the temporary directories and files
    std::filesystem::remove_all(dir);
}

// Test for identical files with different content
TEST(DuplicateFinderTest, IdenticalFilesDifferentContent) {
    std::cout << "DuplicateFinderTest IdenticalFilesDifferentContent\n";

    // Setup: create two files with different content
    std::string dir = "dir_diff_content";
    std::filesystem::create_directory(dir);
    std::ofstream(dir + "/file1.txt") << "Content of file 1";
    std::ofstream(dir + "/file2.txt") << "Content of file 2";  // Different content

    // Execute: Call the function to find all files in the directory
    std::vector<std::filesystem::path> files = getAllFiles(dir);

    // Simulate the logic for detecting duplicates
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;
    for (const auto& file : files) {
        std::string md5 = computeMD5(file);
        file_hashes[md5].push_back(file);
    }

    // Verify: There should be two unique MD5 hashes, as the files have different content
    ASSERT_EQ(file_hashes.size(), 2);  // Two unique files with different content

    // Cleanup: Remove the temporary files and directory
    std::filesystem::remove_all(dir);
}

