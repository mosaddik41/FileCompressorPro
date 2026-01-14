#include "../include/Logger.h"
#include <iostream>
#include <iomanip>

Logger::Logger(const std::string& filename) : logFileName(filename) {
    logFile.open(logFileName, std::ios::app); 
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));
    return std::string(buf);
}

void Logger::logInfo(const std::string& message) {
    if (logFile.is_open()) {
        logFile << "[" << getTimestamp() << "] [INFO] " << message << std::endl;
    }
}

void Logger::logCompressionEvent(size_t original, size_t compressed, double ratio) {
    if (logFile.is_open()) {
        logFile << "[" << getTimestamp() << "] [COMPRESS] Original: " << original 
                << "B, Compressed: " << compressed << "B, Ratio: " 
                << std::fixed << std::setprecision(2) << ratio << "%" << std::endl;
    }
}

void Logger::logError(const std::string& errorMsg) {
    if (logFile.is_open()) {
        logFile << "[" << getTimestamp() << "] [ERROR] " << errorMsg << std::endl;
    }
}

void Logger::showRecentHistory() {
    std::ifstream readLog(logFileName);
    std::string line;
    std::vector<std::string> lines;
    
    while (std::getline(readLog, line)) {
        lines.push_back(line);
    }
    
    std::cout << "\n--- RECENT SESSION HISTORY ---\n";
    size_t start = (lines.size() > 5) ? lines.size() - 5 : 0;
    for (size_t i = start; i < lines.size(); ++i) {
        std::cout << lines[i] << std::endl;
    }
}