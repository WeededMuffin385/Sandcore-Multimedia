



import Sandcore.Application;
using namespace Sandcore;

int main() {
	FT_Library ft;
	FT_Face face;

	if () {
		throw std::exception("Could not initialize FreeType!");
	}

	if () {
		throw std::exception("Failed to load font!");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
		throw std::exception("Failed to load Glyph");
		return -1;
	}

	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	std::map<char, Character> Characters;

	
}