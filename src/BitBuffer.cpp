#include "../include/BitBuffer.h"

BitBuffer::BitBuffer() : currentBits(0), bitCount(0) {}

void BitBuffer::write12Bits(uint16_t code) {
    code &= 0x0FFF;

    currentBits = (currentBits << 12) | code;
    bitCount += 12;

    while (bitCount >= 8) {
        uint8_t byte = (currentBits >> (bitCount - 8)) & 0xFF;
        buffer.push_back(byte);
        bitCount -= 8;
    }
}

void BitBuffer::flush() {
    if (bitCount > 0) {
        uint8_t byte = (currentBits << (8 - bitCount)) & 0xFF;
        buffer.push_back(byte);
    }
    currentBits = 0;
    bitCount = 0;
}

const std::vector<uint8_t>& BitBuffer::getPackedData() const {
    return buffer;
}

void BitBuffer::clear() {
    buffer.clear();
    currentBits = 0;
    bitCount = 0;
}