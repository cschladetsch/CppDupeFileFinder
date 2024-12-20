#ifndef DUPLICATEFILEFINDER_H
#define DUPLICATEFILEFINDER_H

#include <vector>
#include <filesystem>
#include <string>
#include "ProgressBar.h" // Include the ProgressBar header

std::string computeMD5(const std::filesystem::path& filePath);  // Declaration
std::vector<std::filesystem::path> getAllFiles(const std::string& directory);
std::vector<std::vector<std::filesystem::path>> findDuplicateFiles(
    const std::vector<std::filesystem::path>& files, ProgressBar& progressBar);

#endif // DUPLICATEFILEFINDER_H

