
#include "EncoderDictionary.h"

EncoderDictionary::EncoderDictionary() {
    const long int minc = std::numeric_limits<char>::min();
    const long int maxc = std::numeric_limits<char>::max();
    CodeType k {0};

    for (long int c = minc; c <= maxc; ++c)
        initials[static_cast<unsigned char> (c)] = k++;

    vn.reserve(globals::dms);
    Reset();
}

void EncoderDictionary::Reset() {
    vn.clear();

    const long int minc = std::numeric_limits<char>::min();
    const long int maxc = std::numeric_limits<char>::max();

    for (long int c = minc; c <= maxc; ++c)
        vn.push_back(NodeForLZW(c));

    vn.push_back(NodeForLZW('\x00')); // MetaCode::Eof
}


CodeType EncoderDictionary::SearchAndInsert(CodeType i, char c) {
    if (i == globals::dms)
        return SearchInitials(c);

    const CodeType vn_size = vn.size();
    CodeType ci {vn[i].first}; // Current Index

    if (ci != globals::dms)
    {
        while (true)
            if (c < vn[ci].c)
            {
                if (vn[ci].left == globals::dms)
                {
                    vn[ci].left = vn_size;
                    break;
                }
                else
                    ci = vn[ci].left;
            }
            else
            if (c > vn[ci].c)
            {
                if (vn[ci].right == globals::dms)
                {
                    vn[ci].right = vn_size;
                    break;
                }
                else
                    ci = vn[ci].right;
            }
            else // c == vn[ci].c
                return ci;
    }
    else
        vn[i].first = vn_size;

    vn.push_back(NodeForLZW(c));
    return globals::dms;
}


CodeType EncoderDictionary::SearchInitials(char c) const
{
    return initials[static_cast<unsigned char> (c)];
}

std::vector<NodeForLZW>::size_type EncoderDictionary::Size() const
{
    return vn.size();
}