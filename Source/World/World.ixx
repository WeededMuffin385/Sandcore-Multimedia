#include <unordered_map>
#include <memory>

export module Sandcore.World;

import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;

import Sandcore.World.Entity;

import Sandcore.World.Block;

import Sandcore.World.Chunk;

export namespace Sandcore {
	class World {
	public:
		WorldChunk& getChunk(int x, int y, int z);
		WorldChunk& getChunk(Vector3D<int> position);

		std::unordered_map<int, std::unique_ptr<Entity>>& getEntities();
	private:

		std::unordered_map<int, std::unique_ptr<Entity>> entities;
		std::unordered_map<Vector3D<int>, WorldChunk, Vector3DHash<int>> chunks;

		friend class Engine;
	};
}