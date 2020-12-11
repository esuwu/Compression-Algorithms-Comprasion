#include "CodeReader.h"

CodeReader::CodeReader(std::istream &is): is(is), bits(CHAR_BIT + 1), feofmc(false) {
}

std::size_t CodeReader::GetBits() const {
    return bits;
}

void CodeReader::ResetBits() {
    bits = CHAR_BIT + 1;
}

void CodeReader::IncreaseBits() {
    ++bits;
}

bool CodeReader::Read(CodeType &k) {
    static const std::array<unsigned long int, 9> masks {
            {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF}
    };

    std::size_t remaining_bits {bits};
    std::size_t offset {lo.used};
    unsigned char temp;

    k = lo.data;
    remaining_bits -= lo.used;
    lo.used = 0;
    lo.data = 0x00;

    while (remaining_bits != 0 && is.get(reinterpret_cast<char &> (temp)))
        if (remaining_bits >= CHAR_BIT)
        {
            k |= static_cast<CodeType> (temp) << offset;
            offset += CHAR_BIT;
            remaining_bits -= CHAR_BIT;
        }
        else
        {
            k |= static_cast<CodeType> (temp & masks[remaining_bits]) << offset;
            lo.used = CHAR_BIT - remaining_bits;
            lo.data = temp >> remaining_bits;
            break;
        }

    if (k == static_cast<CodeType> (MetaCode::Eof))
    {
        feofmc = true;
        return false;
    }

    return true;
}

bool CodeReader::Corrupted() const
{
    return !feofmc;
}