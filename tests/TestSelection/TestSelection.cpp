#include <gtest/gtest.h>
#include <Selection.h>
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


TEST(SelectorTest, TestChooseAlgorithmAndGetName1){
    string name_alg = "Huffman";
    string type_file = "txt";
    Selection selector(type_file);
    ASSERT_EQ(true,  name_alg == (selector.GetNameAlgorithm()));
}



TEST(SelectorTest, TestChooseAlgorithmAndGetName2){
    string name_alg = "LZW";
    string type_file = "jpg";
    Selection selector(type_file);
    ASSERT_EQ(true,  name_alg == (selector.GetNameAlgorithm()));
}

TEST(SelectorTest, TestChooseAlgorithmAndGetName3){
    string name_alg = "LZW";
    string type_file = "png";
    Selection selector(type_file);
    ASSERT_EQ(true,  name_alg == (selector.GetNameAlgorithm()));
}

TEST(SelectorTest, TestChooseAlgorithmAndGetName4){
    string name_alg = "Huffman";
    string type_file = "zip";
    Selection selector(type_file);
    ASSERT_EQ(true,  name_alg == (selector.GetNameAlgorithm()));
}

TEST(SelectionTest, TestCompressAndDecompresssDataTxt1) {
    string type_file = "txt";

    Selection alg_huffman(type_file);

    alg_huffman.Compress("../../files_for_compress/test1.txt", "../../compressed_files/test1.bin");

    alg_huffman.Decompress("../../compressed_files/test1.bin", "../../decompressed_files/test1.txt");

    bool result = IsFilesEqual("../../files_for_compress/test1.txt", "../../decompressed_files/test1.txt");
    ASSERT_EQ(true, result);
}



TEST(SelectorTest, TestCompressDataTxt1){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test1.txt", "../../compressed_files/test1.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}
TEST(SelectorTest, TestCompressDataTxt2){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test2.txt", "../../compressed_files/test2.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}
TEST(SelectorTest, TestCompressDataTxt3){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test3.txt", "../../compressed_files/test3.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}

TEST(SelectorTest, TestCompressDataTxt4){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test4.txt", "../../compressed_files/test4.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}

TEST(SelectorTest, TestCompressDataTxt5){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test5.txt", "../../compressed_files/test5.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}

TEST(SelectorTest, TestCompressDataJpg6){
    string type_file = "jpg";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test6.jpg", "../../compressed_files/test6.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}



TEST(SelectorTest, TestCompressDataPng9){
    string type_file = "png";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test9.png", "../../compressed_files/test9.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}

TEST(SelectorTest, TestCompressDataZip10){
    string type_file = "zip";
    Selection selector(type_file);
    selector.Compress("../../files_for_compress/test10.zip", "../../compressed_files/test10.bin");
    ASSERT_EQ(true, selector.compressionRatio <= 1);
}





TEST(SelectorTest, TestDecompressDataTxt3) {
    string type_file = "txt";
    Selection selector(type_file);
    selector.Decompress("../../compressed_files/test3.bin", "../../decompressed_files/test3.txt");
    bool result = IsFilesEqual("../../files_for_compress/test3.txt", "../../decompressed_files/test3.txt");
    ASSERT_EQ(true, result);
}

TEST(SelectorTest, TestDecompressDataTxt4){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Decompress("../../compressed_files/test4.bin", "../../decompressed_files/test4.txt");
    bool result = IsFilesEqual("../../files_for_compress/test4.txt", "../../decompressed_files/test4.txt");
    ASSERT_EQ(true, result);

}

TEST(SelectorTest, TestDecompressDataTxt5){
    string type_file = "txt";
    Selection selector(type_file);
    selector.Decompress("../../compressed_files/test5.bin", "../../decompressed_files/test5.txt");
    bool result = IsFilesEqual("../../files_for_compress/test5.txt", "../../decompressed_files/test5.txt");
    ASSERT_EQ(true, result);
}


//TEST(SelectorTest, TestDecompressDataPdf7){
//    string type_file = "pdf";
//    Selection selector(type_file);
//    selector.Decompress("../../compressed_files/test7.bin", "../../decompressed_files/test7.pdf");
//    bool result = IsFilesEqual("../../files_for_compress/test7.pdf", "../../decompressed_files/test7.pdf");
//    ASSERT_EQ(true, result);
//}
//
//TEST(SelectorTest, TestDecompressDataPfd8){
//    string type_file = "pdf";
//    Selection selector(type_file);
//    selector.Decompress("../../compressed_files/test8.bin", "../../decompressed_files/test8.pdf");
//    bool result = IsFilesEqual("../../files_for_compress/test8.pdf", "../../decompressed_files/test8.pdf");
//    ASSERT_EQ(true, result);
//}






int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}