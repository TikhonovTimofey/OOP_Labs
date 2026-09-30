#include "FileManager.h"
#include <iostream>


FileManager::FileManager(char* name, char mode) {
    filename = name;
    m = mode;
    if (mode == 'r') {
        in.open(name);
        if (!in.is_open()) {
            std::cout << "Error opening input file: " << filename << "\n";
        }
    }
    else if (mode == 'w') {
        out.open(name);
        if (!out.is_open()) {
            std::cout << "Error opening output file: " << filename << "\n";
        }
    }
}


FileManager::~FileManager() {
    if (m == 'r') {
        in.close();
    }
    else if (m == 'w') {
        out.close();
    }
}


std::ifstream& FileManager::getStream() {
    return in;
}


void FileManager::csvWrite(std::multimap<int, std::string> ans) {
    out << "Слово,Частота\n";
    for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
        out << it->second << "," << it->first<< "\n";
    }
}
