export module Sandcore.World.Entity;

import Sandcore.Vector3D;

import Sandcore.World.Entity.Identification;

export namespace Sandcore {
	class Entity {
	public:
		Vector3D<int>& getWorldPosition();
		Vector3D<double>& getChunkPosition();
		const Vector3D<double>& getSize();

		EntityIdentification& getId();
	private:

		Vector3D<int> worldPosition;	  // позиция игрока, считается в чанках
		Vector3D<double> chunkPosition; // позиция игрока относительно чанка.

		Vector3D<double> size = { 0.95f,0.95f ,0.95f };

		EntityIdentification identification = EntityIdentification::human;
	};
}