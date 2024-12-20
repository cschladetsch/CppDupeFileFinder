#include <gtest/gtest.h>
#include "DuplicateFinder.h"
#include "FileUtils.h"
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

    std::ofstream(temp_file1) << "Identical content";  // Write identical content to both files
    std::ofstream(temp_file2) << "Identical content";

    // Execute: Call the function to get all files
    std::vector<std::filesystem::path> files = getAllFiles(temp_dir);

    // Simulate the logic for detecting duplicates
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;

    for (const auto& file : files) {
        std::string md5 = computeFileHash(file);  // Get the MD5 hash of each file

        // Debug: Output the MD5 hash and file name
        std::cout << "File: " << file.filename() << " MD5: " << md5 << std::endl;

        file_hashes[md5].push_back(file);  // Group files by their MD5 hash
    }

    // Verify: Check if duplicate files are detected
    bool duplicates_found = false;
    for (const auto& entry : file_hashes) {
        if (entry.second.size() > 1) {  // If there are multiple files with the same hash
            duplicates_found = true;
            std::cout << "Duplicate files found with MD5: " << entry.first << ": ";
            for (const auto& file : entry.second) {
                std::cout << file.filename() << " ";
            }
            std::cout << std::endl;
            break;  // Stop after finding the first duplicate set
        }
    }

    // Verify that duplicates are found
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
// Test for computeMD5() function
TEST(DuplicateFinderTest, ComputeMD5Test) {
    std::cout << "DuplicateFinderTest ComputeMD5Test\n";

    // Setup: Create a temporary file with known content
    std::string temp_file = "test_file.txt";

    // Write the expected content to the file
    std::ofstream file(temp_file);
    file << "Test content";  // Write content to the file
    file.flush();  // Explicitly flush the file to ensure data is written
    file.close();  // Explicitly close the file to ensure it's written

    // Verify: Output file content to debug
    std::ifstream file_check(temp_file);
    std::string file_content((std::istreambuf_iterator<char>(file_check)), std::istreambuf_iterator<char>());
    std::cout << "File content in ComputeMD5Test: \"" << file_content << "\"\n";  // Debugging output

    // Ensure the file is non-empty and has the expected content
    EXPECT_FALSE(file_content.empty());  // Check that the file is not empty
    EXPECT_EQ(file_content, "Test content");  // Check if the content is correct

    // Execute: Call computeMD5()
    std::string md5_hash = computeFileHash(temp_file);

    // Verify: Check if the MD5 hash is as expected (known hash for "Test content")
    EXPECT_EQ(md5_hash, "8bfa8e0684108f419933a5995264d150"); // MD5 for "Test content"

    // Cleanup: Remove the temporary file
    std::filesystem::remove(temp_file);
}

// Test for Identical Files with Different Names
TEST(DuplicateFinderTest, IdenticalFilesDifferentNames) {
    std::cout << "DuplicateFinderTest IdenticalFilesDifferentNames\n";

    // Setup: Create a temporary directory for the files
    std::string temp_dir = "test_dir";
    std::filesystem::create_directory(temp_dir);

    // Create two identical files with different names
    std::string temp_file1 = temp_dir + "/file1.txt";
    std::string temp_file2 = temp_dir + "/file2.txt";

    std::ofstream(temp_file1) << "Identical content";  // Write identical content to both files
    std::ofstream(temp_file2) << "Identical content";

    // Execute: Call the function to get all files
    std::vector<std::filesystem::path> files = getAllFiles(temp_dir);

    // Simulate the logic for detecting duplicates
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;

    for (const auto& file : files) {
        std::string md5 = computeFileHash(file);  // Get the MD5 hash of each file

        // Debug: Output the MD5 hash and file name
        std::cout << "File: " << file.filename() << " MD5: " << md5 << std::endl;

        file_hashes[md5].push_back(file);  // Group files by their MD5 hash
    }

    // Verify: Check if duplicate files are detected
    bool duplicates_found = false;
    for (const auto& entry : file_hashes) {
        if (entry.second.size() > 1) {  // If there are multiple files with the same hash
            duplicates_found = true;
            std::cout << "Duplicate files found with MD5: " << entry.first << ": ";
            for (const auto& file : entry.second) {
                std::cout << file.filename() << " ";
            }
            std::cout << std::endl;
            break;  // Stop after finding the first duplicate set
        }
    }

    // Verify that duplicates are found
    EXPECT_TRUE(duplicates_found);  // Expect that duplicates are found

    // Cleanup: Remove the temporary files and directory
    std::filesystem::remove_all(temp_dir);
}

// Test for Identical Files with Different Content
// Test for Identical Files with Different Content
TEST(DuplicateFinderTest, IdenticalFilesDifferentContent) {
    std::cout << "DuplicateFinderTest IdenticalFilesDifferentContent\n";

    // Setup: Create a temporary directory for the files
    std::string temp_dir = "test_dir";
    std::filesystem::create_directory(temp_dir);

    // Create two files with different content
    std::string temp_file1 = temp_dir + "/file1.txt";
    std::string temp_file2 = temp_dir + "/file2.txt";

    std::ofstream(temp_file1) << "Identical content";  // Identical content
    std::ofstream(temp_file2) << "Different content";  // Different content

    // Verify: Output file content to debug
    std::ifstream file1_check(temp_file1);
    std::ifstream file2_check(temp_file2);
    std::string file1_content((std::istreambuf_iterator<char>(file1_check)), std::istreambuf_iterator<char>());
    std::string file2_content((std::istreambuf_iterator<char>(file2_check)), std::istreambuf_iterator<char>());
    std::cout << "File1 content: \"" << file1_content << "\"\n";  // Debugging output
    std::cout << "File2 content: \"" << file2_content << "\"\n";  // Debugging output

    // Ensure both files are not empty and have the correct content
    EXPECT_FALSE(file1_content.empty());  // Check that the file1 is not empty
    EXPECT_FALSE(file2_content.empty());  // Check that file2 is not empty
    EXPECT_EQ(file1_content, "Identical content");  // Ensure correct content for file1
    EXPECT_EQ(file2_content, "Different content");  // Ensure correct content for file2

    // Execute: Call the function to get all files
    std::vector<std::filesystem::path> files = getAllFiles(temp_dir);

    // Simulate the logic for detecting duplicates
    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;

    for (const auto& file : files) {
        std::string md5 = computeFileHash(file);  // Get the MD5 hash of each file

        // Debug: Output the MD5 hash and file name
        std::cout << "File: " << file.filename() << " MD5: " << md5 << std::endl;

        file_hashes[md5].push_back(file);  // Group files by their MD5 hash
    }

    // Verify: Check the number of hashes (expecting 2 different files with different content)
    EXPECT_EQ(file_hashes.size(), 2);  // Expect two different hashes for the two files

    // Verify: Ensure that duplicates are not found
    bool duplicates_found = false;
    for (const auto& entry : file_hashes) {
        if (entry.second.size() > 1) {
            duplicates_found = true;
            break;  // Stop after finding duplicates
        }
    }
    EXPECT_FALSE(duplicates_found);  // Expect no duplicates because the files are different

    // Cleanup: Remove the temporary files and directory
    std::filesystem::remove_all(temp_dir);
}

