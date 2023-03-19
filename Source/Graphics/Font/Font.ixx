module;
#include <ft2build.h>
#include FT_FREETYPE_H 

#include <stdexcept>
#include <map>
#include <glm/glm.hpp>

#include <filesystem>
#include <fstream>
export module Sandcore.Graphics.Font;

export namespace Sandcore {
	class Font {
	public:
		Font() {
			static bool init = []() ->bool {
				if (FT_Init_FreeType(&freetype)) throw std::exception("FreeType initialization failed!");
				return true;
			}();
		}

		void loadFromFile(std::filesystem::path path) {
			if (FT_New_Face(freetype, path.string().c_str(), 0, &face)) throw std::exception("Unable to load font!");
		}


	private:


		FT_Face face;
		inline static FT_Library freetype;
	};
}