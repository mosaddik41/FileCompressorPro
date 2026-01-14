#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <iostream>
#include <string>


class ProgressBar {
private:
    int totalSteps;
    int currentStep;
    int width;

public:
    ProgressBar(int total, int barWidth = 40) 
        : totalSteps(total), currentStep(0), width(barWidth) {}

    void update(int progress) {
        currentStep = progress;
        float ratio = (float)currentStep / totalSteps;
        int pos = width * ratio;

        std::cout << "[";
        for (int i = 0; i < width; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(ratio * 100.0) << " %\r";
        std::cout.flush();
    }

    void finish() {
        update(totalSteps);
        std::cout << std::endl;
    }
};

#endif