#include "reader.hpp"
#include <fstream>
#include <iostream>

using reader::Reader;

Reader::Reader()
{
    m_trainset = new std::vector<reader::Image>();
    m_testset = new std::vector<reader::Image>();
}

Reader::~Reader()
{
    delete m_testset;
    delete m_trainset;
}

byte4 reader::convert_to_low(byte *_high)
{
    return (byte4) ((_high[0] << 24) |
			   		   (_high[1] << 16) |
			   		   (_high[2] << 8)  |
			   		   (_high[3]));
}

std::vector<reader::Image>* Reader::read_features(const char* _PATH)
{
    std::ifstream file(_PATH, std::ios::binary);
    if (file.is_open()) {
        byte4 info[4];
        byte _byte[4];

        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j)
                file >> _byte[j];
            info[i] = convert_to_low(_byte);
        }

        std::cout << "reading header has done.\n";

        byte4 n_images = info[1];
        byte4 height = info[2];
        byte4 width = info[3];

        std::vector<reader::Image> *images = new std::vector<reader::Image>();

        for(byte4 i = 0; i < n_images; ++i){
            reader::Image img((byte)width, (byte)height);
            for(byte4 j = 0; j < width*height; ++j)
                file >> img.m_pixels[j];
            images->push_back(img);
        }
        file.close();

        if(images->size() != n_images){
            throw std::runtime_error("cannot read the entier data.");
            return NULL;
        }

        std::cout << "reading " << images->size() << " simples.\n";
        return images;
    }

    throw std::invalid_argument(
        "cannot open dataset file.");
}

void Reader::read_labels(const char* _PATH, std::vector<reader::Image>* _images)
{
    std::ifstream file(_PATH, std::ios::binary);
    if (file.is_open()) {
        byte4 info[2];
        byte _byte[4];
        for(int i = 0; i < 2; ++i){
            for(int j = 0; j < 4; ++j)
                file >> _byte[j];
            info[i] = convert_to_low(_byte);
        }
        
        byte4 n_items = info[1];
        if(_images->size() != n_items)
            throw std::runtime_error("cannot read the label size correctlly.");

        for(byte4 i = 0; i < n_items; ++i)
            file >> _images->at(i).m_label;

        file.close();
        
        std::cout << "reading labels has been done.\n";
        return;
    }

    throw std::invalid_argument(
        "cannot open label file.");
}


bool reader::find(std::vector<byte>* _vector, byte _element)
{
    for(byte data : *_vector)
        if(data == _element)
            return true;
    return false;
}

int Reader::count_classes()
{
    std::vector<byte> *classes;
    for(size_t i = 0; i < m_trainset->size(); ++i){
        byte label = m_trainset->at(i).m_label;
        if(!find(classes, label))
            classes->push_back(label);
    }

    m_classes = (int)(classes->size());
    return m_classes;
}

void Reader::read_trainset(const char* _features, const char* _labels)
{
    std::vector<reader::Image> *data = 
            read_features(_features);
    
    read_labels(_labels, data);
    m_trainset = data;
}

void Reader::read_testset(const char* _features, const char* _labels)
{
    std::vector<reader::Image> *data = 
            read_features(_features);
    
    read_labels(_labels, data);
    m_testset = data;
}

std::vector<reader::Image>& Reader::trainset() const
{
    return *m_trainset;
}
std::vector<reader::Image>& Reader::testset() const
{
    return *m_testset;
}
int Reader::classes() const
{
    return m_classes;
}