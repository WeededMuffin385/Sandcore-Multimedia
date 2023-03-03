module;
#include <unordered_map>
#include <glm/glm.hpp>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
export module Sandcore.Render;

import Sandcore.Window;
import Sandcore.Event;

import Sandcore.Render.Chunk;
import Sandcore.Render.Camera;

import Sandcore.Shader.Program;
import Sandcore.Render.Textures;
import Sandcore.World;

import Sandcore.Graphics.Texture2D;
import Sandcore.Mesh;

import Sandcore.Vertex;

import Sandcore.Framebuffer;

import Sandcore.Render.Chunks;

export namespace Sandcore {
	class Render {
	public:
		Render(Window& window, Event& event, World& world);
		~Render();
	private:

		void draw();
		void input();
		void events();
		void update();

		void drawScreenEffects();
		void drawUnderwaterEffect();

		void updateViewport();

		RenderChunks chunks;
		RenderCamera camera;
		ShaderProgram screenShader;
		RenderTextures textures;
		World& world;

		Texture2D underwater;
		Mesh<Vertex<glm::float32>> mesh;

		Window& window;
		Event& event;

		bool mouse = true;
		bool spectator = false;

		friend class Engine;
	};
}