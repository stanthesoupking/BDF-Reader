#pragma once
#include "bdf_font.hpp"

#include <string>

namespace BDF
{
class BDFReader
{
public:
	static BDFFont *load_font(std::string path);
};
} // namespace BDF
