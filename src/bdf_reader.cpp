#include "bdf_reader.hpp"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>

BDFFont *BDFReader::load_font(std::string path)
{
    std::ifstream f(path);
    if (!f.is_open())
    {
        std::cout << "Failed opening file." << std::endl;
        return nullptr;
    }

    std::string line;

    // Get STARTFONT
    const std::string VERSION_LINE = "STARTFONT 2.1";
    std::getline(f, line);
    line = line.substr(0, VERSION_LINE.size());

    if (line.compare(VERSION_LINE) != 0)
    {
        std::cout << "Unsupported BDF format." << std::endl;
    }

    const std::string BITMAP_LINE = "BITMAP";
    BDFFontBitmapBoundingBox bounding_box;
    int current_character = 0;
    int char_stride;
    char *bitmap_data = nullptr;

    while (true)
    {
        // Check if end of file
        if (!getline(f, line))
        {
            break;
        }

        // Get line key
        std::string key;
        f >> key;

        // Check if start of bitmap data
        if (key.compare("BITMAP") == 0)
        {
            // Allocate bitmap data (if not already allocated)
            if (bitmap_data == nullptr)
            {
                bitmap_data = (char *)malloc(sizeof(char) * bounding_box.height * 256);
            }

            // Read bitmap data
            for (int i = 0; i < bounding_box.height; i++)
            {
                std::string hstr;
                f >> hstr;

                int byte = 0;
                std::stringstream ss;
                ss << std::hex << hstr;
                ss >> byte;

                bitmap_data[(current_character * char_stride) + i] = byte;
            }

            // Read ENDCHAR
            std::getline(f, line);
        }

        if (key.compare("FONTBOUNDINGBOX") == 0)
        {
            // Bounding box definition
            f >> bounding_box.width >> bounding_box.height >> bounding_box.offset_x >> bounding_box.offset_y;
            char_stride = bounding_box.height;

            // Only allow fonts with a width of <= 8 (byte)
            if (bounding_box.width > 8)
            {
                std::cout << "Error: Only fonts with a width of 8 or less pixels are supported." << std::endl;
                return nullptr;
            }
        }
        else if (key.compare("STARTCHAR") == 0)
        {
            // Get current character character
            f >> current_character;
        }
    }

    f.close();

    return new BDFFont(bounding_box, bitmap_data);
}