#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <unordered_map>
#include <iostream>

import Sandcore.Render;

import Sandcore.ShaderProgram;

import Sandcore.World;
import Sandcore.Vertex;
import Sandcore.World.Bounds;
import Sandcore.Mesh;
import Sandcore.Cube;

import Sandcore.Framebuffer;

namespace Sandcore {
	Render::Render(Window& window, Event& event, World& world) : window(window), event(event), world(world),
		shader("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/shader/block_shader"),
		texturePackage("C:/Workbench/Sandcore/Sandcore Multimedia/Sandcore Multimedia/Userdata/texture_package") {

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glfwSwapInterval(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_MULTISAMPLE);

		shader.use();
		shader.setdouble("capacity", texturePackage.getCapacity());
	}

	void Render::tick() {
		setUnwantedChunks();
		draw();
		clearUnwantedChunks();

		events();
		input();
	}

	void Render::setUnwantedChunks() {
		for (auto& [position, chunk] : chunks) {
			chunk.setUnwanted();
		}
	}

	void Render::clearUnwantedChunks() {
		std::vector<Vector3D<int>> unwantedChunks;

		for (auto& [position, chunk] : chunks) {
			if (!chunk.isWanted()) unwantedChunks.push_back(position);
		}

		for (auto& position : unwantedChunks) {
			chunks.erase(position);
		}
	}

	void Render::events() {
		while (window.pollEvent(event))
		{
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

					std::cout << "switched camera\n";
				}
			}

