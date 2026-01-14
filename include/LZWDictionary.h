#ifndef LZW_DICTIONARY_H
#define LZW_DICTIONARY_H

#include <unordered_map>
#include <map>
#include <string>
#include <vector>


class LZWDictionary {
private:
    std::unordered_map<std::string, int> compressDict;
    
    std::map<int, std::string> decompressDict;
    
    int nextCode;
    
    const int MAX_DICT_SIZE = 4096;

public:
    LZWDictionary();
    
    void reset();

    
    bool contains(const std::string& sequence);
    
    bool containsSequenceForCode(int code);
    
    void add(const std::string& sequence);
    
    int getCode(const std::string& sequence);
    
    std::string getSequence(int code);




};



#endif