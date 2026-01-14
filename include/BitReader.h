

#ifndef BIT_READER_H
#define BIT_READER_H

#include <vector>
#include <cstdint>

class BitReader {
private:
    std::vector<uint8_t> data;
    size_t byteIndex;
    uint32_t bitBuffer;
    int bitsAvailable;

public:
    BitReader(const std::vector<uint8_t>& inputData);

    
    int read12Bits();
};

#endif