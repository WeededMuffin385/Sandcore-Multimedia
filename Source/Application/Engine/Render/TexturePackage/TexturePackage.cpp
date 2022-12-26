#include <filesystem>
#include <fstream>

import Sandcore.TexturePackage;

import Sandcore.Graphics.Texture3D;

namespace Sandcore {
	TexturePackage::TexturePackage(std::filesystem::path path) {
		load(path);
	}

	void TexturePackage::load(std::filesystem::path path) {
		loadInformation(path / "info.txt");
		loadBlocks(path / "blocks");
	}

	double TexturePackage::getCapacity() {
		return (double)BlockIdentification::size;
	}

	void TexturePackage::loadInformation(std::filesystem::path path) {
		std::ifstream file(path);

		while (!file.eof()) {
			std::string identification;
			file >> identification;

			if (identification == "resolution") file >> width >> height;
		}
	}

	void TexturePackage::loadBlocks(std::filesystem::path path) {
		using TPBI = BlockIdentification;

		blockTextures.create(width, height, static_cast<int>(TPBI::size));

		loadBlock(TPBI::wrong, path / "wrong.png");

		loadBlock(TPBI::dirt, path / "dirt.png");

		loadBlock(TPBI::grassTop, path / "grass_top.png");
		loadBlock(TPBI::grassSide, path / "grass_side.png");


		loadBlock(TPBI::stone, path / "stone.png");

		loadBlock(TPBI::waterTop, path / "water_3.png");
		loadBlock(TPBI::sand, path / "sand.png");

		loadBlock(TPBI::woodTop, path / "wood_top.png");
		loadBlock(TPBI::woodSide, path / "wood_side.png");

		loadBlock(TPBI::leaves, path / "leaves.png");

		loadBlock(TPBI::ironOre, path / "iron_ore.png");
		loadBlock(TPBI::coalOre, path / "coal_ore.png");
		loadBlock(TPBI::goldOre, path / "gold_ore.png");

		loadBlock(TPBI::lava, path / "lava.png");

		blockTextures.generateMipmap();
	}

	void TexturePackage::loadBlock(BlockIdentification identification, std::filesystem::path path) {
		blockTextures.loadFromFile(static_cast<int>(identification), path);
	}

	void TexturePackage::bindBlocks() {
		blockTextures.bind();
	}
}