//
// Created by alexandr on 11/24/19.
//

#ifndef PROTOTIPE_IINPUTSTREAM_H
#define PROTOTIPE_IINPUTSTREAM_H
typedef unsigned char byte;

#include <string>

class IInputStream {
public:
    virtual size_t GetFileSize() = 0;
    virtual bool Read(byte& value) = 0;
    virtual std::string GetFilePath() = 0;
};


#endif //PROTOTIPE_IINPUTSTREAM_H
