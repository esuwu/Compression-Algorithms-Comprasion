#include <cassert>
#include <iostream>
#include "Input.h"

Input::Input(const std::string _filepath ) : count(0), filepath(_filepath), isFileOpenedSuccesful(true) {
    fin.open(filepath,std::ios::binary);
    if (!fin.is_open()) {
        std::cout << "file " << filepath << " cant be open" << std::endl;
        fin.close();
    }
}

Input::Input(const Input &input){
    filepath = input.filepath;
    fin.open(input.filepath, std::ios::binary);
    count = input.count;

    if (!fin.is_open()) {
        std::cout << "file " << filepath << " cant be open" << std::endl;
        fin.close();
        isFileOpenedSuccesful = false;
    }
}

size_t Input::GetFileSize() {
    return count;
}
void Input::RemoveFile() {
    const char *filep = filepath.c_str();
    std::remove(filep);
}

bool Input::Read(byte& value) {
    char buff;
    if (fin.read(&buff, sizeof(char))) {
        value = (unsigned char)buff;
        ++count;
        return true;
    }
    return false;
}

Input::~Input() {
    fin.close();
}

bool Input::isFileEmpty(){
    (0 == count) ? true : false;
}


std::string Input::GetFilePath(){
    return filepath;
}
