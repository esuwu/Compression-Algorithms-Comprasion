
#include "CodeWriter.h"

CodeWriter::CodeWriter(std::ostream &os): os(os), bits(CHAR_BIT + 1) {
}

CodeWriter::~CodeWriter() {
    Write(static_cast<CodeType> (MetaCode::Eof));

    // write the incomplete leftover byte as-is
    if (lo.used != 0)
        os.put(static_cast<char> (lo.data));
}


std::size_t CodeWriter::GetBits() const {
    return bits;
}
void CodeWriter::ResetBits() {
    bits = CHAR_BIT + 1;
}


void CodeWriter::IncreaseBits() {

    ++bits;
}

bool CodeWriter::Write(CodeType k) {
    std::size_t remaining_bits {bits};

    if (lo.used != 0)
    {
        lo.data |= k << lo.used;
        os.put(static_cast<char> (lo.data));
        k >>= CHAR_BIT - lo.used;
        remaining_bits -= CHAR_BIT - lo.used;
        lo.used = 0;
        lo.data = 0x00;
    }

    while (remaining_bits != 0)
        if (remaining_bits >= CHAR_BIT)
        {
            os.put(static_cast<char> (k));
            k >>= CHAR_BIT;
            remaining_bits -= CHAR_BIT;
        }
        else
        {
            lo.used = remaining_bits;
            lo.data = k;
            break;
        }

    return true;
}