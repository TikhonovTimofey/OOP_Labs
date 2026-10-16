#include "FrequencyCounter.h"
#include <string>
#include "FileManager.h"
#include <iostream>

int main(int argc, char** argv){

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    FileManager file(argv[1], FileManager::Mode::READ);
    FileManager out(argv[2], FileManager::Mode::WRITE);

    auto fc = FrequencyCounter(&file);
    std::map <std::string, int> freq = fc.calculateFrequencies();
    std::multimap<int, std::string> ans = FrequencyCounter::SortFrequencies(freq);
    out.csvWrite("Слово,Частота\n", ans);

}
