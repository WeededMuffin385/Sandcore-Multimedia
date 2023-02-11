#include <unordered_map>

export module Sandcore.Render.Chunks;

import Sandcore.World.Chunk;
import Sandcore.Render.Chunk;

import Sandcore.Render.Textures;

import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;

import Sandcore.World;
import Sandcore.Shader.Program;

import Sandcore.Window;
import Sandcore.Render.Camera;

export namespace Sandcore {
	class RenderChunks {
	public:
		RenderChunks(World& world, Window& window, RenderCamera& camera, RenderTextures& textures);

		void update();

		void draw();
		void draw(RenderChunk::Identification identification);

		void resolution(int width, int height);

	private:
		void clearUnwantedChunks();
		void checkChunks();
		void extendRenderChunk(Mesh<RenderChunkVertex>& chunk);
		bool isRelatedChunksLoaded(Vector3D<int> position);
		void generateChunk(Vector3D<int> position);
		bool isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, RenderChunk::Identification section);

		RenderTextures& textures;
		RenderCamera& camera;
		Window& window;
		World& world;

		int radius = 6;

		std::unordered_map<Vector3D<int>, RenderChunk, Vector3DHash<int>> chunks;
		ShaderProgram shader;
	};
}