			if (event.type == Event::Type::window) {

			}
		}
	}

	void Render::input() {
		if (spectator) {
			camera.keyboardInput(window);
		}
		if (!mouse) camera.mouseInput(window);
	}


	void Render::draw() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texturePackage.bindBlocks();
		shader.use();

		static int prevWidth = 0, prevHeight = 0;
		int width, height;
		window.getSize(&width, &height);

		if (prevWidth != width || prevHeight != height) {
			glViewport(0, 0, width, height);
			prevWidth = width;
			prevHeight = height;
		}

		shader.setMat4("projection", camera.getProjMatrix(width, height));
		shader.setMat4("view", camera.getViewMatrix());

		drawBlocks();

		window.swapBuffers();
	}

	bool Render::isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, bool transparent) {
		bounds<World::Chunk::size>(worldPosition, chunkPosition);

		World::Chunk::Block::Identification id = world.getChunk(worldPosition).getBlock(chunkPosition).getId();

		if (!transparent)
		switch (id) {
			case World::Chunk::Block::Identification::vacuum:
			case World::Chunk::Block::Identification::water:
				return false;
			default:
				return true;
		}
		else
		{
			return id != World::Chunk::Block::Identification::vacuum;
		}
	}

	Cube Render::getCube(World::Chunk::Block::Identification identification) {
		using BI = World::Chunk::Block::Identification;
		using TPBI = TexturePackage::BlockIdentification;
		switch (identification) {
		case BI::coalOre:
			return { {(float)TPBI::coalOre, (float)TPBI::coalOre}, {(float)TPBI::coalOre, (float)TPBI::coalOre}, {(float)TPBI::coalOre, (float)TPBI::coalOre} };
		case BI::goldOre:
			return { {(float)TPBI::goldOre, (float)TPBI::goldOre}, {(float)TPBI::goldOre, (float)TPBI::goldOre}, {(float)TPBI::goldOre, (float)TPBI::goldOre} };
		case BI::ironOre:
			return { {(float)TPBI::ironOre,(float)TPBI::ironOre}, {(float)TPBI::ironOre,(float)TPBI::ironOre}, {(float)TPBI::ironOre,(float)TPBI::ironOre} };
		case BI::dirt:
			return { {(float)TPBI::dirt,(float)TPBI::dirt}, {(float)TPBI::dirt,(float)TPBI::dirt}, {(float)TPBI::dirt,(float)TPBI::dirt} };
		case BI::grass:
			return { {(float)TPBI::grassSide, (float)TPBI::grassSide}, {(float)TPBI::grassSide, (float)TPBI::grassSide}, {(float)TPBI::dirt, (float)TPBI::grassTop} };
		case BI::wood:
			return { {(float)TPBI::woodSide,(float)TPBI::woodSide}, {(float)TPBI::woodSide,(float)TPBI::woodSide}, {(float)TPBI::woodTop,(float)TPBI::woodTop} };
		case BI::sand:
			return { {(float)TPBI::sand,(float)TPBI::sand}, {(float)TPBI::sand,(float)TPBI::sand}, {(float)TPBI::sand,(float)TPBI::sand}};
		case BI::water:
			return { {(float)TPBI::waterTop,(float)TPBI::waterTop }, {(float)TPBI::waterTop,(float)TPBI::waterTop}, {(float)TPBI::waterTop,(float)TPBI::waterTop} };
		case BI::stone:
			return { {(float)TPBI::stone,(float)TPBI::stone}, {(float)TPBI::stone,(float)TPBI::stone}, {(float)TPBI::stone,(float)TPBI::stone} };
		case BI::lava:
			return { {(float)TPBI::lava,(float)TPBI::lava}, {(float)TPBI::lava,(float)TPBI::lava}, {(float)TPBI::lava,(float)TPBI::lava} };
		
		default:
			return { {0,0}, {0,0}, {0,0} };
		}
	}

	void Render::generateChunkMesh(Vector3D<int> position) {
		for (int x = 0; x < World::Chunk::size::x; ++x) {
			for (int y = 0; y < World::Chunk::size::y; ++y) {
				for (int z = 0; z < World::Chunk::size::z; ++z) {
					World::Chunk::Block::Identification id = world.getChunk(position).getBlock(x, y, z).getId();
					Mesh<Render::Chunk::Vertex>& chunk = id == World::Chunk::Block::Identification::water ? chunks[position].transparent : chunks[position].solid;

					if (id == World::Chunk::Block::Identification::vacuum) continue;
					bool isTransparent = id == World::Chunk::Block::Identification::water;

					auto cube = getCube(id);

					if (!isBlocked(position, Vector3D<int>(x - 1, y, z), isTransparent)) {
						int offset = chunk.vertices.size();
						float light = 0.85f;


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

					if (!isBlocked(position, Vector3D<int>(x + 1, y, z), isTransparent)) {
						int offset = chunk.vertices.size();
						float light = 0.95f;

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



					if (!isBlocked(position, Vector3D<int>(x, y - 1, z), isTransparent)) {
						int offset = chunk.vertices.size();
						float light = 0.8f;

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

					if (!isBlocked(position, Vector3D<int>(x, y + 1, z), isTransparent)) {
						int offset = chunk.vertices.size();
						float light = 0.9f;

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



					if (!isBlocked(position, Vector3D<int>(x, y, z - 1), isTransparent)) {
						int offset = chunk.vertices.size();
						float light = 0.75f;

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

					if (!isBlocked(position, Vector3D<int>(x, y, z + 1), isTransparent)) {
						int offset = chunk.vertices.size();
						float light = 1.0f;

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

	void Render::drawBlocks() {
		for (int r = 0; r <= renderRadius; ++r) {
			for (int x = -renderRadius; x <= renderRadius; ++x) {
				for (int y = -renderRadius; y <= renderRadius; ++y) {
					for (int z = -renderRadius; z <= renderRadius; ++z) {
						if (x * x + y * y + z * z <= r * r) {
							glm::mat4 model = glm::mat4(1.0f);
							model = glm::translate(model, glm::vec3(World::Chunk::size::x * x, World::Chunk::size::y * y, World::Chunk::size::z * z));
							shader.setMat4("model", model);

							Vector3D<int> position = camera.getWorldPosition() + Vector3D<int>(x, y, z);

							if (chunks.find(position) == chunks.end()) {
								if (world.getChunk(position).loaded &&
									world.getChunk(position + Vector3D<int>(1, 0, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(-1, 0, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(0, 1, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(0, -1, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(0, 0, 1)).loaded &&
									world.getChunk(position + Vector3D<int>(0, 0, -1)).loaded
									)
									generateChunkMesh(position);
							}

							if (chunks.find(position) != chunks.end() ) {
								if (!chunks[position].isDrawSolid) {
									chunks[position].drawSolid();
									chunks[position].isDrawSolid = true;
								}
							}
						}
					}
				}
			}
		}

		glDisable(GL_CULL_FACE);

		for (int r = 0; r <= renderRadius; ++r) {
			for (int x = -renderRadius; x <= renderRadius; ++x) {
				for (int y = -renderRadius; y <= renderRadius; ++y) {
					for (int z = -renderRadius; z <= renderRadius; ++z) {
						if (x * x + y * y + z * z <= r * r) {
							glm::mat4 model = glm::mat4(1.0f);
							model = glm::translate(model, glm::vec3(World::Chunk::size::x * x, World::Chunk::size::y * y, World::Chunk::size::z * z));
							shader.setMat4("model", model);

							Vector3D<int> position = camera.getWorldPosition() + Vector3D<int>(x, y, z);

							if (chunks.find(position) == chunks.end()) {
								if (world.getChunk(position).loaded &&
									world.getChunk(position + Vector3D<int>(1, 0, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(-1, 0, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(0, 1, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(0, -1, 0)).loaded &&
									world.getChunk(position + Vector3D<int>(0, 0, 1)).loaded &&
									world.getChunk(position + Vector3D<int>(0, 0, -1)).loaded
									)
									generateChunkMesh(position);
							}

							if (chunks.find(position) != chunks.end()) {
								if (!chunks[position].isDrawTransparent) {
									chunks[position].drawTransparent();
									chunks[position].isDrawTransparent = true;
								}
							}
						}
					}
				}
			}
		}
		glEnable(GL_CULL_FACE);
	}
}