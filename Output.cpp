#include "Output.h"

#include <iostream>
#include <fstream>
#include "IOutputStream.h"

void Output::RemoveFile() {
    const char *filep = filepath.c_str();
    std::remove(filep);
}

Output::Output(std::string _filepath) : filepath(_filepath) {
    fout.open(filepath, std::ios::binary);
    if (!fout.is_open()) {
        std::cout << "can't open or create file" << filepath << std::endl;
        fout.close();
    }
}

Output::Output(const Output & output){
    filepath = output.filepath;
    fout.open(output.filepath, std::ios::binary);
    size = output.size;

    if (!fout.is_open()) {
        std::cout << "file " << filepath << " cant be open" << std::endl;
        fout.close();
    }
}

void Output::Write(byte value) {
    char buff = (char)value;
    fout.write(&buff, sizeof(char));
    ++size;
}

size_t Output::GetFileSize() {
    fout.seekp(0, std::ios::end);
    long size_file = fout.tellp();
    return size_file;
}

Output::~Output() {
    fout.close();
}


std::string Output::GetFilePath(){
    return filepath;
}

