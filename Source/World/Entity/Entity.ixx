module;
#include <glm/glm.hpp>
export module Sandcore.World.Entity;

export namespace Sandcore {
	class Entity {
	public:
		enum class Identification : unsigned char {
			vacuum,
			human,
			elephant
		};

		glm::ivec3& getWorldPosition();
		glm::fvec3& getChunkPosition();
		glm::fvec3& getSize();

		Identification& getId();

		bool loaded = false;
		bool loadInProgress = false;
	private:

		glm::ivec3    worldPosition; // позиция игрока относительно чанков
		glm::fvec3    chunkPosition; // позиция игрока в чанке.
		glm::fvec3    size = { 0.95f, 0.95f ,0.95f };

		Identification	identification = Identification::human;
	};
}