#include <unordered_map>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

export module Sandcore.Render;

import Sandcore.ShaderProgram;
import Sandcore.Camera;
import Sandcore.World;
import Sandcore.Vector3D;
import Sandcore.Vector3D.Hash;
import Sandcore.Mesh;
import Sandcore.TexturePackage;
import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Framebuffer;
import Sandcore.Cube;

export namespace Sandcore {
	class Render {
	public:
		class Chunk {
		public:
			class Vertex {
			public:
				glm::vec3 pos;
				glm::float32 shade;
				glm::float32 texId;
				glm::float32 index;

				static void setAttributeDescriptions();
			};
		public:
			void update();

			void drawSolid();
			void drawTransparent();

			bool isWanted();
			void setUnwanted();

			bool isDrawSolid = false;
			bool isDrawTransparent = false;
			bool isLoaded = false;

			Mesh<Render::Chunk::Vertex> solid;
			Mesh<Render::Chunk::Vertex> transparent;
		};
	public:
		class Camera : public Sandcore::Camera {
		public:
			Vector3D<int> getWorldPosition() { return worldPosition; }
			Vector3D<double> getChunkPosition() { return Vector3D<double>(position.x, position.y, position.z); }

			void setWorldPosition(Vector3D<int> worldPosition) { this->worldPosition = worldPosition; }
			void setChunkPosition(Vector3D<double> chunkPosition) { position.x = chunkPosition.x; position.y = chunkPosition.y; position.z = chunkPosition.z; }

			virtual Vector3D<double> getDirection(Window& window);

			virtual void mouseInput(Window& window);
			virtual void keyboardInput(Window& window);

		private:
			virtual void updateVectors();


			Vector3D<int> worldPosition;

			glm::vec3 front2D;
			glm::vec3 right2D;
		};
	public:

		Render(Window& window, Event& event, World& world);

		void tick();

	private:

		void events();
		void input();

		void drawBlocks();

		void generateChunkMesh(Vector3D<int> position);
		bool isBlocked(Vector3D<int> worldPosition, Vector3D<int> chunkPosition, bool transparent);

		Cube getCube(World::Chunk::Block::Identification identification);

		void draw();

		void setUnwantedChunks();
		void clearUnwantedChunks();

		Camera camera;
		ShaderProgram shader;
		TexturePackage texturePackage;
		World& world;

		Window& window;
		Event& event;

		bool mouse = true;
		int renderRadius = 6;

		bool cameraFocus = false;
		bool spectator = true;

		std::unordered_map<Vector3D<int>, Render::Chunk, Vector3DHash<int>> chunks;

		friend class Engine;
	};
}