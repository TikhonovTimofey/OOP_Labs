#include "FrequencyCounter.h"
#include <fstream>
#include <iostream>

FrequencyCounter::FrequencyCounter(char* argv) {
    filename = argv;
}

std::multimap<int, std::string> FrequencyCounter::calculateFrequencies() {
    std::ifstream in(filename);

    if (!in.is_open()) {
        std::cout << "Error opening input file: " << filename << "\n";
        return {};
    }

    std::string line;
    std::map <std::string, int> frequencies;
    std::string word;
    std::multimap <int, std::string> ans;
    unsigned char previous = '.';
    while (std::getline(in, line)) {
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
    in.close();

    for (const auto& pair : frequencies) {
        ans.insert({pair.second, pair.first});
    }
    return ans;
}
