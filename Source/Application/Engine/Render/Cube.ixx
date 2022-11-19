export module Sandcore.Cube;

import Sandcore.World.Block;
import Sandcore.TexturePackage;

export namespace Sandcore {
	struct Axis {
		float minus = 0;
		float plus = 0;
	};

	struct Cube {
		static Cube getCube(Block::Identification identification);

		Axis x;
		Axis y;
		Axis z;

	private:
		static bool initialize();
	};

	Cube Cube::getCube(Block::Identification identification) {
		switch (identification) { // switch - because faster
			case Sandcore::Block::grass:	return { {(float)TexturePackage::BlockIdentification::grassSide, (float)TexturePackage::BlockIdentification::grassSide}, {(float)TexturePackage::BlockIdentification::grassSide, (float)TexturePackage::BlockIdentification::grassSide}, {(float)TexturePackage::BlockIdentification::dirt, (float)TexturePackage::BlockIdentification::grassTop} };
			case Sandcore::Block::stone:	return { {(float)TexturePackage::BlockIdentification::stone,(float)TexturePackage::BlockIdentification::stone}, {(float)TexturePackage::BlockIdentification::stone,(float)TexturePackage::BlockIdentification::stone}, {(float)TexturePackage::BlockIdentification::stone,(float)TexturePackage::BlockIdentification::stone} };
			case Sandcore::Block::dirt:		return { {(float)TexturePackage::BlockIdentification::dirt, (float)TexturePackage::BlockIdentification::dirt}, {(float)TexturePackage::BlockIdentification::dirt, (float)TexturePackage::BlockIdentification::dirt}, {(float)TexturePackage::BlockIdentification::dirt, (float)TexturePackage::BlockIdentification::dirt} };
			case Sandcore::Block::water:	return { {(float)TexturePackage::BlockIdentification::waterTop,(float)TexturePackage::BlockIdentification::waterTop }, {(float)TexturePackage::BlockIdentification::waterTop,(float)TexturePackage::BlockIdentification::waterTop}, {(float)TexturePackage::BlockIdentification::waterTop,(float)TexturePackage::BlockIdentification::waterTop} };
			case Sandcore::Block::sand:		return { {(float)TexturePackage::BlockIdentification::sand,(float)TexturePackage::BlockIdentification::sand}, {(float)TexturePackage::BlockIdentification::sand,(float)TexturePackage::BlockIdentification::sand}, {(float)TexturePackage::BlockIdentification::sand,(float)TexturePackage::BlockIdentification::sand} };
			case Sandcore::Block::wood:		return { {(float)TexturePackage::BlockIdentification::woodSide, (float)TexturePackage::BlockIdentification::woodSide}, {(float)TexturePackage::BlockIdentification::woodSide,(float)TexturePackage::BlockIdentification::woodSide}, {(float)TexturePackage::BlockIdentification::woodTop,(float)TexturePackage::BlockIdentification::woodTop} };
			case Sandcore::Block::leaves:	return { {(float)TexturePackage::BlockIdentification::leaves, (float)TexturePackage::BlockIdentification::leaves},{(float)TexturePackage::BlockIdentification::leaves, (float)TexturePackage::BlockIdentification::leaves},{(float)TexturePackage::BlockIdentification::leaves, (float)TexturePackage::BlockIdentification::leaves} };
			case Sandcore::Block::lava:		return { {(float)TexturePackage::BlockIdentification::lava,(float)TexturePackage::BlockIdentification::lava}, {(float)TexturePackage::BlockIdentification::lava,(float)TexturePackage::BlockIdentification::lava}, {(float)TexturePackage::BlockIdentification::lava,(float)TexturePackage::BlockIdentification::lava} };
			case Sandcore::Block::ironOre:	return { {(float)TexturePackage::BlockIdentification::ironOre, (float)TexturePackage::BlockIdentification::ironOre}, {(float)TexturePackage::BlockIdentification::ironOre, (float)TexturePackage::BlockIdentification::ironOre}, {(float)TexturePackage::BlockIdentification::ironOre, (float)TexturePackage::BlockIdentification::ironOre} };
			case Sandcore::Block::coalOre:	return { {(float)TexturePackage::BlockIdentification::coalOre, (float)TexturePackage::BlockIdentification::coalOre}, {(float)TexturePackage::BlockIdentification::coalOre, (float)TexturePackage::BlockIdentification::coalOre}, {(float)TexturePackage::BlockIdentification::coalOre, (float)TexturePackage::BlockIdentification::coalOre} };
			case Sandcore::Block::goldOre:	return { {(float)TexturePackage::BlockIdentification::goldOre, (float)TexturePackage::BlockIdentification::goldOre}, {(float)TexturePackage::BlockIdentification::goldOre, (float)TexturePackage::BlockIdentification::goldOre}, {(float)TexturePackage::BlockIdentification::goldOre, (float)TexturePackage::BlockIdentification::goldOre} };
			default:						return { 0,0,0,0,0,0 };
		}
	}
}