

#ifndef BIT_BUFFER_H
#define BIT_BUFFER_H

#include <vector>
#include <cstdint>

class BitBuffer {
private:
    std::vector<uint8_t> buffer; 
    uint32_t currentBits;        
    int bitCount;                

public:
    BitBuffer();

    void write12Bits(uint16_t code);

    void flush();

    const std::vector<uint8_t>& getPackedData() const;

    void clear();
};

#endif