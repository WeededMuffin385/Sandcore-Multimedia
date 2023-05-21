#include <unordered_map>
#include <fstream>

#include <asio.hpp>
#include <limits>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


import Sandcore.Engine;

import Sandcore.Message;
import Sandcore.World;
import Sandcore.Clock;
import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Client;
import Sandcore.Render;
import Sandcore.Render.Camera;

import Sandcore.World.Bounds;

import Sandcore.Print;

namespace Sandcore {
	Engine::Engine(Window& window, Event& event, Scenes& scenes) : Scene(window, event, scenes), render(window, event, world) {
	}

	Engine::~Engine() {
		std::print("Engine was deleted!\n");
	}

	void Engine::update() {
		world.tick();

		if (tps.tick()) std::print("World chunks:{} | Render chunks:{}\n", world.chunks.size(), render.chunks.chunks.size());
		render.update();
		requestChunks();
		recieve();
	}

	void Engine::events() {
		render.events();

		if (event.type == Event::Type::Mouse) {
			if (event.mouse.button == GLFW_MOUSE_BUTTON_RIGHT) {
				if (event.mouse.action == GLFW_PRESS) breakBlock();
			}

			if (event.mouse.button == GLFW_MOUSE_BUTTON_LEFT) {
				if (event.mouse.action == GLFW_PRESS) placeBlock();
			}

			if (event.mouse.button == GLFW_MOUSE_BUTTON_MIDDLE) {
				if (event.mouse.action == GLFW_PRESS) captureBlock();
			}
		}

		if (event.type == Event::Type::Key) {
			if (event.key.key == GLFW_KEY_ESCAPE) {
				run = false;
			}
		}
	}

	bool touchable(Block::Identification identification) {
		switch (identification) {
		case Block::Identification::Water:
		case Block::Identification::Vacuum:
			return false;
			
		default:
			return true;
		}
	}

	void Engine::breakBlock() {
		glm::f32vec3 chunkPosition = render.camera.getChunkPosition();
		glm::i32vec3 worldPosition = render.camera.getWorldPosition();

		glm::f32vec3	vec; {
			auto v = render.camera.getFront() ;
			vec = glm::f32vec3(v.x / precision, v.y / precision, v.z / precision);
		}

		for (int i = 0; i < distance * precision; ++i) {
			chunkPosition += glm::f32vec3(vec.x, vec.y, vec.z);
			bounds<WorldChunk::size>(worldPosition, chunkPosition);

			if (touchable(world.getChunk(worldPosition).getBlock(chunkPosition).getId())) {
				client.connection->send(Sandcore::Message::generateBreakMessage(worldPosition, chunkPosition));
				break;
			}
		}
	}

	void Engine::placeBlock() {
		glm::i32vec3		emptyChunkPosition;
		glm::i32vec3		emptyWorldPosition;

		bool found = false;

		glm::f32vec3	chunkPosition = render.camera.getChunkPosition();
		glm::i32vec3		worldPosition = render.camera.getWorldPosition();

		glm::f32vec3	vec; {
			auto v = render.camera.getFront();
			vec = glm::f32vec3(v.x / precision, v.y / precision, v.z / precision);
		}

		for (int i = 0; i < distance * precision; ++i) {
			chunkPosition += vec;
			bounds<WorldChunk::size>(worldPosition, chunkPosition);

			if (!touchable(world.getChunk(worldPosition).getBlock(chunkPosition).getId())) {
				emptyWorldPosition = worldPosition;
				emptyChunkPosition = chunkPosition;
				found = true;
			}

			if (touchable(world.getChunk(worldPosition).getBlock(chunkPosition).getId()) && found) {
				client.connection->send(Sandcore::Message::generatePlaceMessage(emptyWorldPosition, emptyChunkPosition, currentBlockID));
				break;
			}
		}
	}

	void Engine::captureBlock() {
		glm::f32vec3 chunkPosition = render.camera.getChunkPosition();
		glm::i32vec3 worldPosition = render.camera.getWorldPosition();

		glm::f32vec3	vec; {
			auto v = render.camera.getFront();
			vec = glm::f32vec3(v.x / precision, v.y / precision, v.z / precision);
		}

		for (int i = 0; i < distance * precision; ++i) {
			chunkPosition += glm::f32vec3(vec.x, vec.y, vec.z);
			bounds<WorldChunk::size>(worldPosition, chunkPosition);

			if (touchable(world.getChunk(worldPosition).getBlock(chunkPosition).getId())) {
				currentBlockID = world.getChunk(worldPosition).getBlock(chunkPosition).getId();
				break;
			}
		}
	}


	void Engine::draw() {
		render.draw();
	}

