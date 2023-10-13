#pragma once

#include <vector>

#define byte unsigned char

namespace reader{
    class Reader;

    class Image{
        friend class Reader;
        public:
            Image(byte, byte);
            Image(byte, byte, const std::vector<byte>&);

            inline const std::vector<byte>& reader() const;
            inline byte width() const;
            inline byte height() const;
            inline void set_label(byte);
            inline byte label() const;
            

            void output_pgm(const char *) const;

        private:
            std::vector<byte> m_pixels;
            int m_width, m_height;
            byte m_label;

    };  // Image class

};  // reader namespace