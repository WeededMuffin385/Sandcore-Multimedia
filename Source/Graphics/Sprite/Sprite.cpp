import Sandcore.Sprite;


namespace Sandcore {
	void Sprite::draw() {
		texture.bind();
		mesh.draw();
	}
}