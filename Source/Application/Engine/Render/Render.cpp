#include <filesystem>
#include <unordered_map>

#include <chrono>
#include <set>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


import Sandcore.Render;

import Sandcore.Shader.Program;

import Sandcore.World;
import Sandcore.Vertex;
import Sandcore.World.Bounds;
import Sandcore.Mesh;
import Sandcore.Cube;

import Sandcore.Framebuffer;
import Sandcore.Graphics.Draw.Target;
import Sandcore.Framebuffer.Vertex;

import Sandcore.Render.Chunk.Vertex;
import Sandcore.Render.Chunk;

namespace Sandcore {
	Render::Render(Window& window, Event& event, World& world) : window(window), event(event), world(world),
		blocksShader("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/shaders/blocks_shader"),
		screenShader("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/shaders/screen_shader"),
		texturePackage("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/texture_package") {

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glfwSwapInterval(0);
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);


		glEnable(GL_MULTISAMPLE);
		blocksShader.use();
		blocksShader.setDouble("capacity", texturePackage.getCapacity());

		mesh.vertices = { {0}, {1}, {2}, {3} };
		mesh.indices = { 1,0,2,1,2,3 };
		mesh.update();

		underwater.loadFromFile("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/texture_package/blocks/water_3.png");
	}

	void Render::update() {
		updateViewport();
	}

	void Render::clearUnwantedChunks() {
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		std::list<Vector3D<int>> unwantedChunks;

		for (auto& [position, chunk] : chunks) {
			if (chunk.isUnwanted(end)) unwantedChunks.push_back(position);
		}

		for (auto& position : unwantedChunks) {
			chunks.erase(position);
		}
	}

	void Render::events() {
		if (event.type == Event::Type::key && event.key.action == GLFW_PRESS) {
			if (event.key.key == GLFW_KEY_ESCAPE)
				window.close();

			if (event.key.key == GLFW_KEY_I) {
				if (mouse) window.setMouseDisabled();
				if (!mouse) window.setMouseEnabled();

				camera.setFirst();
				mouse = !mouse;
			}

			if (event.key.key == GLFW_KEY_HOME) {
				cameraFocus = !cameraFocus;
				spectator = !spectator;
			}
		}

		if (event.type == Event::Type::window) {

		}
	}

	void Render::input() {
		if (spectator) {
			camera.keyboardInput(window);
		}
		if (!mouse) camera.mouseInput(window);
	}

	void Render::updateViewport() {
		static int prevWidth = 0, prevHeight = 0;
		int width, height;
		window.getSize(&width, &height);

		// auto view-porting

		if (prevWidth != width || prevHeight != height) {
			glViewport(0, 0, width, height);
			prevWidth = width;
			prevHeight = height;
		}

		blocksShader.setMat4("projection", camera.getProjMatrix(width, height)); // uniform doesn't changes from call to call
	}

	void Render::draw() {
		window.clear(0.52734375f, 0.8046875f, 0.91796875f);
		
		drawBlocks();
		drawScreenEffects();

		window.display();

		clearUnwantedChunks();
	}

	void Render::drawBlocks() {
		blocksShader.use();

		blocksShader.setMat4("view", camera.getViewMatrix());

		drawBlocks(RenderChunk::Identification::opaque);
		drawBlocks(RenderChunk::Identification::transparent);
	}

	void Render::drawScreenEffects() {
		drawUnderwaterEffect();
	}

	void Render::drawUnderwaterEffect() {
		if (world.getChunk(camera.getWorldPosition()).getBlock(camera.getChunkPosition()).getId() == Block::Identification::water) {
			glDisable(GL_DEPTH_TEST);
			window.draw(mesh, screenShader, underwater);
			glEnable(GL_DEPTH_TEST);
		}
	}

	bool Render::isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section) {
		bounds<WorldChunk::size>(worldPosition, chunkPosition);

		Block::Identification id = world.getChunk(worldPosition).getBlock(chunkPosition).getId();

		if (section == RenderChunk::Identification::transparent && id != Block::Identification::vacuum) return true;
		if (id == Block::Identification::vacuum) return false;
		return section == RenderChunk::getIdentification(id);
	}

	void extendRenderChunk(Mesh<RenderChunkVertex>& chunk) {
		chunk.vertices.reserve(chunk.vertices.size() + 4);
		chunk.indices.reserve(chunk.indices.size() + 6);
	}

	void Render::generateChunkMesh(Vector3D<int> position) {
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

						chunk.vertices.push_back({ { x,y,z }, light,cube.x.minus, 2  });
						chunk.vertices.push_back({ { x,y + 1,z }, light,cube.x.minus, 3  });
						chunk.vertices.push_back({ { x,y + 1,z + 1 }, light,cube.x.minus, 0  });
						chunk.vertices.push_back({ { x,y,z + 1 },  light,cube.x.minus, 1  });


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

						chunk.vertices.push_back({ { x + 1,y,z }, light,cube.x.plus, 2  });
						chunk.vertices.push_back({ { x + 1,y + 1,z }, light,cube.x.plus, 3  });
						chunk.vertices.push_back({ { x + 1,y + 1,z + 1 }, light,cube.x.plus, 0  });
						chunk.vertices.push_back({ { x + 1,y,z + 1 }, light,cube.x.plus, 1  });

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

						chunk.vertices.push_back({ { x,y,z }, light,cube.y.minus, 2  });
						chunk.vertices.push_back({ { x + 1,y,z }, light,cube.y.minus, 3  });
						chunk.vertices.push_back({ { x + 1,y,z + 1 }, light,cube.y.minus, 0  });
						chunk.vertices.push_back({ { x,y,z + 1 }, light,cube.y.minus, 1  });

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

						chunk.vertices.push_back({ { x,y + 1,z }, light,cube.y.plus, 2  });
						chunk.vertices.push_back({ { x + 1,y + 1,z }, light,cube.y.plus, 3  });
						chunk.vertices.push_back({ { x + 1,y + 1,z + 1 }, light,cube.y.plus, 0  });
						chunk.vertices.push_back({ { x,y + 1,z + 1 }, light,cube.y.plus, 1  });

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

						chunk.vertices.push_back({ { x ,y ,z }, light,cube.z.minus, 0  });
						chunk.vertices.push_back({ { x ,y + 1 ,z }, light,cube.z.minus, 1  });
						chunk.vertices.push_back({ { x + 1 ,y + 1 ,z }, light,cube.z.minus, 2  });
						chunk.vertices.push_back({ { x + 1,y ,z }, light,cube.z.minus, 3  });

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

						chunk.vertices.push_back({ { x ,y ,z + 1 }, light,cube.z.plus, 0  });
						chunk.vertices.push_back({ { x ,y + 1 ,z + 1 }, light,cube.z.plus, 1  });
						chunk.vertices.push_back({ { x + 1 ,y + 1 ,z + 1 }, light,cube.z.plus, 2  });
						chunk.vertices.push_back({ { x + 1,y ,z + 1 }, light,cube.z.plus, 3  });

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

	void Render::drawBlocks(RenderChunk::Identification identification) {
		std::unordered_map<Vector3D<int>, bool, Vector3DHash<int>> drawn;
		DrawTarget& target = window;

		for (int r = 0; r <= renderRadius; ++r) {
			for (int x = -renderRadius; x <= renderRadius; ++x) {
				for (int y = -renderRadius; y <= renderRadius; ++y) {
					for (int z = -renderRadius; z <= renderRadius; ++z) {
						if (x * x + y * y + z * z <= r * r) {
							auto position = camera.getWorldPosition() + Vector3D<int>(x, y, z);
							if (drawn[position]) continue;


							if (chunks.find(position) == chunks.end() || world.getChunk(position).changed) {
								if (isRelatedChunksLoaded(position)) {
									generateChunkMesh(position);
									world.getChunk(position).changed = false;
								}
							}
							

							if (chunks.find(position) != chunks.end()) {
								blocksShader.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(WorldChunk::size::x * x, WorldChunk::size::y * y, WorldChunk::size::z * z)));

								target.draw(chunks[position].meshes[identification], blocksShader, texturePackage.blockTextures);
								drawn[position] = true;
							}
						}
					}
				}
			}
		}
	}

	bool Render::isRelatedChunksLoaded(Vector3D<int> position) {
		return world.getChunk(position).loaded 
			&& world.getChunk(position + Vector3D<int>(1, 0, 0)).loaded
			&& world.getChunk(position + Vector3D<int>(-1, 0, 0)).loaded
			&& world.getChunk(position + Vector3D<int>(0, 1, 0)).loaded
			&& world.getChunk(position + Vector3D<int>(0, -1, 0)).loaded
			&& world.getChunk(position + Vector3D<int>(0, 0, 1)).loaded
			&& world.getChunk(position + Vector3D<int>(0, 0, -1)).loaded;
	}
}

/*
	Парочка правил отрисовки:

	Шаги:
	1) Забиндить текстуры
	2) Заюзать шейдер
	3) Забиндить юниформы
	4) Отрисовать мэш

	Т. К. в отрисовку уже включёно использование шейдера, то:
	1) Забиндить текстуры
	2) Отрисовать мэш (чем?) шейдером
*/