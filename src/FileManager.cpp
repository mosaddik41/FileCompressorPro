#include "../include/FileManager.h"
#include <fstream>
#include <iostream>
#include <numeric>

FileManager::FileManager(const std::string& input, const std::string& output) 
    : inputPath(input), outputPath(output) {}

bool FileManager::fileExists() {
    std::ifstream f(inputPath.c_str());
    return f.good();
}

uint32_t FileManager::calculateChecksum(const std::vector<char>& data) {
    uint32_t hash = 0;
    for (char c : data) {
        hash = (hash * 31) + static_cast<unsigned char>(c);
    }
    return hash;
}

std::vector<char> FileManager::readFile() {
    std::ifstream file(inputPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return {};

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    file.read(buffer.data(), size);
    return buffer;
}

bool FileManager::writeFile(const std::vector<char>& data) {
    std::ofstream file(outputPath, std::ios::binary);
    if (!file.is_open()) return false;
    file.write(data.data(), data.size());
    return file.good();
}

bool FileManager::verifyIntegrity(const std::string& origPath, const std::string& restoredPath) {
    std::ifstream f1(origPath, std::ios::binary);
    std::ifstream f2(restoredPath, std::ios::binary);

    if (!f1 || !f2) return false;

    f1.seekg(0, std::ios::end);
    f2.seekg(0, std::ios::end);
    if (f1.tellg() != f2.tellg()) return false;

    f1.seekg(0, std::ios::beg);
    f2.seekg(0, std::ios::beg);


    return std::equal(std::istreambuf_iterator<char>(f1), std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2));
}