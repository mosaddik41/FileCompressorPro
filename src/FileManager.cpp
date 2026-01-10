#include "../include/FileManager.h"

FileManager::FileManager(const std::string& input, const std::string& output) 
    : inputPath(input), outputPath(output) {}

bool FileManager::fileExists() {
    return fs::exists(inputPath);
}

long long FileManager::getFileSize() {
    if (fileExists()) {
        return fs::file_size(inputPath);
    }
    return -1;
}

std::vector<char> FileManager::readFile() {
    std::ifstream file("sample.txt", std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) return {};

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    file.read(buffer.data(), size);
    return buffer;
}

void FileManager::writeFile(const std::vector<char>& data) {
    std::ofstream file("output.txt", std::ios::binary);
    if (file.is_open()) {
        file.write(data.data(), data.size());
    }
}