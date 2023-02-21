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
		screenShader("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/Shaders/ScreenShaders"),
		textures("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/TexturePackage"),
		chunks(world, window, camera, textures) {

		glEnable(GL_DEPTH_TEST);
		

		glEnable(GL_CULL_FACE);
		glfwSwapInterval(0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);


		glEnable(GL_MULTISAMPLE);

		using FV = FramebufferVertex;

		mesh.vertices = { {0},{1}, {2}, {3} };
		mesh.indices = { 0, 1, 2, 0, 2, 3 };
		mesh.update();

		underwater.loadFromFile("C:/Users/Mi/Documents/GitHub/Sandcore-Multimedia/Userdata/TexturePackage/blocks/water_3.png");
	}

	void Render::update() {
		chunks.update();
		updateViewport();
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

		chunks.resolution(width, height);
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
		}
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