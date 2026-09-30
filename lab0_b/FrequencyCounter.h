#ifndef LAB0_B_FREQUENCYCOUNTER_H
#define LAB0_B_FREQUENCYCOUNTER_H
#include "FileManager.h"
#include <map>
#include <string>


class FrequencyCounter {
public:
    explicit FrequencyCounter(FileManager* f);
    std::multimap<int, std::string> calculateFrequencies();
private:
    FileManager *file;

};

#endif //LAB0_B_FREQUENCYCOUNTER_H
