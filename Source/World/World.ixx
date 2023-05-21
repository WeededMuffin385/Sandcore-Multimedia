module;
#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
export module Sandcore.World;

import Sandcore.World.Entity;
import Sandcore.World.Block;
import Sandcore.World.Chunk;

export namespace Sandcore {
	class World {
	public:
		void tick();

		WorldChunk& getChunk(int x, int y, int z);
		WorldChunk& getChunk(glm::i32vec3 position);

		std::unordered_map<int, std::unique_ptr<Entity>>& getEntities();
	private:

		std::unordered_map<int, std::unique_ptr<Entity>> entities;
		std::unordered_map<glm::i32vec3, WorldChunk> chunks;

		friend class Engine;
		friend class RenderChunks;
	};
}