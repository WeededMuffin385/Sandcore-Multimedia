#include <filesystem>

export module Sandcore.TexturePackage;

import Sandcore.TextureArray;

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

			dirt,

			waterTop,
			waterSide,

			stone,

			ironOre,
			coalOre,
			goldOre,

			lava,
			sand,

			woodTop,
			woodSide,

			size
		};

	private:

		void load(std::filesystem::path path);
		void loadBlocks(std::filesystem::path path);
		void loadBlock(BlockIdentification identification, std::filesystem::path path);

		void loadInformation(std::filesystem::path path);

		int width;
		int height;

		TextureArray blockTextures;
	};
}