
#ifndef ANALYSIS_ENGINE_H
#define ANALYSIS_ENGINE_H

#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

class AnalysisEngine {
public:
    static double calculateEntropy(const std::vector<char>& data) {
        if (data.empty()) return 0.0;
        std::vector<int> freq(256, 0);
        for (char c : data) freq[static_cast<unsigned char>(c)]++;

        double entropy = 0.0;
        for (int f : freq) {
            if (f > 0) {
                double p = static_cast<double>(f) / data.size();
                entropy -= p * (log2(p));
            }
        }
        return entropy;
    }

    static std::string getEfficiencyRecommendation(double entropy) {
        if (entropy < 3.0) return "High Yield (Expect >70% savings)";
        if (entropy < 6.0) return "Moderate Yield (Expect 30-50% savings)";
        return "Low Yield (Encrypted or Random Data)";
    }

    static void displayComparisonTable(size_t original, size_t lossless, size_t lossy, double lossPercent) {
        std::cout << "\n========================================================" << std::endl;
        std::cout << "          LOSSLESS VS. LOSSY COMPARISON REPORT          " << std::endl;
        std::cout << "========================================================" << std::endl;
        std::cout << std::left << std::setw(22) << "Metric" 
                  << std::setw(18) << "LZW (Lossless)" 
                  << std::setw(18) << "Quantized (Lossy)" << std::endl;
        std::cout << "--------------------------------------------------------" << std::endl;

        // Row 1: Size
        std::cout << std::left << std::setw(22) << "Compressed Size" 
                  << std::setw(18) << (std::to_string(lossless) + " B") 
                  << std::setw(18) << (std::to_string(lossy) + " B") << std::endl;

        // Row 2: Ratio
        double losslessRatio = (static_cast<double>(lossless) / original) * 100.0;
        double lossyRatio = (static_cast<double>(lossy) / original) * 100.0;
        std::cout << std::left << std::setw(22) << "Compression Ratio" 
                  << std::fixed << std::setprecision(1)
                  << std::setw(18) << (std::to_string(losslessRatio).substr(0, 4) + "%") 
                  << std::setw(18) << (std::to_string(lossyRatio).substr(0, 4) + "%") << std::endl;

        // Row 3: Integrity
        std::cout << std::left << std::setw(22) << "Data Integrity" 
                  << std::setw(18) << "100% (Exact)" 
                  << std::setw(18) << (std::to_string(100.0 - lossPercent).substr(0, 4) + "%") << std::endl;

        // Row 4: Recommendation
        std::cout << std::left << std::setw(22) << "Best Use-case" 
                  << std::setw(18) << "Archiving" 
                  << std::setw(18) << "Fast Preview" << std::endl;
        std::cout << "========================================================\n" << std::endl;
    }
};

#endif













/*#ifndef ANALYSIS_ENGINE_H
#define ANALYSIS_ENGINE_H

#include <vector>
#include <map>
#include <cmath>
#include <string>

class AnalysisEngine {
public:
    static double calculateEntropy(const std::vector<char>& data) {
        if (data.empty()) return 0.0;
        
        std::map<unsigned char, int> frequencies;
        for (char c : data) {
            frequencies[static_cast<unsigned char>(c)]++;
        }

        double entropy = 0.0;
        double size = static_cast<double>(data.size());

        for (auto const& [val, count] : frequencies) {
            double p = count / size;
            entropy -= p * std::log2(p);
        }
        return entropy;
    }

    static std::string getEfficiencyRecommendation(double entropy) {
        if (entropy < 3.0) return "High (Excellent patterns detected)";
        if (entropy < 5.0) return "Moderate (Standard text file)";
        return "Low (File is likely already compressed or encrypted)";
    }
};

#endif
*/

