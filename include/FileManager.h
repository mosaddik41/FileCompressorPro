#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <cstdint>

struct CompressionHeader {
    char magic[4];          
    uint32_t originalSize;  
    uint32_t checksum;      
};

class FileManager {
private:
    std::string inputPath;
    std::string outputPath;

public:
    FileManager(const std::string& input, const std::string& output);
    
    bool fileExists();
    std::vector<char> readFile();
    bool writeFile(const std::vector<char>& data);
    
    uint32_t calculateChecksum(const std::vector<char>& data);
    
    bool verifyIntegrity(const std::string& origPath, const std::string& restoredPath);
};

#endif