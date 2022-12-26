namespace Sandcore {
	class Render;
	class World;
}

import Sandcore.Render.Chunk;

import Sandcore.Vector3D;

export module Sandcore.Render.ChunkBuilder;

export namespace Sandcore {
	class RenderChunkBuilder {
	public:
		RenderChunkBuilder(World& world);

		void buildRenderChunk(Vector3D<int> position);
	private:

		bool isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section);

		Render& render;
		World& world;
	};
}