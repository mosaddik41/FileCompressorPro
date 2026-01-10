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

void LZWDictionary::add(const std::string& sequence) {
    if (nextCode < MAX_DICT_SIZE) {
        compressDict[sequence] = nextCode;
        decompressDict[nextCode] = sequence;
        nextCode++;
    }
}

int LZWDictionary::getCode(const std::string& sequence) {
    return compressDict[sequence];
}

std::string LZWDictionary::getSequence(int code) {
    return decompressDict[code];
}