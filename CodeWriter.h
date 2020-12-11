//
// Created by alexandr on 12/21/19.
//

#ifndef PROTOTIPE_CODEWRITER_H
#define PROTOTIPE_CODEWRITER_H

#include "EncoderDictionary.h"

struct ByteCache {

    ByteCache(): used(0), data(0x00) {
    }

    std::size_t     used;
    unsigned char   data;
};

class CodeWriter {
public:

    CodeWriter(std::ostream &os);
    ~CodeWriter();
    std::size_t GetBits() const;
    void ResetBits();
    void IncreaseBits();
    bool Write(CodeType k);
private:

    std::ostream    &os;
    std::size_t     bits;
    ByteCache       lo;

};


#endif //PROTOTIPE_CODEWRITER_H
