#include "Algorithm.h"
using namespace std;

Algorithm::Algorithm() : compressionRatio(0) {

}

double Algorithm::Compress(Input& input, Output& output){
    if(input.isFileOpenedSuccesful && !input.isFileEmpty()){
        Encode(input, output);
        compressionRatio = (double)output.GetFileSize()/(double)input.GetFileSize();
        return compressionRatio;
    }
    assert("File for compress is empty or doesn't exist");
}




void Algorithm::Decompress(Input& input, Output& output){
    if(input.isFileOpenedSuccesful && !input.isFileEmpty()){
        Decode(input, output);
        return;
    }
    assert("File for decompress is empty or doesn't exist");
}



double Algorithm::GetCompressionRatio() {
    return compressionRatio;
}

