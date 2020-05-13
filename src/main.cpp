#include <iostream>
#include <bitset>
#include "bdf_reader.hpp"

#define BDF_VERSION "0.1.0"

int main(int argc, char **argv)
{
    std::cout << "BDF Reader v" << BDF_VERSION << "." << std::endl;

    BDFFont *font = BDFReader::load_font("font.bdf");

    // Get data for the 'A' key
    char *key = font->get_bitmap_data('A');

    std::cout << "A is ..." << std::endl;
    for (int i = 0; i < font->get_char_height(); i++)
    {
        std::cout << std::bitset<8>(key[i]) << std::endl;
    }

    return 0;
}