#include <iostream>
#include <vector>
#include <string>
#include "../include/FileManager.h"
#include "../include/LZWDictionary.h"

int main() {
    FileManager fm("sample.txt", "output.txt");
    LZWDictionary dict;

    std::cout << "--- C++ File Compressor: Day 2 (Logic Test) ---" << std::endl;

    std::vector<char> fileData = fm.readFile();
    std::string input(fileData.begin(), fileData.end());

    std::string current = "";
    std::vector<int> compressedOutput;

    std::cout << "[PROCESS] Encoding input: " << input << std::endl;

    for (char c : input) {
        std::string next = current + c;
        if (dict.contains(next)) {
            current = next;
        } else {
            compressedOutput.push_back(dict.getCode(current));
            dict.add(next);
            current = std::string(1, c);
        }
    }
    if (!current.empty()) {
        compressedOutput.push_back(dict.getCode(current));
    }

    std::cout << "[RESULT] Compressed Codes: ";
    for (int code : compressedOutput) {
        std::cout << code << " ";
    }
    std::cout << "\n[SUCCESS] Sequence converted to dictionary codes." << std::endl;

    return 0;
}