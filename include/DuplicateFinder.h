#ifndef DUPLICATEFINDER_H
#define DUPLICATEFINDER_H

#include <vector>
#include <filesystem>
#include "ProgressBar.h"

// Function declaration: Find duplicate files, print them, but don't return any value
std::vector<std::vector<std::filesystem::path>> findDuplicateFiles(
    const std::vector<std::filesystem::path>& files, ProgressBar& progress);

#endif // DUPLICATEFINDER_H

