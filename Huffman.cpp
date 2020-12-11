#include "Huffman.h"

using namespace std;

Huffman::Huffman(std::vector<std::string> choosen_formats): cellSize(8), cellSizeBinary(256) {
    vector<string> new_formats = {"txt", "rtf", "doc", "docx", "html", "pdf", "odt"};
    Formats = new_formats;
    if(choosen_formats.size() != 0){
        if(choosen_formats[0] != ""){
            for(auto &it : choosen_formats){
                Formats.push_back(it);
            }
        }
    }
}

bool Huffman::ShouldChoose(string type_file) {

    auto it = find(Formats.begin(), Formats.end(), type_file);
    if(it != Formats.end()) {
        return true;
    }
    return false;
}



void Huffman::buildTable(shared_ptr<Node> root, vector<bool> &bits, map <char, vector<bool> > &code) {
    if (!root) return;

    if (!root->left && !root->right) {
        code[root->c] = bits;
    }

    if (root->left) {
        bits.push_back(0);
        buildTable(root->left, bits, code);
    }

    if (root->right) {
        bits.push_back(1);
        buildTable(root->right, bits, code);
    }
    bits.pop_back();
}

void Huffman::WriteTree(shared_ptr<Node> root, IOutputStream& compressed) {
    if (!root){
        return;
    }
    WriteTree(root->left, compressed);
    WriteTree(root->right, compressed);
    if (!root->left && !root->right) {
        compressed.Write('1');
        compressed.Write(root->c);
    } else {
        compressed.Write('0');
    }
}
shared_ptr<Node> Huffman::ReadTree(IInputStream& compressed) {
    unsigned char charSize;
    int intSize;
    compressed.Read(charSize);
    intSize = (unsigned char)charSize;
    compressed.Read(charSize);
    intSize += (int)((unsigned char)charSize) << cellSize;

    stack<shared_ptr<Node>> s;
    int currSize = 0;
    unsigned char c;

    while (currSize < intSize|| s.size() > 1) {
        compressed.Read(c);
        if (c == '1') {
            compressed.Read(c);
            ++currSize;
            shared_ptr<Node> newNode(new Node(c));
            s.push(newNode);
        } else if (c == '0'){
            shared_ptr<Node> node1 = s.top();
            s.pop();
            shared_ptr<Node> node2 = s.top();
            s.pop();

            shared_ptr<Node> newNode(new Node(node2, node1));
            s.push(newNode);
        }
    }
    shared_ptr<Node> root = nullptr;
    if (!s.empty()) root = s.top();
    s.pop();
    return root;
}

void Huffman::Encode(IInputStream& original, IOutputStream& compressed){
    map<char, int> freqs;
    string file;
    size_t strPtr = 0;
    unsigned char c;

    // подсчёт
    while (original.Read(c)) {
        ++freqs[c];
        file += c;
    }

    // составление списка
    std::list<shared_ptr<Node>> l;
    for(auto it : freqs){
        shared_ptr<Node> node(new Node(it.first, it.second, 0, 0));
        l.push_back(node);
    }

    // построение дерева
    if (l.size() == 0) return;
    while(l.size() != 1) {
        l.sort(nodeComparator());
        shared_ptr<Node> left = l.front();
        l.pop_front();

        shared_ptr<Node> right = l.front();
        l.pop_front();
        shared_ptr<Node> parent(new Node(0, left->freq + right->freq, left, right));
        l.push_back(parent);
    }


    shared_ptr<Node> root = l.front();

    //построение кода Хаффмана
    vector<bool> bits;
    map<char, vector<bool> > code;
    buildTable(root, bits, code);

    //запись в файл
    int count = 0;
    unsigned char  buf = 0;


    size_t fileSize = file.size();
    for (int i = 0; i < cellSize; ++i) {
        unsigned char ch = (fileSize >> (i * cellSize));
        compressed.Write(ch);
    }

    int size = code.size();
    compressed.Write(size);
    compressed.Write(size >> cellSize);

    WriteTree(root, compressed);

    /*Записываем закодированные  в файл*/
    while (strPtr < file.size()) {
        c = file[strPtr];
        ++strPtr;
        vector<bool> x = code[c];
        for (int n = 0; n < x.size(); ++n) {
            buf = buf | (x[n] << ((cellSize - 1) - count));
            ++count;
            if (count == cellSize) {
                count = 0;
                compressed.Write(buf);

                buf = 0;
            }
        }
    }

    compressed.Write(buf);

}

void Huffman::Decode( IInputStream& compressed, IOutputStream& original ){
    size_t fileSize = 0;
    size_t filePtr = 0;
    for (int k = 0; k < 8; ++k) {
        unsigned char ch;
        compressed.Read(ch);
        if (ch > 0) {fileSize += pow(cellSizeBinary, k) * ch;}
        else if (ch < 0) fileSize += pow(cellSizeBinary, k) * (pow(2, cellSize) + ch);
    }



    shared_ptr<Node> root = ReadTree(compressed);
    shared_ptr<Node> node = root;
    if (!root) return;

    //построение кода Хаффмана
    vector<bool> bits;
    map<char, vector<bool> > code;
    buildTable(root, bits, code);


    int count = 0;
    unsigned char c;
    char buf;
    compressed.Read(c);

    while(filePtr < fileSize) {
        bool b = c & (1 << ((cellSize -1) - count++) );
        if (b) node = node->right;
        else node = node->left;
        if (!node){
            break;
        }
        if (!node->left && !node->right) {
            original.Write(node->c);
            buf = node->c;
            ++filePtr;
            node = root;
        }
        if (count == cellSize) {
            count = 0;
            compressed.Read(c);
        }
    }

}

string Huffman::GetName(){
    return "Huffman";
}