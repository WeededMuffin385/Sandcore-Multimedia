export module Sandcore.Cube;

import Sandcore.World.Block;
import Sandcore.Render.Textures;

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
		using T = RenderTextures::BlockIdentification;

		switch (identification) { // switch - because faster
			case Sandcore::Block::Grass:	return { {(float)T::GrassSide,	(float)T::GrassSide},	{(float)T::GrassSide,	(float)T::GrassSide},	{(float)T::Dirt,		(float)T::GrassTop} };
			case Sandcore::Block::Stone:	return { {(float)T::Stone,		(float)T::Stone},		{(float)T::Stone,		(float)T::Stone},		{(float)T::Stone,		(float)T::Stone} };
			case Sandcore::Block::Dirt:		return { {(float)T::Dirt,		(float)T::Dirt},		{(float)T::Dirt,		(float)T::Dirt},		{(float)T::Dirt,		(float)T::Dirt} };
			case Sandcore::Block::Water:	return { {(float)T::WaterTop,	(float)T::WaterTop },	{(float)T::WaterTop,	(float)T::WaterTop},	{(float)T::WaterTop,	(float)T::WaterTop} };
			case Sandcore::Block::Sand:		return { {(float)T::Sand,		(float)T::Sand},		{(float)T::Sand,		(float)T::Sand},		{(float)T::Sand,		(float)T::Sand} };
			case Sandcore::Block::Wood:		return { {(float)T::WoodSide,	(float)T::WoodSide},	{(float)T::WoodSide,	(float)T::WoodSide},	{(float)T::WoodTop,		(float)T::WoodTop} };
			case Sandcore::Block::Leaves:	return { {(float)T::Leaves,		(float)T::Leaves},		{(float)T::Leaves,		(float)T::Leaves},		{(float)T::Leaves,		(float)T::Leaves} };
			case Sandcore::Block::Lava:		return { {(float)T::Lava,		(float)T::Lava},		{(float)T::Lava,		(float)T::Lava},		{(float)T::Lava,		(float)T::Lava} };
			case Sandcore::Block::IronOre:	return { {(float)T::IronOre,	(float)T::IronOre},		{(float)T::IronOre,		(float)T::IronOre},		{(float)T::IronOre,		(float)T::IronOre} };
			case Sandcore::Block::CoalOre:	return { {(float)T::CoalOre,	(float)T::CoalOre},		{(float)T::CoalOre,		(float)T::CoalOre},		{(float)T::CoalOre,		(float)T::CoalOre} };
			case Sandcore::Block::GoldOre:	return { {(float)T::GoldOre,	(float)T::GoldOre},		{(float)T::GoldOre,		(float)T::GoldOre},		{(float)T::GoldOre,		(float)T::GoldOre} };
			default:						return { 0,0,0,0,0,0 };
		}
	}
}