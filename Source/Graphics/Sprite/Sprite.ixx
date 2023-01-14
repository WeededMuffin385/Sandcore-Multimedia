export module Sandcore.Sprite;

import Sandcore.Graphics.Texture2D;
import Sandcore.Mesh;
import Sandcore.Interface.Vertex;
import Sandcore.Graphics.Draw.Object;

export namespace Sandcore {
	class Sprite {
	public:
		virtual void draw();

	private:
		double x;
		double y;
		double width;
		double height;

		Mesh<InterfaceVertex> mesh;
		Texture2D& texture;
	};
}