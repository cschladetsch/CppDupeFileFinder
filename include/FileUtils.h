#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <unordered_map>
#include <filesystem>

struct FileMetadata {
    uintmax_t fileSize;
    std::filesystem::file_time_type lastModified;
    std::string fileHash;
};

using FileCache = std::unordered_map<std::string, FileMetadata>;

std::string computeFileHash(const std::string& filePath);
FileCache loadCache(const std::string& cacheFilePath);
void saveCache(const FileCache& cache, const std::string& cacheFilePath);

#endif // FILE_UTILS_H

