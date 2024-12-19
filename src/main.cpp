#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "DuplicateFinder.h"
#include "ProgressBar.h"

int main(int argc, char **argv) {
    std::vector<std::string> directories = {"/mnt/c/", "/mnt/d/"};
	if (argc == 3) {
		directories = std::vector<std::string> { argv[1], argv[2] };
	}

    ProgressBar scanProgress(directories.size(), "Scanning Directories");

    // Scan directories and collect all files
    std::vector<std::filesystem::path> allFiles;
    for (const auto& dir : directories) {
        auto files = getAllFiles(dir);
        allFiles.insert(allFiles.end(), files.begin(), files.end());
        scanProgress.update(allFiles.size());
    }
    scanProgress.complete();

    // Initialize progress bar for comparison
    ProgressBar compareProgress(allFiles.size(), "Comparing Files");

    // Compare files to find duplicates
    auto duplicates = findDuplicateFiles(allFiles, compareProgress);
    compareProgress.complete();

    // Display duplicate files
    if (!duplicates.empty()) {
        std::cout << "Duplicate files found:\n";
        for (const auto& group : duplicates) {
            for (const auto& file : group) {
                std::cout << "  " << file << '\n';
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "No duplicate files found." << std::endl;
    }

    return 0;
}

