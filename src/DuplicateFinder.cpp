#include "FileUtils.h"
#include "DuplicateFinder.h"
#include "ProgressBar.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <omp.h>

// Function to find duplicate files and return them as a vector of vectors
std::vector<std::vector<std::filesystem::path>> findDuplicateFiles(
    const std::vector<std::filesystem::path>& files, ProgressBar& progress) {

    std::unordered_map<std::string, std::vector<std::filesystem::path>> file_hashes;
    size_t total_files = files.size();
    size_t processed_files = 0;

    // Use OpenMP to parallelize MD5 computation across multiple threads
    #pragma omp parallel for
    for (size_t i = 0; i < total_files; ++i) {
        std::string file_hash = computeFileHash(files[i]);

        // Thread-safe update of the file_hashes map
        #pragma omp critical
        file_hashes[file_hash].push_back(files[i]);

        // Update progress
        #pragma omp atomic
        processed_files++;

        // Update progress bar periodically or asynchronously
        if (processed_files % 10 == 0) {
            progress.update(processed_files / static_cast<double>(total_files));
        }
    }

    // Collect duplicates into a vector of vectors
    std::vector<std::vector<std::filesystem::path>> duplicates;
    for (const auto& entry : file_hashes) {
        if (entry.second.size() > 1) {
            duplicates.push_back(entry.second);
        }
    }

    return duplicates;
}

