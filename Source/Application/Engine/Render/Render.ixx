#include <unordered_map>
#include <glm/glm.hpp>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

export module Sandcore.Render;

import Sandcore.Shader.Program;
import Sandcore.Camera;
import Sandcore.World;
import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;
import Sandcore.Mesh;
import Sandcore.Render.Textures;
import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Cube;
import Sandcore.Graphics.Texture2D;

import Sandcore.Framebuffer;
import Sandcore.Framebuffer.Vertex;
import Sandcore.Render.Chunk.Vertex;

import Sandcore.Render.Chunk;
import Sandcore.Render.Camera;

import Sandcore.Render.Chunks;

export namespace Sandcore {
	class Render {
	public:
		Render(Window& window, Event& event, World& world);

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
		Mesh<FramebufferVertex> mesh;

		Window& window;
		Event& event;

		bool mouse = true;
		bool spectator = false;

		friend class Engine;
	};
}