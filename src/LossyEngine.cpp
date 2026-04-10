#include "../include/LossyEngine.h"
#include <cmath>

std::vector<char> LossyEngine::compressLossy(const std::vector<char>& input) {
    std::vector<char> output;
    for (char c : input) {
        
        char lossyChar = c & 0xF8; 
        output.push_back(lossyChar);
    }
    return output;
}

double LossyEngine::calculateDataLoss(const std::vector<char>& original, const std::vector<char>& lossy) {
    if (original.size() != lossy.size()) return 100.0;
    
    int differences = 0;
    for (size_t i = 0; i < original.size(); ++i) {
        if (original[i] != lossy[i]) differences++;
    }
    return (static_cast<double>(differences) / original.size()) * 100.0;
}