import Sandcore.Render.ChunkBuilder;

import Sandcore.World;
import Sandcore.World.Chunk;
import Sandcore.Render.Chunk;

import Sandcore.Vector3D;
import Sandcore.World.Bounds;

import Sandcore.Mesh;

namespace Sandcore {
	RenderChunkBuilder::RenderChunkBuilder(World& world) : world(world) {
	}

	void extendRenderChunk(Mesh<RenderChunkVertex>& chunk) {
		chunk.vertices.reserve(chunk.vertices.size() + 4);
		chunk.indices.reserve(chunk.indices.size() + 6);
	}

	void RenderChunkBuilder::buildRenderChunk(Vector3D<int> position) {
		chunks[position].clear();
		for (int x = 0; x < WorldChunk::size::x; ++x) {
			for (int y = 0; y < WorldChunk::size::y; ++y) {
				for (int z = 0; z < WorldChunk::size::z; ++z) {
					auto id = world.getChunk(position).getBlock(x, y, z).getId();
					auto section = RenderChunk::getIdentification(id);
					Mesh<RenderChunkVertex>& chunk = chunks[position].meshes[section];

					if (id == Block::Identification::vacuum) continue;

					Cube cube = Cube::getCube(id);

					if (!isBlocked(position, Vector3D<int>(x - 1, y, z), section)) {
						int offset = chunk.vertices.size();
						float light = 0.85f;

						extendRenderChunk(chunk);

						chunk.vertices.push_back({ { x,y,z }, light,cube.x.minus, 2 });
						chunk.vertices.push_back({ { x,y + 1,z }, light,cube.x.minus, 3 });
						chunk.vertices.push_back({ { x,y + 1,z + 1 }, light,cube.x.minus, 0 });
						chunk.vertices.push_back({ { x,y,z + 1 },  light,cube.x.minus, 1 });


						chunk.indices.push_back(offset + 0);
						chunk.indices.push_back(offset + 3);
						chunk.indices.push_back(offset + 2);

						chunk.indices.push_back(offset + 2);
						chunk.indices.push_back(offset + 1);
						chunk.indices.push_back(offset + 0);
					}

					if (!isBlocked(position, Vector3D<int>(x + 1, y, z), section)) {
						int offset = chunk.vertices.size();
						float light = 0.95f;

						extendRenderChunk(chunk);

						chunk.vertices.push_back({ { x + 1,y,z }, light,cube.x.plus, 2 });
						chunk.vertices.push_back({ { x + 1,y + 1,z }, light,cube.x.plus, 3 });
						chunk.vertices.push_back({ { x + 1,y + 1,z + 1 }, light,cube.x.plus, 0 });
						chunk.vertices.push_back({ { x + 1,y,z + 1 }, light,cube.x.plus, 1 });

						chunk.indices.push_back(offset + 0);
						chunk.indices.push_back(offset + 1);
						chunk.indices.push_back(offset + 2);

						chunk.indices.push_back(offset + 2);
						chunk.indices.push_back(offset + 3);
						chunk.indices.push_back(offset + 0);
					}


					if (!isBlocked(position, Vector3D<int>(x, y - 1, z), section)) {
						int offset = chunk.vertices.size();
						float light = 0.8f;

						extendRenderChunk(chunk);

						chunk.vertices.push_back({ { x,y,z }, light,cube.y.minus, 2 });
						chunk.vertices.push_back({ { x + 1,y,z }, light,cube.y.minus, 3 });
						chunk.vertices.push_back({ { x + 1,y,z + 1 }, light,cube.y.minus, 0 });
						chunk.vertices.push_back({ { x,y,z + 1 }, light,cube.y.minus, 1 });

						chunk.indices.push_back(offset + 0);
						chunk.indices.push_back(offset + 1);
						chunk.indices.push_back(offset + 2);

						chunk.indices.push_back(offset + 2);
						chunk.indices.push_back(offset + 3);
						chunk.indices.push_back(offset + 0);
					}

					if (!isBlocked(position, Vector3D<int>(x, y + 1, z), section)) {
						int offset = chunk.vertices.size();
						float light = 0.9f;

						extendRenderChunk(chunk);

						chunk.vertices.push_back({ { x,y + 1,z }, light,cube.y.plus, 2 });
						chunk.vertices.push_back({ { x + 1,y + 1,z }, light,cube.y.plus, 3 });
						chunk.vertices.push_back({ { x + 1,y + 1,z + 1 }, light,cube.y.plus, 0 });
						chunk.vertices.push_back({ { x,y + 1,z + 1 }, light,cube.y.plus, 1 });

						chunk.indices.push_back(offset + 0);
						chunk.indices.push_back(offset + 3);
						chunk.indices.push_back(offset + 2);

						chunk.indices.push_back(offset + 2);
						chunk.indices.push_back(offset + 1);
						chunk.indices.push_back(offset + 0);
					}



					if (!isBlocked(position, Vector3D<int>(x, y, z - 1), section)) {
						int offset = chunk.vertices.size();
						float light = 0.75f;

						extendRenderChunk(chunk);

						chunk.vertices.push_back({ { x ,y ,z }, light,cube.z.minus, 0 });
						chunk.vertices.push_back({ { x ,y + 1 ,z }, light,cube.z.minus, 1 });
						chunk.vertices.push_back({ { x + 1 ,y + 1 ,z }, light,cube.z.minus, 2 });
						chunk.vertices.push_back({ { x + 1,y ,z }, light,cube.z.minus, 3 });

						chunk.indices.push_back(offset + 0);
						chunk.indices.push_back(offset + 1);
						chunk.indices.push_back(offset + 2);

						chunk.indices.push_back(offset + 2);
						chunk.indices.push_back(offset + 3);
						chunk.indices.push_back(offset + 0);
					}

					if (!isBlocked(position, Vector3D<int>(x, y, z + 1), section)) {
						int offset = chunk.vertices.size();
						float light = 1.0f;

						extendRenderChunk(chunk);

						chunk.vertices.push_back({ { x ,y ,z + 1 }, light,cube.z.plus, 0 });
						chunk.vertices.push_back({ { x ,y + 1 ,z + 1 }, light,cube.z.plus, 1 });
						chunk.vertices.push_back({ { x + 1 ,y + 1 ,z + 1 }, light,cube.z.plus, 2 });
						chunk.vertices.push_back({ { x + 1,y ,z + 1 }, light,cube.z.plus, 3 });

						chunk.indices.push_back(offset + 0);
						chunk.indices.push_back(offset + 3);
						chunk.indices.push_back(offset + 2);

						chunk.indices.push_back(offset + 2);
						chunk.indices.push_back(offset + 1);
						chunk.indices.push_back(offset + 0);
					}
				}
			}
		}

		chunks[position].update();
	}

	bool RenderChunkBuilder::isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section) {
		bounds<WorldChunk::size>(worldPosition, chunkPosition);

		Block::Identification id = world.getChunk(worldPosition).getBlock(chunkPosition).getId();

		if (section == RenderChunk::Identification::transparent && id != Block::Identification::vacuum) return true;
		if (id == Block::Identification::vacuum) return false;
		return section == RenderChunk::getIdentification(id);
	}
}