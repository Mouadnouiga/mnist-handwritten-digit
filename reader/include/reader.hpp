#pragma once 

#include "./../../img/include/image.hpp"
#include <vector>

#define byte4 unsigned int

namespace reader{

    class Reader{

        public:
            Reader();
            ~Reader();

            void read_trainset(const char*, const char *);
            void read_testset(const char*, const char *);

            std::vector<reader::Image>& trainset() const;
            std::vector<reader::Image>& testset() const;
            int classes() const;
            

        private:
            std::vector<reader::Image>* read_features(const char*);
            void read_labels(const char*, std::vector<reader::Image>*);
            int count_classes();


            std::vector<reader::Image> *m_trainset;
            std::vector<reader::Image> *m_testset;
            int m_classes;

    }; // Reader class 

    byte4 convert_to_low(byte *_high);
    bool find(std::vector<byte>* _vector, byte _element);

}; // reader namespace