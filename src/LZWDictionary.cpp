#include "../include/LZWDictionary.h"

LZWDictionary::LZWDictionary() {
    reset();
}

void LZWDictionary::reset() {
    compressDict.clear();
    decompressDict.clear();
    
    for (int i = 0; i < 256; i++) {
        std::string s(1, (char)i);
        compressDict[s] = i;
        decompressDict[i] = s;
    }
    
    nextCode = 256;
}

bool LZWDictionary::contains(const std::string& sequence) {
    return compressDict.find(sequence) != compressDict.end();
}

bool LZWDictionary::containsSequenceForCode(int code) {
    return decompressDict.find(code) != decompressDict.end();
}

void LZWDictionary::add(const std::string& sequence) {
    if (nextCode < MAX_DICT_SIZE) {
        compressDict[sequence] = nextCode;
        decompressDict[nextCode] = sequence;
        nextCode++;
    }
}

int LZWDictionary::getCode(const std::string& sequence) {
    if (contains(sequence)) {
        return compressDict[sequence];
    }
    return -1; 
}

std::string LZWDictionary::getSequence(int code) {
    if (containsSequenceForCode(code)) {
        return decompressDict[code];
    }
    return ""; 



}