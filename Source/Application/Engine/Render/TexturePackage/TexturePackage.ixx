#include <filesystem>

export module Sandcore.TexturePackage;

import Sandcore.Graphics.Texture3D;

export namespace Sandcore {
	class TexturePackage {
	public:
		TexturePackage(std::filesystem::path path);

		void bindBlocks();
		double getCapacity();

		enum class BlockIdentification {
			wrong,

			grassTop,
			grassSide,

			waterTop,
			waterSide,

			dirt,
			stone,
			sand,

			ironOre,
			coalOre,
			goldOre,

			lava,

			woodTop,
			woodSide,

			leaves,

			size
		};

		Texture3D blockTextures;
	private:

		void load(std::filesystem::path path);
		void loadBlocks(std::filesystem::path path);
		void loadBlock(BlockIdentification identification, std::filesystem::path path);

		void loadInformation(std::filesystem::path path);

		int width;
		int height;
	};
}