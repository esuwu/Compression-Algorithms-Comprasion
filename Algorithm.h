//
// Created by alexandr on 11/25/19.
//

#ifndef PROTOTIPE_ALGORITHM_H
#define PROTOTIPE_ALGORITHM_H

#include <algorithm>
#include <cassert>
#include "IInputStream.h"
#include "Input.h"
#include "IOutputStream.h"
#include <iostream>
#include <list>
#include <math.h>
#include <map>
#include <stack>
#include "Output.h"
#include <vector>



class Algorithm {
public:
    Algorithm();
    ~Algorithm() = default;
    double compressionRatio;
    double Compress(Input& input, Output& output);
    void Decompress(Input& input, Output& output);
    virtual bool ShouldChoose(std::string type_file) = 0;
    virtual double GetCompressionRatio();
    virtual std::string GetName() = 0;
private:
    bool IsOrigLessCompr(double size_compressed_f, double size_origin_f);
    virtual void Encode(IInputStream& original, IOutputStream& compressed) = 0;
    virtual void Decode(IInputStream& compressed, IOutputStream& original) = 0;
};


#endif //PROTOTIPE_ALGORITHM_H
