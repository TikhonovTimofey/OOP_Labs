#include "FrequencyCounter.h"
#include <fstream>
#include <iostream>

FrequencyCounter::FrequencyCounter(FileManager *f) {
    file = f;
}

std::multimap<int, std::string> FrequencyCounter::calculateFrequencies() {
    std::map <std::string, int> frequencies;
    std::multimap <int, std::string> ans;

    unsigned char previous = '.';
    std::string word;
    std::string line;
    while (std::getline(file->getStream(), line)) {
        for (char c: line) {
            if (isalnum(c)) {
                word += c;
            }
            else if (isalnum(previous)) {
                frequencies[word] += 1;
                word.clear();
            }
            previous = c;
        }
        if (!word.empty()) {
            frequencies[word] += 1;
            word.clear();
        }

    }

    for (const auto& pair : frequencies) {
        ans.insert({pair.second, pair.first});
    }
    return ans;
}
