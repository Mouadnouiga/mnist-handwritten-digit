#include "reader/include/reader.hpp"
#include <iostream>
#include <string>

int main(){
    const char *featuers_path = "./../data/t10k-images-idx3-ubyte";
    const char *labels_path = "./../data/t10k-labels-idx1-ubyte";

    reader::Reader rd;
    rd.read_testset(featuers_path, labels_path); 
    for(char i = 0; i < 20; ++i){
        std::string path("../images/image");
        path = path + i;
        rd.testset().at(20*i).output_pgm(path.c_str());
    }
}