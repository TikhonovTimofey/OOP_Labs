#include "FrequencyCounter.h"
#include <fstream>
#include <iostream>

FrequencyCounter::FrequencyCounter(FileManager *f) : file(f){
}

std::map <std::string, int> FrequencyCounter::calculateFrequencies() {
    std::map <std::string, int> frequencies;
    std::string word;
    std::string line;
    while (std::getline(file->getStream(), line)) {
        for (char c: line) {
            if (isalnum(c)) {
                word += c;
            }
            else if (!word.empty()) {
                frequencies[word] += 1;
                word.clear();
            }
        }
        if (!word.empty()) {
            frequencies[word] += 1;
            word.clear();
        }
    }
    return frequencies;
}

std::multimap<int, std::string> FrequencyCounter::SortFrequencies(const std::map <std::string, int> &frequencies) {
    std::multimap <int, std::string> ans;
    for (const auto& pair : frequencies) {
        ans.insert({pair.second, pair.first});
    }
    return ans;
}
