import Sandcore.Render;

import Sandcore.Mesh;
import Sandcore.Vertex;

namespace Sandcore {
	void Render::Chunk::update() {
		solid.update();
		transparent.update();
		isLoaded = true;
	}

	void Render::Chunk::drawSolid() {
		solid.draw();
	}

	void Render::Chunk::drawTransparent() {
		transparent.draw();
	}

	bool Render::Chunk::isWanted() {
		return isDrawSolid && isDrawTransparent;
	}

	void Render::Chunk::setUnwanted() {
		isDrawSolid = false;
		isDrawTransparent = false;
	}
}