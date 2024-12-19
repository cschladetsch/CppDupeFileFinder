#include "FileUtils.h"
#include <fstream>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

std::string computeFileHash(const std::string& filePath) {
    unsigned char c[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;
    MD5_Init(&mdContext);

    std::ifstream file(filePath, std::ifstream::binary);
    if (file) {
        char buffer[4096];
        while (file.read(buffer, sizeof(buffer))) {
            MD5_Update(&mdContext, buffer, file.gcount());
        }
        MD5_Update(&mdContext, buffer, file.gcount());
    }
    MD5_Final(c, &mdContext);

    std::ostringstream oss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)c[i];

    return oss.str();
}

FileCache loadCache(const std::string& cacheFilePath) {
    FileCache cache;
    std::ifstream cacheFile(cacheFilePath, std::ios::binary);
    if (cacheFile) {
        size_t cacheSize;
        cacheFile.read(reinterpret_cast<char*>(&cacheSize), sizeof(cacheSize));
        for (size_t i = 0; i < cacheSize; ++i) {
            std::string filePath;
            uintmax_t fileSize;
            std::filesystem::file_time_type lastModified;
            std::string fileHash;

            size_t pathSize;
            cacheFile.read(reinterpret_cast<char*>(&pathSize), sizeof(pathSize));
            filePath.resize(pathSize);
            cacheFile.read(&filePath[0], pathSize);
            cacheFile.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
            cacheFile.read(reinterpret_cast<char*>(&lastModified), sizeof(lastModified));
            size_t hashSize;
            cacheFile.read(reinterpret_cast<char*>(&hashSize), sizeof(hashSize));
            fileHash.resize(hashSize);
            cacheFile.read(&fileHash[0], hashSize);

            cache[filePath] = {fileSize, lastModified, fileHash};
        }
    }
    return cache;
}

void saveCache(const FileCache& cache, const std::string& cacheFilePath) {
    std::ofstream cacheFile(cacheFilePath, std::ios::binary);
    if (cacheFile) {
        size_t cacheSize = cache.size();
        cacheFile.write(reinterpret_cast<const char*>(&cacheSize), sizeof(cacheSize));
        for (const auto& [filePath, metadata] : cache) {
            size_t pathSize = filePath.size();
            cacheFile.write(reinterpret_cast<const char*>(&pathSize), sizeof(pathSize));
            cacheFile.write(filePath.data(), pathSize);
            cacheFile.write(reinterpret_cast<const char*>(&metadata.fileSize), sizeof(metadata.fileSize));
            cacheFile.write(reinterpret_cast<const char*>(&metadata.lastModified), sizeof(metadata.lastModified));
            size_t hashSize = metadata.fileHash.size();
            cacheFile.write(reinterpret_cast<const char*>(&hashSize), sizeof(hashSize));
            cacheFile.write(metadata.fileHash.data(), hashSize);
        }
    }
}
