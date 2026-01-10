#ifndef LZW_DICTIONARY_H
#define LZW_DICTIONARY_H

#include <unordered_map>
#include <map>
#include <string>
#include <vector>

class LZWDictionary {
private:
    // For Compression: Maps a String to an Integer Code
    std::unordered_map<std::string, int> compressDict;
    
    // For Decompression: Maps an Integer Code back to a String
    std::map<int, std::string> decompressDict;
    
    int nextCode;
    const int MAX_DICT_SIZE = 4096; // 12-bit limit

public:
    LZWDictionary();
    
    // Reset dictionary to initial 256 ASCII characters
    void reset();
    
    // Check if sequence exists
    bool contains(const std::string& sequence);
    
    // Add new sequence to dictionary
    void add(const std::string& sequence);
    
    // Get code for a sequence
    int getCode(const std::string& sequence);
    
    // Get sequence for a code
    std::string getSequence(int code);
};

#endif