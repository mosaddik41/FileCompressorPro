#ifndef LOSSY_ENGINE_H
#define LOSSY_ENGINE_H

#include <vector>
#include <string>
#include <cstdint>

class LossyEngine {
public:
    static std::vector<char> compressLossy(const std::vector<char>& input);
    
    static double calculateDataLoss(const std::vector<char>& original, const std::vector<char>& lossy);
};

#endif