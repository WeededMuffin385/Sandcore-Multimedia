module;
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
export module Sandcore.Render.Chunks;

import Sandcore.World.Chunk;
import Sandcore.Render.Chunk;

import Sandcore.Render.Textures;

import Sandcore.World;
import Sandcore.Graphics.Program;

import Sandcore.Window;
import Sandcore.Render.Camera;

import Sandcore.Graphics.Vertex;
import Sandcore.Graphics.Canvas;

import Sandcore.Graphics.Framebuffer;

export namespace Sandcore {
	class RenderChunks {
	public:
		RenderChunks(World& world, Window& window, RenderCamera& camera, RenderTextures& textures);

		void update();
		void draw();

		struct {
			float quality = 1;
			bool dynamic = true;
		} resolution;

	private:
		void draw(RenderChunk::Identification identification);

		void deleteUnwantedChunks();
		void updateWantedChunks();

		void generateChunk(glm::i32vec3 position);
		void generateChunks();

		bool areRelatedChunksLoaded(glm::i32vec3 position);
		bool isBlocked(glm::i32vec3 worldPosition, glm::i32vec3 chunkPosition, RenderChunk::Identification section);
		bool isInRadius(glm::i32vec3 worldPosition);


		RenderTextures& textures;
		RenderCamera& camera;
		Window& window;
		World& world;

		int radius = 8;

		std::unordered_map<glm::i32vec3, RenderChunk> chunks;
		Program shader;

		Framebuffer framebuffer;

	private:
		friend class Engine;
		friend class Render;
	};
}