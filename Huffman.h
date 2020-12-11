#ifndef PROTOTIPE_HUFFMAN_H
#define PROTOTIPE_HUFFMAN_H

#include "Algorithm.h"
#include <memory>

struct Node {
    unsigned char c;
    int freq;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node() {}
    Node(char c) : c(c), left(), right() {}
    Node (std::shared_ptr<Node> left, std::shared_ptr<Node> right) : c(0), left(left), right(right) {}
    Node(char c, int freq, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : right(right), c(c), left(left), freq(freq) {
    }
    ~Node() {

    }
};

struct nodeComparator {
    bool operator ()(const std::shared_ptr<Node> left, const std::shared_ptr<Node> right) const
    {
        return left->freq < right->freq;
    }
};

class Huffman : public Algorithm {
public:
    Huffman(std::vector<std::string> choosen_formats = {""});
    ~Huffman() = default;
    bool ShouldChoose(std::string type_file) override;
    std::string GetName();
private:
    std::vector<std::string> Formats;
    size_t cellSize;
    size_t cellSizeBinary;
    void buildTable(std::shared_ptr<Node> root, std::vector<bool> & bits, std::map<char, std::vector<bool> >  & code);
    void WriteTree(std::shared_ptr<Node> root, IOutputStream& compressed);
    std::shared_ptr<Node> ReadTree(IInputStream& compressed);
    void Encode(IInputStream& original, IOutputStream& compressed) override;
    void Decode(IInputStream& compressed, IOutputStream& original) override;
};


#endif //PROTOTIPE_HUFFMAN_H
