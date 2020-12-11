#include <gtest/gtest.h>
#include <Huffman.h>
#include <iostream>

using namespace std;

bool IsFilesEqual(string input_filepath, string output_filepath) {
    ifstream fin1(input_filepath, ios::binary);
    ifstream fin2(output_filepath, ios::binary);
    /*Сравниваем файлы побайтово*/
    bool result = true;
    if (fin2 && fin2) {
        char ch1, ch2;
        while (fin1.get(ch1) && fin2.get(ch2)) {
            if (ch1 != ch2) {
                result =  false;
                break;
            }
        }
    }
    else{
        cout << "Error opening file!" << endl;
        result = false;
    }
    return result;
}

TEST(HuffmanTest, TestShouldChoose1){
    Huffman alg_huffman;
    vector<string> types_file = {"txt", "rtf", "doc", "docx", "html", "pdf", "odt"};
    for(auto &it : types_file){
        ASSERT_EQ(true, alg_huffman.ShouldChoose(it));
    }

}

TEST(HuffmanTest, TestShouldChoose2){
    Huffman alg_huffman;
    vector<string> types_file = {"txtttttt"};
    for(auto &it : types_file){
        ASSERT_EQ(false, alg_huffman.ShouldChoose(it));
    }

}

TEST(HuffmanTest, TestGetName1){
    Huffman alg_huffman;
    string name = "Huffman";
        ASSERT_EQ(true, alg_huffman.GetName() == name);

}

TEST(HuffmanTest, TestGetName2){
    Huffman alg_huffman;
    string name = "Huffmannnnnn";
    ASSERT_EQ(false, alg_huffman.GetName() == name);

}



TEST(HuffmanTest, TestCompressDataTxt1) {
    Huffman alg_huffman;
    Input input("../../files_for_compress/test1.txt");
    Output output("../../compressed_files/test1.bin");
    alg_huffman.Compress(input, output);

    ASSERT_EQ(true, alg_huffman.compressionRatio <= 1);
}

TEST(HuffmanTest, TestCompressDataTxt2) {
    Huffman alg_huffman;
    Input input("../../files_for_compress/test2.txt");
    Output output("../../compressed_files/test2.bin");
    alg_huffman.Compress(input, output);

    ASSERT_EQ(true, alg_huffman.compressionRatio <= 1);
}

TEST(SelectorTest, TestDecompressDataTxt1){
    Huffman alg_huffman;
    Input input("../../compressed_files/test1.bin");
    Output output("../../decompressed_files/test1.txt");
    alg_huffman.Decompress(input, output);

    bool result = IsFilesEqual("../../files_for_compress/test1.txt", "../../decompressed_files/test1.txt");

    ASSERT_EQ(true, result);
}

TEST(SelectorTest, TestDecompressDataTxt2){
    Huffman alg_huffman;
    Input input("../../compressed_files/test2.bin");
    Output output("../../decompressed_files/test2.txt");
    alg_huffman.Decompress(input, output);

    bool result = IsFilesEqual("../../files_for_compress/test2.txt", "../../decompressed_files/test2.txt");

    ASSERT_EQ(true, result);
}


TEST(HuffmanTest, TestCompressDataPng9){
    Huffman alg_huffman;
    Input input("../../files_for_compress/test9.png");
    Output output("../../compressed_files/test9.bin");
    alg_huffman.Compress(input, output);

    Input _input("../../compressed_files/test9.bin");
    Output _output("../../decompressed_files/test9.png");
    alg_huffman.Decompress(_input, _output);

    bool result = IsFilesEqual("../../files_for_compress/test9.png", "../../decompressed_files/test9.png");
    ASSERT_EQ(true, result);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}