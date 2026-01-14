#include "../include/LZWDecompressor.h"
#include <iostream>



LZWDecompressor::LZWDecompressor() {
    dictionary.reset();
}


std::vector<char> LZWDecompressor::decompress(const std::vector<uint8_t>& compressedData) {

     dictionary.reset();
    

     BitReader reader(compressedData);
    

     std::vector<char> outputBuffer;


     int currentCode = reader.read12Bits();
    

     if (currentCode == -1) {
        return outputBuffer;
    }


    std::string previousSequence = dictionary.getSequence(currentCode);
    
    for (char c : previousSequence) {
        outputBuffer.push_back(c);
    }

    while (true) {
        currentCode = reader.read12Bits();
        
        if (currentCode == -1) {
            break;
        }

        std::string currentEntry = "";


        if (dictionary.containsSequenceForCode(currentCode)) {
            currentEntry = dictionary.getSequence(currentCode);
        } 
        else {
            
            currentEntry = previousSequence + previousSequence[0];
        }

        for (char character : currentEntry) {
            outputBuffer.push_back(character);
        }

        
        std::string newPattern = previousSequence + currentEntry[0];
        dictionary.add(newPattern);
        
        previousSequence = currentEntry;
    }

    return outputBuffer;
}