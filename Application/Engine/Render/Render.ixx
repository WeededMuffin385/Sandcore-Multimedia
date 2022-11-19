#include <unordered_map>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

export module Sandcore.Render;

import Sandcore.Shader.Program;
import Sandcore.Camera;
import Sandcore.World;
import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;
import Sandcore.Mesh;
import Sandcore.TexturePackage;
import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Cube;

import Sandcore.Framebuffer;

import Sandcore.Render.Chunk;
import Sandcore.Render.Camera;

export namespace Sandcore {
	class Render {
	public:
		
	public:
		Render(Window& window, Event& event, World& world);

		void tick();
	private:

		void draw();
		void events();
		void input();

		void drawBlocks();
		void drawBlocks(RenderChunk::Identification identification);

		void updateViewport();

		void generateChunkMesh(Vector3D<int> position);
		bool isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section);

		bool isRelatedChunksLoaded(Vector3D<int> position);

		void clearUnwantedChunks();

		RenderCamera camera;
		ShaderProgram blocksShader;
		TexturePackage texturePackage;
		World& world;

		Window& window;
		Event& event;

		bool mouse = true;
		int renderRadius = 6;

		bool cameraFocus = true;
		bool spectator = false;

		std::unordered_map<Vector3D<int>, RenderChunk, Vector3DHash<int>> chunks;

		friend class Engine;
	};
}