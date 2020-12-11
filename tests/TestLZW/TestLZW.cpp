#include <gtest/gtest.h>
#include <LZW.h>
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

TEST(LZWTest, TestShouldChoose1){
    LZW alg_lzw;
    vector<string> types_file = {"png", "tiff", "jpg", "gif", "bmp"};
    for(auto &it : types_file){
        ASSERT_EQ(true, alg_lzw.ShouldChoose(it));
    }

}

TEST(LZWTest, TestShouldChoose2){
    LZW alg_lzw;
    vector<string> types_file = {"blabla"};
    for(auto &it : types_file){
        ASSERT_EQ(false, alg_lzw.ShouldChoose(it));
    }

}

TEST(LZWTest, TestGetName1){
    LZW alg_lzw;
    string name = "LZW";
    ASSERT_EQ(true, alg_lzw.GetName() == name);

}

TEST(LZWTest, TestGetName2){
    LZW alg_huffman;
    string name = "NOTLZW";
    ASSERT_EQ(false, alg_huffman.GetName() == name);

}



TEST(LZWTest, TestCompressDataTxt1){
    LZW alg_lzw;
    Input input("../../files_for_compress/test1.txt");
    Output output("../../compressed_files/test1.bin");
    alg_lzw.Compress(input, output);
    ASSERT_EQ(true, alg_lzw.compressionRatio <= 1);
}


TEST(LZWTest, TestCompressDataPng9){
    LZW alg_lzw;
    Input input("../../files_for_compress/test9.png");
    Output output("../../compressed_files/test9.bin");
    alg_lzw.Compress(input, output);
    ASSERT_EQ(false, alg_lzw.compressionRatio <= 1);
}

TEST(SelectorTest, TestDecompressDataTxt1){
    LZW alg_huffman;
    Input input("../../compressed_files/test1.bin");
    Output output("../../decompressed_files/test1.txt");
    alg_huffman.Decompress(input, output);

    bool result = IsFilesEqual("../../files_for_compress/test1.txt", "../../decompressed_files/test1.txt");

    ASSERT_EQ(true, result);
}

TEST(SelectorTest, TestDecompressDataPng9){
    LZW alg_huffman;
    Input input("../../compressed_files/test9.bin");
    Output output("../../decompressed_files/test9.png");
    alg_huffman.Decompress(input, output);

    bool result = IsFilesEqual("../../files_for_compress/test9.png", "../../decompressed_files/test9.png");

    ASSERT_EQ(true, result);
}






int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
