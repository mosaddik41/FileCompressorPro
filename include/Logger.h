#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>


class Logger {
private:
    std::string logFileName;
    std::ofstream logFile;
    

    std::string getTimestamp();

public:
    Logger(const std::string& filename = "session_history.log");
    ~Logger();


    void logInfo(const std::string& message);
    

    void logCompressionEvent(size_t original, size_t compressed, double ratio);
    

    void logError(const std::string& errorMsg);

    void showRecentHistory();
};

#endif