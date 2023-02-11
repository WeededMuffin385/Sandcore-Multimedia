#include <filesystem>
#include <fstream>

import Sandcore.Render.Textures;

import Sandcore.Graphics.Texture3D;

namespace Sandcore {
	RenderTextures::RenderTextures(std::filesystem::path path) {
		load(path);
	}

	void RenderTextures::load(std::filesystem::path path) {
		loadInformation(path / "info.txt");
		loadBlocks(path / "blocks");
	}

	double RenderTextures::getCapacity() {
		return (double)BlockIdentification::size;
	}

	void RenderTextures::loadInformation(std::filesystem::path path) {
		std::ifstream file(path);

		while (!file.eof()) {
			std::string identification;
			file >> identification;

			if (identification == "resolution") file >> width >> height;
		}
	}

	void RenderTextures::loadBlocks(std::filesystem::path path) {
		using TPBI = BlockIdentification;

		blockTextures.create(width, height, static_cast<int>(TPBI::size));

		loadBlock(TPBI::Wrong, path / "wrong.png");

		loadBlock(TPBI::Dirt, path / "dirt.png");

		loadBlock(TPBI::GrassTop, path / "grass_top.png");
		loadBlock(TPBI::GrassSide, path / "grass_side.png");


		loadBlock(TPBI::Stone, path / "stone.png");

		loadBlock(TPBI::WaterTop, path / "water_3.png");
		loadBlock(TPBI::Sand, path / "sand.png");

		loadBlock(TPBI::WoodTop, path / "wood_top.png");
		loadBlock(TPBI::WoodSide, path / "wood_side.png");

		loadBlock(TPBI::Leaves, path / "leaves.png");

		loadBlock(TPBI::IronOre, path / "iron_ore.png");
		loadBlock(TPBI::CoalOre, path / "coal_ore.png");
		loadBlock(TPBI::GoldOre, path / "gold_ore.png");

		loadBlock(TPBI::Lava, path / "lava.png");

		blockTextures.generateMipmap();
	}

	void RenderTextures::loadBlock(BlockIdentification identification, std::filesystem::path path) {
		blockTextures.loadFromFile(static_cast<int>(identification), path);
	}

	void RenderTextures::bindBlocks() {
		blockTextures.bind();
	}
}