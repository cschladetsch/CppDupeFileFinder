#include "FileUtils.h"
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

// Function to compute the hash of a file using the EVP API (MD5)
std::string computeFileHash(const std::filesystem::path& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) return "";

    // Create and initialize the EVP context for MD5
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        std::cerr << "Error creating file hash context." << std::endl;
        return "";
    }

    if (EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr) != 1) {
        EVP_MD_CTX_free(mdctx);
        std::cerr << "Error initializing file hash." << std::endl;
        return "";
    }

    char buffer[4096];  // Buffer for reading files in chunks
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(mdctx, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(mdctx);
            std::cerr << "Error updating file hash." << std::endl;
            return "";
        }
    }

    // Finalize the file hash computation
    unsigned char hash_result[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    if (EVP_DigestFinal_ex(mdctx, hash_result, &hash_len) != 1) {
        EVP_MD_CTX_free(mdctx);
        std::cerr << "Error finalizing file hash." << std::endl;
        return "";
    }

    // Convert the result to a hexadecimal string
    std::stringstream ss;
    for (unsigned int i = 0; i < hash_len; ++i) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)hash_result[i];
    }

    EVP_MD_CTX_free(mdctx);  // Free the EVP context
    return ss.str();  // Return the hexadecimal file hash
}

// Function to get all files in a directory
std::vector<std::filesystem::path> getAllFiles(const std::string& directory) {
    std::vector<std::filesystem::path> files;
	std::cout << "Directory to scan: " << directory << std::endl;
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
		if (!(fs::status(entry).permissions() & fs::perms::owner_read)) {
			std::cerr << "Cannot read " << entry << std::endl;
		}

		if (entry.path().string().find('$') != std::string::npos) continue;

		std::cout << "Scanning folder: " << entry.path() << std::endl;
		try {
				if (std::filesystem::is_regular_file(entry.status())) {
					files.push_back(entry.path());
			}
		} catch (const std::filesystem::filesystem_error& e) {
			std::cerr << "Error reading directory: " << e.what() << std::endl;
		}
	}
    return files;
}

