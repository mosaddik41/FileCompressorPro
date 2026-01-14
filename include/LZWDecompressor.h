#ifndef LZW_DECOMPRESSOR_H
#define LZW_DECOMPRESSOR_H

#include <vector>
#include <string>
#include <cstdint>
#include "LZWDictionary.h"
#include "BitReader.h"


class LZWDecompressor {
private:

LZWDictionary dictionary;

public:
    

    LZWDecompressor();

    
    std::vector<char> decompress(const std::vector<uint8_t>& compressedData);
};

#endif 