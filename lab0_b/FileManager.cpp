#include "FileManager.h"
#include <iostream>


FileManager::FileManager(char* name, Mode mode) : filename(name), m(mode){
    if (mode == Mode::READ) {
        in.open(name);
        if (!in.is_open()) {
            std::cout << "Error opening input file: " << filename << "\n";
        }
    }
    else if (mode == Mode::WRITE) {
        out.open(name);
        if (!out.is_open()) {
            std::cout << "Error opening output file: " << filename << "\n";
        }
    }
    else {
        throw std::invalid_argument("Invalid mode! Use 'r' for reading or 'w' for writing.");
    }
}


FileManager::~FileManager() {
    if (m == Mode::READ) {
        in.close();
    }
    else if (m == Mode::WRITE) {
        out.close();
    }
}


std::ifstream& FileManager::getStream() {
    return in;
}


void FileManager::csvWrite(const std::string& header, std::multimap<int, std::string> ans) {
    out << header;
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
        out << it->second << "," << it->first<< "\n";
    }
}
