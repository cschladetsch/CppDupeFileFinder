#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <vector>

struct FileMetadata {
    uintmax_t fileSize;
    std::filesystem::file_time_type lastModified;
    std::string fileHash;
};

using FileCache = std::unordered_map<std::string, FileMetadata>;

std::vector<std::filesystem::path> getAllFiles(const std::string& directory);
std::string computeFileHash(const std::filesystem::path& file_path);
FileCache loadCache(const std::string& cacheFilePath);
void saveCache(const FileCache& cache, const std::string& cacheFilePath);


