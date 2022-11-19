#include <string>

export module Sandcore.World.Chunk;

import Sandcore.World.Block;
import Sandcore.Vector3D;

export namespace Sandcore {
	class WorldChunk {
	public:
		WorldChunk();

		void upload(std::string& data);

		Block& getBlock(Vector3D<int> position);
		Block& getBlock(int x, int y, int z);

		void setBlock(Vector3D<int> position, Block block);
		void setBlock(int x, int y, int z, Block block);

		enum size : unsigned char {
			x = 16,
			y = 16,
			z = 16
		};

		bool loaded = false;
		bool loadInProgress = false;

		int drawCount = 0;
	private:

		Block blocks[size::x][size::y][size::z];
	};
}