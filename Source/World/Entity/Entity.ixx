export module Sandcore.World.Entity;

import Sandcore.Vector3D;

export namespace Sandcore {
	class Entity {
	public:
		enum class Identification : unsigned char {
			vacuum,
			human,
			elephant
		};

		Vector3D<int>& getWorldPosition();
		Vector3D<double>& getChunkPosition();
		Vector3D<double>& getSize();

		Identification& getId();

		bool loaded = false;
		bool loadInProgress = false;
	private:

		Vector3D<int>			worldPosition;	// позиция игрока относительно чанков
		Vector3D<double>		chunkPosition; // позиция игрока в чанке.
		Vector3D<double>		size = { 0.95f, 0.95f ,0.95f };

		Identification	identification = Identification::human;
	};
}