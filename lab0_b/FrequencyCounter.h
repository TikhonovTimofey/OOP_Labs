#ifndef LAB0_B_FREQUENCYCOUNTER_H
#define LAB0_B_FREQUENCYCOUNTER_H
#include "FileManager.h"
#include <map>
#include <string>


class FrequencyCounter {
public:
    explicit FrequencyCounter(FileManager* f);
    std::map <std::string, int>  calculateFrequencies();
    static std::multimap<int, std::string> SortFrequencies(const std::map <std::string, int> &frequencies);
private:
    FileManager *file;

};

#endif //LAB0_B_FREQUENCYCOUNTER_H
