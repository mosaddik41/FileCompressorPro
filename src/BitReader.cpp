#include "../include/BitReader.h"

BitReader::BitReader(const std::vector<uint8_t>& inputData) 
    : data(inputData), byteIndex(0), bitBuffer(0), bitsAvailable(0) {}

int BitReader::read12Bits() {
    while (bitsAvailable < 12 && byteIndex < data.size()) {
        bitBuffer = (bitBuffer << 8) | data[byteIndex++];
        bitsAvailable += 8;
    }

    if (bitsAvailable < 12) return -1; // End of data

    int code = (bitBuffer >> (bitsAvailable - 12)) & 0xFFF;
    bitsAvailable -= 12;
    
    bitBuffer &= (1 << bitsAvailable) - 1;

    return code;
}