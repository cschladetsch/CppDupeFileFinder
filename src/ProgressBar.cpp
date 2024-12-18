#include "ProgressBar.h"
#include <iostream>
#include <iomanip>

ProgressBar::ProgressBar(unsigned int total, const std::string& taskDescription)
    : total(total), current(0), taskDescription(taskDescription) {
    display();
}

void ProgressBar::update(unsigned int progress) {
    current = progress;
    display();
}

void ProgressBar::complete() {
    current = total;
    display();
    std::cout << std::endl;
}

void ProgressBar::display() const {
    const int barWidth = 70;
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);

    std::cout << taskDescription << " [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (progress * 100.0) << " %\r";
    std::cout.flush();
}

