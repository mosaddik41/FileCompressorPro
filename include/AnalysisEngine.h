#ifndef ANALYSIS_ENGINE_H
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