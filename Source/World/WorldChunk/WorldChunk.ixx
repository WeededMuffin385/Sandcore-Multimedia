module;
#include <string>
#include <chrono>
#include <glm/glm.hpp>
export module Sandcore.World.Chunk;

import Sandcore.World.Block;

export namespace Sandcore {
	class WorldChunk {
	public:
		WorldChunk();

		void upload(std::string& data);

		const Block& getBlock(glm::ivec3 position);
		const Block& getBlock(int x, int y, int z);

		void setBlock(glm::ivec3 position, Block block);
		void setBlock(int x, int y, int z, Block block);

		enum size : unsigned char {
			x = 16,
			y = 16,
			z = 16
		};

		bool isUnwanted(std::chrono::high_resolution_clock::time_point& end);
		void setWanted();

		bool loaded = false;
		bool loadInProgress = false;

		bool changed = false;
	private:
		std::chrono::high_resolution_clock::time_point wanted = std::chrono::high_resolution_clock::now();
		Block blocks[size::x][size::y][size::z];
	};
}