module;
#include <unordered_map>
export module Sandcore.Render.Chunks;

import Sandcore.World.Chunk;
import Sandcore.Render.Chunk;

import Sandcore.Render.Textures;

import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;

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

		void generateChunk(Vector3D<int> position);
		void generateChunks();

		bool areRelatedChunksLoaded(Vector3D<int> position);
		bool isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section);
		bool isInRadius(Vector3D<int> worldPosition);


		RenderTextures& textures;
		RenderCamera& camera;
		Window& window;
		World& world;

		int radius = 8;

		std::unordered_map<Vector3D<int>, RenderChunk, Vector3DHash<int>> chunks;
		Program shader;

		Framebuffer framebuffer;

	private:
		friend class Engine;
		friend class Render;
	};
}