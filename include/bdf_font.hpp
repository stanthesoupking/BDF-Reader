#pragma once

struct BDFFontBitmapBoundingBox {
	int width;
	int height;
	int offset_x;
	int offset_y;
};

class BDFFont {
	private:
		BDFFontBitmapBoundingBox bounding_box;
		char *bitmap_data;

		// Stride between character entries in bitmap data
		int char_bitmap_stride;
	public:
		BDFFont(BDFFontBitmapBoundingBox _bounding_box, char * _bitmap_data);
		~BDFFont();	

		char * get_bitmap_data(char c);

		int get_char_width();
		int get_char_height();
};
