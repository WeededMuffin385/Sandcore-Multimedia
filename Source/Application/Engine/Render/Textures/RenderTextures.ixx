module;
#include <filesystem>
export module Sandcore.Render.Textures;

import Sandcore.Graphics.Texture3D;

export namespace Sandcore {
	class RenderTextures {
	public:
		RenderTextures(std::filesystem::path path);

		void bindBlocks();
		double getCapacity();

		enum class BlockIdentification {
			Wrong,

			GrassTop,
			GrassSide,

			WaterTop,
			WaterSide,

			Dirt,
			Stone,
			Sand,

			IronOre,
			CoalOre,
			GoldOre,

			Lava,

			WoodTop,
			WoodSide,

			Leaves,

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