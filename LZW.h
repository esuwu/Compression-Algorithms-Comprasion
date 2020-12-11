#ifndef PROTOTIPE_LZW_H
#define PROTOTIPE_LZW_H

#include "Algorithm.h"
#include "CodeReader.h"
#include "CodeWriter.h"
#include "EncoderDictionary.h"
#include <map>
#include <cmath>
#include <iterator>
#include <limits>


typedef unsigned char byte;

class LZW : public Algorithm {
public:
    LZW(std::vector<std::string> choosen_formats = {""});
    ~LZW() = default;
    bool ShouldChoose(std::string type_file);
    std::string GetName() override;
private:
    std::size_t GetRequiredBits(unsigned long int n);
    void Encode(IInputStream& original, IOutputStream& compressed) override;
    void Decode(IInputStream& compressed, IOutputStream& original) override;
    void InternalCompress(std::istream &is, std::ostream &os);
    void InternalDecompress(std::istream &is, std::ostream &os);
    std::vector<std::string> Formats;


};

#endif //PROTOTIPE_LZW_H
