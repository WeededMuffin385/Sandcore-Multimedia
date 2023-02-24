#include <unordered_map>
#include <chrono>
#include <list>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Sandcore.Render.Chunks;

import Sandcore.World;
import Sandcore.Shader.Program;

import Sandcore.World.Chunk;
import Sandcore.Render.Chunk;

import Sandcore.World.Bounds;
import Sandcore.Cube;

namespace Sandcore {
	RenderChunks::RenderChunks(World& world, Window& window , RenderCamera& camera, RenderTextures& textures) : world(world), window(window), camera(camera), textures(textures), shader("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/Shaders/BlockShaders") {
		shader.use();
		shader.setDouble("capacity", textures.getCapacity());
	}

	void RenderChunks::update() {
		clearUnwantedChunks();
		checkChunks();
	}

	void RenderChunks::resolution(int width, int height) {
		shader.setMat4("projection", camera.getProjMatrix(width, height)); // uniform doesn't changes from call to call
	}

	void RenderChunks::draw() {
		shader.use();
		shader.setMat4("view", camera.getViewMatrix());

		draw(RenderChunk::Identification::opaque);

		glDisable(GL_CULL_FACE);
		draw(RenderChunk::Identification::leaves);
		glDepthFunc(GL_ALWAYS);
		draw(RenderChunk::Identification::transparent);
		glDepthFunc(GL_LESS);
		draw(RenderChunk::Identification::leaves);
		glEnable(GL_CULL_FACE);


		draw(RenderChunk::Identification::opaque);
	}

	bool RenderChunks::isRelatedChunksLoaded(Vector3D<int> position) {
		return world.getChunk(position).loaded
			&& world.getChunk(position + Vector3D(1, 0, 0)).loaded
			&& world.getChunk(position - Vector3D(1, 0, 0)).loaded
			&& world.getChunk(position + Vector3D(0, 1, 0)).loaded
			&& world.getChunk(position - Vector3D(0, 1, 0)).loaded
			&& world.getChunk(position + Vector3D(0, 0, 1)).loaded
			&& world.getChunk(position - Vector3D(0, 0, 1)).loaded;
	}

	void RenderChunks::checkChunks() {
		for (int r = 0; r <= radius; ++r) 
		for (int x = -radius; x <= radius; ++x)
		for (int y = -radius; y <= radius; ++y)
		for (int z = -radius; z <= radius; ++z) {
			if (x * x + y * y + z * z <= r * r) {
				auto position = camera.getWorldPosition() + Vector3D(x, y, z);
					if (!chunks.contains(position) || world.getChunk(position).changed) {
					if (isRelatedChunksLoaded(position)) {
						generateChunk(position);
						world.getChunk(position).changed = false;
					}
				}
			}
		}
	}

	bool RenderChunks::isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section) {
		bounds<WorldChunk::size>(worldPosition, chunkPosition);

		Block::Identification id = world.getChunk(worldPosition).getBlock(chunkPosition).getId();

		if (section == RenderChunk::Identification::transparent && id != Block::Identification::Vacuum) return true;
		if (id == Block::Identification::Vacuum) return false;
		return section == RenderChunk::getIdentification(id);
	}

	void RenderChunks::extendRenderChunk(Mesh<RenderChunkVertex>& chunk) {
		chunk.vertices.reserve(chunk.vertices.size() + 4 * 6);
		chunk.indices.reserve(chunk.indices.size() + 6 * 6);
	}

	void RenderChunks::generateChunk(Vector3D<int> position) {
		chunks[position].clear();
		for (int x = 0; x < WorldChunk::size::x; ++x)
		for (int y = 0; y < WorldChunk::size::y; ++y)
		for (int z = 0; z < WorldChunk::size::z; ++z) {
			auto id = world.getChunk(position).getBlock(x, y, z).getId();
			auto section = RenderChunk::getIdentification(id);
			Mesh<RenderChunkVertex>& chunk = chunks[position].meshes[section];

			if (id == Block::Identification::Vacuum) continue;

			Cube cube = Cube::getCube(id);

			extendRenderChunk(chunk);

			if (!isBlocked(position, Vector3D<int>(x - 1, y, z), section)) {
				int offset = chunk.vertices.size();
				float light = 0.85f;


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

				chunk.vertices.push_back({ { x + 1,y,z }, light,cube.x.plus, 2});
				chunk.vertices.push_back({ { x + 1,y + 1,z }, light,cube.x.plus, 3});
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

				chunk.vertices.push_back({ { x ,y ,z }, light,cube.z.minus, 0});
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

		chunks[position].update();
	}

	void RenderChunks::clearUnwantedChunks() {
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		std::list<Vector3D<int>> unwantedChunks;

		for (auto& [position, chunk] : chunks) {
			if (chunk.isUnwanted(end)) unwantedChunks.push_back(position);
		}

		for (auto& position : unwantedChunks) {
			chunks.erase(position);
		}
	}

	void RenderChunks::draw(RenderChunk::Identification identification) {
		std::unordered_map<Vector3D<int>, bool, Vector3DHash<int>> drawn;

		for (int r = 0; r <= radius; ++r)
		for (int x = -radius; x <= radius; ++x)
		for (int y = -radius; y <= radius; ++y)
		for (int z = -radius; z <= radius; ++z) {
			if (x * x + y * y + z * z <= r * r) {
				auto position = camera.getWorldPosition() + Vector3D<int>(x, y, z);
				if (drawn[position]) continue;
				if (chunks.contains(position)) {
					shader.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(WorldChunk::size::x * x, WorldChunk::size::y * y, WorldChunk::size::z * z)));

					window.draw(chunks[position].meshes[identification], shader, textures.blockTextures);
					drawn[position] = true;
				}
			}
		}
	}
}