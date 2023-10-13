#include "image.hpp"
#include <fstream>

using reader::Image;

Image::Image(byte _width, byte _height) : 
        m_width(_width), m_height(_height)
{
    m_pixels.resize(m_width*m_height);
}


Image::Image(byte _width, byte _height, 
                const std::vector<byte>& _pixels) :
                m_width(_width), m_height(_height)
{
    m_pixels.resize(m_width*m_height);
    std::copy(_pixels.begin(), _pixels.end(), m_pixels.begin());
}

const std::vector<byte>& Image::reader() const
{
    return m_pixels;
}
byte Image::width() const
{
    return m_width;
}
byte Image::height() const
{
    return m_height;
}

void reader::Image::set_label(byte _label)
{
    m_label = _label;
}

byte Image::label() const
{
    return m_label;
}

void Image::output_pgm(const char *_PATH) const
{
    std::ofstream file(_PATH, std::ios::binary);
    if(file.is_open()){
        if (m_pixels.size() != m_width * m_height) {
            file.close();
            throw std::runtime_error("Invalid image dimensions.");
        }
        
        file << "P2\n" << m_width << " " << m_height << '\n'
            << 255 << '\n';

        for(size_t i = 0; i < m_pixels.size();){
            file << static_cast<int>(m_pixels.at(i)) << ' ';
            if(++i % m_height == 0) file << '\n';
        }
        
        file.close();
    }

    else
        throw std::runtime_error("cannot create image.");
}