	void Engine::input() {
		render.input();
		ñontrols.input(window, render.camera);
		if (!render.spectator) sendMove();
	}

	bool Engine::connect(std::string address, std::string port, std::string mail, std::string username, std::string password) {
		if (!client.connect(address, port)) {
			return false;
		}

		client.start();

		client.connection->send(Sandcore::Message::generateRegistrationMessage(mail, username, password));
		client.connection->send(Sandcore::Message::generateAuthorisationMessage(mail, password));
		return true;
	}

	void Engine::requestChunks() {
		for (auto& [position, chunk] : world.chunks) {
			if (!chunk.loadInProgress && !chunk.loaded) {
				chunk.loadInProgress = true;
				client.connection->send(Message::generateRequestChunkMessage(position));
			}
		}
	}

	void Engine::recieveChunks() {
		std::string data;
		glm::i32vec3 position;
		Sandcore::Message::decompileChunkMessage(client.connection->recieve(), position, data);
		world.getChunk(position).upload(data);
		world.getChunk(position).loadInProgress = false;
		world.getChunk(position).loaded = true;
	}

	void Engine::createEntity(int id) {
		if (!world.getEntities().contains(id)) {
			world.getEntities()[id] = std::make_unique<Entity>(Entity());
		}
	}

	void Engine::recieveEntityPosition() {
		int id;
		glm::i32vec3 worldPosition;
		glm::f32vec3 chunkPosition;

		Message::decompileEntityPositionMessage(client.connection->recieve(), id, worldPosition, chunkPosition);

		createEntity(id);

		if (!world.getEntities()[id]->loaded) {
			if (!world.getEntities()[id]->loadInProgress) {
				client.connection->send(Message::generateRequestEntityMessage(id));
				world.getEntities()[id]->loadInProgress = true;
			}
		} else {
			world.getEntities()[id]->getWorldPosition() = worldPosition;
			world.getEntities()[id]->getChunkPosition() = chunkPosition;
		}


		if ((id == currentID) && !render.spectator) {
			render.camera.setPosition(worldPosition, chunkPosition + glm::f32vec3(0, 0, world.getEntities()[id]->getSize().z * 0.8));
		}
	}

	void Engine::recieveEntity() {
		int id;
		bool you;
		glm::f32vec3 size;
		Message::decompileEntityMessage(client.connection->recieve(), id, you, size);

		createEntity(id);
		world.getEntities()[id]->getSize() = size;
	

		if (you) {
			currentID = id;
		}

		world.getEntities()[id]->loaded = true;
		world.getEntities()[id]->loadInProgress = false;
	}

	void Engine::sendMove() {
		if (ñontrols.isChanged()) {
			client.connection->send(ñontrols.generateMoveMessage());
		}
	}

	void Engine::recieveBlock() {
		glm::i32vec3 worldPosition;
		glm::i32vec3 chunkPosition;
		Block::Identification id;

		Message::decompileBlockMessage(client.connection->recieve(), worldPosition, chunkPosition, id);
		world.getChunk(worldPosition).setBlock(chunkPosition, Block(id));

		if (chunkPosition.x == 0)	world.getChunk(worldPosition - glm::i32vec3(1, 0, 0)).changed = true;
		if (chunkPosition.x == 15)	world.getChunk(worldPosition + glm::i32vec3(1, 0, 0)).changed = true;

		if (chunkPosition.y == 0)	world.getChunk(worldPosition - glm::i32vec3(0, 1, 0)).changed = true;
		if (chunkPosition.y == 15)	world.getChunk(worldPosition + glm::i32vec3(0, 1, 0)).changed = true;

		if (chunkPosition.z == 0)	world.getChunk(worldPosition - glm::i32vec3(0, 0, 1)).changed = true;
		if (chunkPosition.z == 15)	world.getChunk(worldPosition + glm::i32vec3(0, 0, 1)).changed = true;
	}

	void Engine::recieve() {
		while (!client.connection->empty()) {
			Message::Identification messageIdentification = static_cast<Message::Identification>(client.connection->recieve()[0]);

			switch (messageIdentification) {
			case Message::Identification::Text:
				recieveText();
				break;

			case Message::Identification::SendingChunk:
				recieveChunks();
				break;

			case Message::Identification::SendingEntity:
				recieveEntity();
				break;

			case Message::Identification::SendingEntityPosition:
				recieveEntityPosition();
				break;

			case Message::Identification::SendingBlock:
				recieveBlock();
				break;
			}

			client.connection->pop();
		}
	}

	void Engine::recieveText() {
		std::string message;
		Message::decompileTextMessage(client.connection->recieve(), message);
	}
}