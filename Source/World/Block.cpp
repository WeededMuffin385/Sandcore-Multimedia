#include <iostream>

import Sandcore.World;


namespace Sandcore {
	World::Chunk::Block::Block(Identification identification) : identification(identification) {
	}

	World::Chunk::Block::Identification World::Chunk::Block::getId() {
		return identification;
	}
}