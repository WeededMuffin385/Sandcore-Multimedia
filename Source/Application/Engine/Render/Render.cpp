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

import Sandcore.Graphics.Program;

import Sandcore.World;
import Sandcore.Vertex;
import Sandcore.World.Bounds;
import Sandcore.Graphics.Mesh;
import Sandcore.Cube;
import Sandcore.Print;

import Sandcore.Graphics.Framebuffer;
import Sandcore.Graphics.Canvas;

import Sandcore.Render.Chunk;
import Sandcore.Application.Memory;

import Sandcore.Print;

namespace Sandcore {
	Render::Render(Window& window, Event& event, World& world) : window(window), event(event), world(world),
		screenShader(Memory::shaderScreenPath),
		textures(Memory::texturesPath),
		chunks(world, window, camera, textures) {

		glEnable(GL_DEPTH_TEST);
		

		glEnable(GL_CULL_FACE);
		glfwSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);


		glEnable(GL_MULTISAMPLE);

		using FV = typename Vertex<glm::float32>;

		mesh.vertices = { {0},{1}, {2}, {3} };
		mesh.indices = { 0, 1, 2, 0, 2, 3 };
		mesh.update();

		underwater.loadFromFile(Memory::texturesPath / "blocks/water_3.png");
	}

	Render::~Render() {
		window.toggleCursor(Window::Cursor::Normal);
	}

	void Render::update() {
		chunks.update();
		updateViewport();
	}

	void Render::events() {
		if (event.type == Event::Type::Key && event.key.action == GLFW_PRESS) {
			if (event.key.key == GLFW_KEY_I) {
				if (mouse) window.toggleCursor(Window::Cursor::Disabled);
				if (!mouse) window.toggleCursor(Window::Cursor::Normal);

				camera.setFirst();
				mouse = !mouse;
			}

			if (event.key.key == GLFW_KEY_HOME) {
				spectator = !spectator;
			}

			if (!chunks.resolution.dynamic) {
				if (event.key.key == GLFW_KEY_EQUAL) {

					chunks.resolution.quality *= 2;
					chunks.framebuffer.resize(chunks.window.getSize().x * chunks.resolution.quality,
						chunks.window.getSize().y * chunks.resolution.quality);
				}

				if (event.key.key == GLFW_KEY_MINUS) {
					chunks.resolution.quality /= 2;

					chunks.framebuffer.resize(chunks.window.getSize().x * chunks.resolution.quality,
						chunks.window.getSize().y * chunks.resolution.quality);
				}
			}

			if (event.key.key == GLFW_KEY_SLASH) {
				chunks.framebuffer.toggle();
			}

			if (event.key.key == GLFW_KEY_BACKSLASH) {
				chunks.resolution.dynamic = !chunks.resolution.dynamic;
			}
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
		auto size = window.getSize();

		// auto view-porting

		if (prevWidth != size.x || prevHeight != size.y) {
			window.viewport(size.x, size.y);
			prevWidth = size.x;
			prevHeight = size.y;
		}
	}

	void Render::draw() {
		window.clear(0.52734375f, 0.8046875f, 0.91796875f);

		chunks.draw();
		drawScreenEffects();

		window.display();
	}

	void Render::drawScreenEffects() {
		drawUnderwaterEffect();
	}

	void Render::drawUnderwaterEffect() {
		if (world.getChunk(camera.getWorldPosition()).getBlock(camera.getChunkPosition()).getId() == Block::Identification::Water) {
			glDisable(GL_DEPTH_TEST);
			window.draw(mesh, screenShader, underwater);
			glEnable(GL_DEPTH_TEST);
		} // else std::print()
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