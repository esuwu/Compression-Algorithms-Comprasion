#include "LZW.h"

using namespace std;

LZW::LZW(std::vector<std::string> choosen_formats) {
    Formats = {"png", "tiff", "jpg", "gif", "bmp"};
    if(choosen_formats.size() != 0 ){
        if(choosen_formats[0] != "") {
            for(auto &it : choosen_formats) {
                Formats.push_back(it);
            }
        }
    }

}

void LZW::Encode(IInputStream &original, IOutputStream &compressed) {
    unsigned char value;
    while(original.Read(value)){}

    const std::size_t buffer_size {1024 * 1024};
    const std::unique_ptr<char[]> input_buffer(new char[buffer_size]);
    const std::unique_ptr<char[]> output_buffer(new char[buffer_size]);
    std::ifstream input_file;
    std::ofstream output_file;

    input_file.rdbuf()->pubsetbuf(input_buffer.get(), buffer_size);
    input_file.open(original.GetFilePath(), std::ios_base::binary);

    output_file.rdbuf()->pubsetbuf(output_buffer.get(), buffer_size);
    output_file.open(compressed.GetFilePath(), std::ios_base::binary);

    input_file.exceptions(std::ios_base::badbit);
    output_file.exceptions(std::ios_base::badbit | std::ios_base::failbit);

    InternalCompress(input_file, output_file);
}

void LZW::Decode(IInputStream &compressed, IOutputStream &original) {
    const std::size_t buffer_size {1024 * 1024};
    const std::unique_ptr<char[]> input_buffer(new char[buffer_size]);
    const std::unique_ptr<char[]> output_buffer(new char[buffer_size]);
    std::ifstream input_file;
    std::ofstream output_file;

    input_file.rdbuf()->pubsetbuf(input_buffer.get(), buffer_size);
    input_file.open(compressed.GetFilePath(), std::ios_base::binary);

    output_file.rdbuf()->pubsetbuf(output_buffer.get(), buffer_size);
    output_file.open(original.GetFilePath(), ios_base::out);

    input_file.exceptions(std::ios_base::badbit);
    output_file.exceptions(std::ios_base::badbit | std::ios_base::failbit);

    InternalDecompress(input_file, output_file);
}


bool LZW::ShouldChoose(string type_file) {
    auto it = find(Formats.begin(), Formats.end(), type_file);
    if(it != Formats.end()) {
        return true;
    }
    else {
        return false;
    }
}

string LZW::GetName() {
    return "LZW";
}

std::size_t LZW::GetRequiredBits(unsigned long int n) {
    std::size_t r {1};

    while ((n >>= 1) != 0)
        ++r;

    return r;
}

void LZW::InternalCompress(std::istream &is, std::ostream &os){
    EncoderDictionary ed;
    CodeWriter cw(os);
    CodeType i {globals::dms};
    char c;
    bool rbwf {false};

    while (is.get(c)) {
        if (ed.Size() == globals::dms) {
            ed.Reset();
            rbwf = true;
        }

        const CodeType temp {i};

        if ((i = ed.SearchAndInsert(temp, c)) == globals::dms)
        {
            cw.Write(temp);
            i = ed.SearchInitials(c);

            if (GetRequiredBits(ed.Size() - 1) > cw.GetBits())
                cw.IncreaseBits();
        }

        if (rbwf)
        {
            cw.ResetBits();
            rbwf = false;
        }
    }

    if (i != globals::dms)
        cw.Write(i);
}

void LZW::InternalDecompress(std::istream &is, std::ostream &os){
    std::vector<std::pair<CodeType, char>> dictionary;

    const auto reset_dictionary = [&dictionary] {
        dictionary.clear();
        dictionary.reserve(globals::dms);

        const long int minc = std::numeric_limits<char>::min();
        const long int maxc = std::numeric_limits<char>::max();

        for (long int c = minc; c <= maxc; ++c)
            dictionary.push_back({globals::dms, static_cast<char> (c)});

        dictionary.push_back({0, '\x00'});
    };

    const auto rebuild_string = [&dictionary](CodeType k) -> const std::vector<char> * {
        static std::vector<char> s;

        s.clear();

        s.reserve(globals::dms);

        while (k != globals::dms) {
            s.push_back(dictionary[k].second);
            k = dictionary[k].first;
        }

        std::reverse(s.begin(), s.end());
        return &s;
    };

    reset_dictionary();

    CodeReader cr(is);
    CodeType i {globals::dms};
    CodeType k;

    while (true)
    {
        if (dictionary.size() == globals::dms)
        {
            reset_dictionary();
            cr.ResetBits();
        }

        if (GetRequiredBits(dictionary.size()) > cr.GetBits())
            cr.IncreaseBits();

        if (!cr.Read(k))
            break;

        if (k > dictionary.size())
            throw std::runtime_error("invalid compressed code");

        const std::vector<char> *s; // String

        if (k == dictionary.size())
        {
            dictionary.push_back({i, rebuild_string(i)->front()});
            s = rebuild_string(k);
        }
        else
        {
            s = rebuild_string(k);

            if (i != globals::dms)
                dictionary.push_back({i, s->front()});
        }

        os.write(&s->front(), s->size());
        i = k;
    }

    if (cr.Corrupted())
        throw std::runtime_error("corrupted compressed file");
}





