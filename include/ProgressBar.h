#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <string>

class ProgressBar {
public:
    ProgressBar(unsigned int total, const std::string& taskDescription);
    void update(unsigned int progress);
    void complete();

private:
    unsigned int total;
    unsigned int current;
    std::string taskDescription;
    void display() const;
};

#endif // PROGRESSBAR_H

