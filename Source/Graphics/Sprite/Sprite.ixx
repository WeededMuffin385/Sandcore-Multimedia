export module Sandcore.Sprite;

import Sandcore.Graphics.Texture2D;
import Sandcore.Mesh;
import Sandcore.Interface.Vertex;

export namespace Sandcore {
	class Sprite {
	public:



	private:
		Mesh<InterfaceVertex> mesh;
		Texture2D& texture;
	};
}