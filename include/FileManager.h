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
    // Constructor
    FileManager(const std::string& input, const std::string& output);

    // Get the size of the file in bytes
    long long getFileSize();

    // Read the entire file into a buffer
    std::vector<char> readFile();

    // Write a buffer of data to a file
    void writeFile(const std::vector<char>& data);

    // Utility to check if file exists
    bool fileExists();
};

#endif