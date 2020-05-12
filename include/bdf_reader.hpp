#pragma once
#include "bdf_font.hpp"

#include <iostream>

class BDFReader {
	public:
		static BDFFont *load_font(std::string path);
};
