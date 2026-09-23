#include <fstream>
#include "FrequencyCounter.h"
#include <string>

int main(int argc, char** argv){
    std::ofstream out(argv[2]);
    FrequencyCounter fc = FrequencyCounter(argv[1]);
    std::multimap<int, std::string> ans = fc.calculateFrequencies();

    out << "Слово,Частота\n";
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
        out << it->second << "," << it->first<< "\n";
    }
    out.close();
}
