#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager {
private:
    std::string inputPath;
    std::string outputPath;

public:
    
    FileManager(const std::string& input, const std::string& output);

    
    long long getFileSize();

    std::vector<char> readFile();

    void writeFile(const std::vector<char>& data);

    bool fileExists();
};

#endif