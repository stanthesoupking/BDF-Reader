#include "bdf_reader.hpp"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>

using namespace BDF;

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
    BDFFontBitmapBoundingBox bbx;
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
            // Add y-offset lines
            int above_row_count = ((bounding_box.height - bbx.height) - bbx.offset_y);
            for (int i = 0; i < above_row_count; i++)
            {
                bitmap_data[(current_character * char_stride) + i] = 0;
            }

            for (int i = above_row_count; i < above_row_count + bbx.height; i++)
            {
                std::string hstr;
                f >> hstr;

                int byte = 0;
                std::stringstream ss;
                ss << std::hex << hstr;
                ss >> byte;

                // Apply x-offset
                // Note: This may be changed to not be hard-coded into bitmap data.
                //  Could instead supply the offset to the user to decide how to offset it?
                byte = byte >> bbx.offset_x;

                bitmap_data[(current_character * char_stride) + i] = byte;
            }

            // Append remaining lines
            for (int i = above_row_count + bbx.height; i < bounding_box.height; i++)
            {
                bitmap_data[(current_character * char_stride) + i] = 0;
            }

            // Read ENDCHAR
            std::getline(f, line);
        }

        bool isFontBoundingBox = (key.compare("FONTBOUNDINGBOX") == 0);
        bool isBBX = (key.compare("BBX") == 0);

        if (isFontBoundingBox || isBBX)
        {
            BDFFontBitmapBoundingBox tbox = {0, 0, 0, 0};

            // Bounding box definition
            f >> tbox.width >> tbox.height >> tbox.offset_x >> tbox.offset_y;

            // Only allow fonts with a width of <= 8 (byte)
            if (tbox.width > 8)
            {
                std::cout << "Error: Only fonts with a width of 8 or less pixels are supported." << std::endl;
                return nullptr;
            }

            if (isFontBoundingBox)
            {
                bounding_box = tbox;
                char_stride = bounding_box.height;
            }
            else if (isBBX)
            {
                bbx = tbox;
            }
        }
        else if (key.compare("ENCODING") == 0)
        {
            // Get current character character
            f >> current_character;
        }
    }

    f.close();

    return new BDFFont(bounding_box, bitmap_data);
}