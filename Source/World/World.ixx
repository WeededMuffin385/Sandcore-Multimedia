#include <unordered_map>
#include <memory>

export module Sandcore.World;

import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;

import Sandcore.World.Entity;

export namespace Sandcore {
	class World {
	public:
		class Chunk {
		public:
			class Block {
			public:
				enum class Identification : unsigned char {
					vacuum,
					grass,
					stone,
					dirt,
					water,
					sand,
					wood,

					lava,

					ironOre,
					coalOre,
					goldOre,

					size
				};

				Block(Identification identification = Identification::vacuum);

				Identification getId();

			private:

				Identification identification;
			};
		public:
			Chunk();

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
	public:

		Chunk& getChunk(int x, int y, int z);
		Chunk& getChunk(Vector3D<int> position);

		std::unordered_map<int, std::unique_ptr<Entity>>& getEntities();
		std::unordered_map<Vector3D<int>, Chunk, Vector3DHash<int>>& getChunks();

	private:

		std::unordered_map<int, std::unique_ptr<Entity>> entities;
		std::unordered_map<Vector3D<int>, Chunk, Vector3DHash<int>> chunks;
	};
}