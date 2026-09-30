#include "FrequencyCounter.h"
#include <string>
#include "FileManager.h"

int main(int argc, char** argv){

    FileManager file(argv[1], 'r');
    FileManager out(argv[2], 'w');

    auto fc = FrequencyCounter(&file);
    std::multimap<int, std::string> ans = fc.calculateFrequencies();
    out.csvWrite(ans);

}
