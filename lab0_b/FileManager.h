#ifndef LAB0_B_FILEMANAGER_H
#define LAB0_B_FILEMANAGER_H
#include <fstream>
#include <map>



class FileManager {
    public:
        explicit FileManager(char* name, char mode);
        ~FileManager();
    std::ifstream& getStream();
    void csvWrite(std::multimap<int, std::string>);
    private:
        std::string filename;
        std::ifstream in;
        std::ofstream out;
        char m;


};


#endif //LAB0_B_FILEMANAGER_H
