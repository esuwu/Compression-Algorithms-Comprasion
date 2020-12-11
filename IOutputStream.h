//
// Created by alexandr on 11/24/19.
//

#ifndef PROTOTIPE_IOUTPUTSTREAM_H
#define PROTOTIPE_IOUTPUTSTREAM_H

#include <string>

class IOutputStream {
public:
    virtual void Write(unsigned char value) = 0;
    virtual std::string GetFilePath() = 0;
    virtual size_t GetFileSize() = 0;
};


#endif //PROTOTIPE_IOUTPUTSTREAM_H
