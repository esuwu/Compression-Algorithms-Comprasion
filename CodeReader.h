//
// Created by alexandr on 12/21/19.
//

#ifndef PROTOTIPE_CODEREADER_H
#define PROTOTIPE_CODEREADER_H

#include "EncoderDictionary.h"
#include "CodeWriter.h"


class CodeReader {
public:

    explicit CodeReader(std::istream &is);
    std::size_t GetBits() const;
    void ResetBits();
    void IncreaseBits();
    bool Read(CodeType &k);
    bool Corrupted() const;
private:

    std::istream    &is;
    std::size_t     bits;
    bool            feofmc;
    ByteCache       lo;
};


#endif //PROTOTIPE_CODEREADER_H
