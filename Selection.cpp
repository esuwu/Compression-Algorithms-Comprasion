#include <algorithm>
#include <memory>
#include <sstream>
#include "Selection.h"
#include "logger.h"
using namespace std;

Selection::Selection(string _typeFile, vector<shared_ptr<Algorithm>> added_algos) : isActive(false), typeFile(_typeFile), compressionRatio(0), addedAlgos(std::move(added_algos)) {
    logger::init_logger("selection.log");
    logger::write_info("Инициализация...");

}

void Selection::GetActive() {
    Add(shared_ptr<Huffman>(new Huffman));
    Add(shared_ptr<LZW>(new LZW));
    for(auto &it : addedAlgos){
        Add(it);
    }
    ChooseAlgorithm();
    isActive = true;
}

double Selection::Compress(string input_filepath, string output_filepath){
    if(!isActive){
        GetActive();
    }

    Input input(input_filepath);
    Output output(output_filepath);

    string Recovery = "Сжимаю файл " + input_filepath + " ...";
    logger::write_info(Recovery);

    algo->Compress(input, output); //getAlgo
    compressionRatio = algo->compressionRatio;

    string Recovering_success = "Сжал исходный файл в: " + output_filepath;
    logger::write_info(Recovering_success);

    if(IsOrigLessCompr((double)output.GetFileSize(), (double)input.GetFileSize())){
        logger::write_info("Сжатый файл оказался больше исходного.");
        logger::write_info("Удаляю сжатый файл.");
        output.RemoveFile();
        compressionRatio = 1;
    }

    std::ostringstream oss;
    oss << compressionRatio;
    string comprRat = "Коэффициент сжатия " + oss.str();
    logger::write_info(comprRat);

    return compressionRatio;
}

void Selection::Decompress(string input_filepath, string output_filepath){
    if(!isActive){
        GetActive();
    }
    string Recovery = "Восстанавливаю сжатый файл " + input_filepath + " ...";
    logger::write_info(Recovery);

    Input input(input_filepath);
    Output output(output_filepath);
    algo->Decompress(input, output);
    string Recovering_success = "Восстанавил сжатый файл: " + output_filepath;
    logger::write_info(Recovering_success);

}


void Selection::Add(shared_ptr<Algorithm> chosen_alg) {
    arrayAlgos.push_back(chosen_alg);
}

void Selection::SetDefaultAlg() {
    static shared_ptr<Huffman> huffman_algo(new Huffman);
    algo = huffman_algo;
    logger::write_info("Выбрал алгоритм: ");
    logger::write_info(algo->GetName());
}


void Selection::ChooseAlgorithm() {
    logger::write_info("Выбираю алгоритм...");
    for (auto &it : arrayAlgos){
        if(it->ShouldChoose(typeFile)){
            algo = it;
            logger::write_info("Выбрал алгоритм: ");
            logger::write_info(algo->GetName());
            return;
        }
    }

     SetDefaultAlg();

}

string Selection::GetNameAlgorithm(){
    if(!isActive){
        GetActive();
    }
   return algo->GetName();
}

string Selection::GetTypeFile() {
    return typeFile;
}

bool Selection::IsOrigLessCompr(double size_compressed_f, double size_origin_f) {
    return (size_origin_f < size_compressed_f);
}

