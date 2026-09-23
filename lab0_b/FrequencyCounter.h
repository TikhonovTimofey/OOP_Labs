#ifndef LAB0_B_FREQUENCYCOUNTER_H
#define LAB0_B_FREQUENCYCOUNTER_H
#include <map>
#include <string>
class FrequencyCounter {
public:
    explicit FrequencyCounter(char* argv);
    std::multimap<int, std::string> calculateFrequencies();
private:
    std::string filename;
};

#endif //LAB0_B_FREQUENCYCOUNTER_H
