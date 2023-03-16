#include <ft2build.h>
#include FT_FREETYPE_H 

#include <stdexcept>


import Sandcore.Application;
using namespace Sandcore;

int main() {
	FT_Library ft;
	FT_Face face;

	if (FT_Init_FreeType(&ft)) {
		throw std::exception("Could not initialize FreeType!");
	}

	if (FT_New_Face(ft, "C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/Resources/LiberationSans-Regular.ttf", 0, &face)) {
		throw std::exception("Failed to load font!");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
		throw std::exception("Failed to load Glyph");
		return -1;
	}
}