#ifndef PROTOTIPE_ENCODERDICTIONARY_H
#define PROTOTIPE_ENCODERDICTIONARY_H

#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <limits>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using CodeType = std::uint32_t;

namespace globals {

    const CodeType dms {512 * 1024};

}


enum class MetaCode: CodeType {
    Eof = 1u << CHAR_BIT,
};

struct NodeForLZW {
    explicit NodeForLZW(char c): first(globals::dms), c(c), left(globals::dms), right(globals::dms) {
    }

    CodeType    first;
    char        c;
    CodeType    left;
    CodeType    right;
};

class EncoderDictionary {

public:
    EncoderDictionary();
    void Reset();
    CodeType SearchAndInsert(CodeType i, char c);
    CodeType SearchInitials(char c) const;
    std::vector<NodeForLZW>::size_type Size() const;

private:

    std::vector<NodeForLZW> vn;
    std::array<CodeType, 1u << CHAR_BIT> initials;

};


#endif //PROTOTIPE_ENCODERDICTIONARY_H
