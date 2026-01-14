#ifndef DICT_MONITOR_H
#define DICT_MONITOR_H

#include <iostream>
#include <vector>



class DictMonitor {
private:
    size_t totalBytesProcessed;
    size_t totalCodesGenerated;
    int dictionaryResets;

public:
    DictMonitor() : totalBytesProcessed(0), totalCodesGenerated(0), dictionaryResets(0) {}

    void recordStep(size_t inputBatch, size_t outputCodes) {
        totalBytesProcessed += inputBatch;
        totalCodesGenerated += outputCodes;
    }

    bool shouldReset(int currentDictSize) {

        if (currentDictSize >= 4096) {
            double ratio = static_cast<double>(totalCodesGenerated * 1.5) / totalBytesProcessed;
            return ratio > 0.9; 
        }
        return false;
    }

    void logReset() {
        dictionaryResets++;
        std::cout << "\n[MONITOR] Dictionary full & efficiency dropping. Performing Reset #" 
                  << dictionaryResets << std::endl;
    }
};

#endif