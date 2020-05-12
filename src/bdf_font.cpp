#include "bdf_font.hpp"

BDFFont::BDFFont(BDFFontBitmapBoundingBox _bounding_box, char * _bitmap_data)
{
	bounding_box = _bounding_box;

	// Calculate character stride
	char_bitmap_stride = bounding_box.height;

	bitmap_data = _bitmap_data;
}

BDFFont::~BDFFont()
{
	// Free allocated memory
}

char * BDFFont::get_bitmap_data(char c)
{
	return &bitmap_data[c * char_bitmap_stride];
}
