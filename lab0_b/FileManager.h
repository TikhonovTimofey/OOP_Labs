#ifndef LAB0_B_FILEMANAGER_H
#define LAB0_B_FILEMANAGER_H
#include <fstream>
#include <map>



class FileManager {
    public:
        FileManager(const FileManager&) = delete;
        FileManager& operator=(const FileManager&) = delete;
        FileManager(FileManager&&) = delete;
        FileManager& operator=(FileManager&&) = delete;

        enum class Mode {READ, WRITE};
        explicit FileManager(char* name, Mode mode);
        ~FileManager();
        std::ifstream& getStream();
        void csvWrite(const std::string& header, std::multimap<int, std::string>);
    private:
        std::string filename;
        std::ifstream in;
        std::ofstream out;
        Mode m;


};


#endif //LAB0_B_FILEMANAGER_H
