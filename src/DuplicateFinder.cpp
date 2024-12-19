#include "DuplicateFinder.h"
#include "ProgressBar.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <vector>
#include <iostream>
#include <filesystem>
#include <vector>

#include <openssl/evp.h> // Use EVP functions instead of deprecated MD5 functions

std::vector<std::filesystem::path> getAllFiles(const std::string& directory) {
    std::vector<std::filesystem::path> files;
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                files.push_back(entry.path());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        //TODO LOG std::cerr << "Error accessing " << directory << ": " << e.what() << '\n';
    }
    return files;
}

std::string computeMD5(const std::filesystem::path& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filePath.string());
    }

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        throw std::runtime_error("Failed to create EVP_MD_CTX");
    }

    const EVP_MD* md = EVP_md5();
    if (EVP_DigestInit_ex(mdctx, md, nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("EVP_DigestInit_ex failed");
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("EVP_DigestUpdate failed");
        }
    }
    // Process any remaining bytes
    if (file.gcount() > 0) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(mdctx);
            throw std::runtime_error("EVP_DigestUpdate failed");
        }
    }

    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int result_len;
    if (EVP_DigestFinal_ex(mdctx, result, &result_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        throw std::runtime_error("EVP_DigestFinal_ex failed");
    }

    EVP_MD_CTX_free(mdctx);

    // Convert the result to a hexadecimal string
    std::ostringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < result_len; ++i) {
        hexStream << std::setw(2) << static_cast<int>(result[i]);
    }
    return hexStream.str();
}

std::vector<std::vector<std::filesystem::path>> findDuplicateFiles(
    const std::vector<std::filesystem::path>& files, ProgressBar& progressBar) {
    std::unordered_map<std::string, std::vector<std::filesystem::path>> hashToFileMap;
    size_t totalFiles = files.size();
    for (size_t i = 0; i < totalFiles; ++i) {
        try {
            std::string fileHash = computeMD5(files[i]);
            hashToFileMap[fileHash].push_back(files[i]);
        } catch (const std::exception& e) {
            //TODO LOG std::cerr << "\nError processing file " << files[i] << ": " << e.what() << std::endl;
        }
        // Update comparison progress
        progressBar.update(i + 1); // Pass the current progress
    }

    // Collect duplicate files
    std::vector<std::vector<std::filesystem::path>> duplicates;
    for (const auto& [hash, paths] : hashToFileMap) {
        if (paths.size() > 1) {
            duplicates.push_back(paths);
        }
    }
    return duplicates;
}

