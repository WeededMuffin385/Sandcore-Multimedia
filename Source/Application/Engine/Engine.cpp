#include <unordered_map>
#include <fstream>
#include <iostream>

#include <asio.hpp>

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

import Sandcore.Vector3D.GLM;

namespace Sandcore {
	Engine::Engine(Window& window, Event& event) : Scene(window, event) , render(window, event, world) {
		while (!connect()) std::cout << "Re-connecting...\n";
	}

	Engine::~Engine() {
	}

	void Engine::update() {
		tps.tick();
		render.update();
		requestChunks();
		recieve();
	}

	void Engine::events() {
		render.events();

		if (event.type == Event::Type::mouse) {
			if (event.mouse.button == GLFW_MOUSE_BUTTON_RIGHT) {
				if (event.mouse.action == GLFW_RELEASE) {
					Vector3D<double> chunkPosition = render.camera.getChunkPosition();
					Vector3D<int> worldPosition = render.camera.getWorldPosition();

					auto vec = render.camera.getFront();

					chunkPosition += Vector3D<double>(vec.x, vec.y, vec.z);

					bounds<WorldChunk::size>(worldPosition, chunkPosition);

					client.connection->send(Sandcore::Message::generateBreakMessage(worldPosition, chunkPosition));
				}
			}
		}
	}

	void Engine::draw() {
		render.draw();
	}

	void Engine::input() {
		render.input();
		creatureControls.input(window, render.camera);
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
		for (auto& [position, chunk] : world.getChunks()) {
			if (!chunk.loadInProgress && (!chunk.loaded || (chunk.drawCount >= 60))) {
				chunk.loadInProgress = true;
				client.connection->send(Message::generateRequestChunkMessage(position));
			}
		}
	}

	void Engine::recieveChunks() {
		std::string data;
		Vector3D<int> position;
		Sandcore::Message::decompileChunkMessage(client.connection->recieve(), position, data);
		world.getChunk(position).upload(data);
		world.getChunk(position).loadInProgress = false;
		world.getChunk(position).loaded = true;
		world.getChunk(position).drawCount = 0;
	}

	void Engine::createEntity(int id) {
		if (world.getEntities().find(id) == world.getEntities().end()) {
			world.getEntities()[id] = std::make_unique<Entity>(Entity());
		}
	}

	void Engine::recieveEntityPosition() {
		int id;
		Vector3D<int> worldPosition;
		Vector3D<double> chunkPosition;

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


		if ((id == yourId) && render.cameraFocus) {
			render.camera.setPosition(worldPosition, chunkPosition + Vector3D<double>(0, 0, world.getEntities()[id]->getSize().z * 0.8));
		}
	}

	void Engine::recieveEntity() {
		int id;
		bool you;
		Vector3D<double> size;
		Message::decompileEntityMessage(client.connection->recieve(), id, you, size);

		createEntity(id);
		world.getEntities()[id]->getSize() = size;
	

		if (you) {
			yourId = id;
		}

		world.getEntities()[id]->loaded = true;
		world.getEntities()[id]->loadInProgress = false;
	}

	void Engine::sendMove() {
		if (creatureControls.isChanged()) {
			client.connection->send(creatureControls.generateMoveMessage());
		}
	}

	void Engine::recieveBlock() {
		Vector3D<int> worldPosition;
		Vector3D<int> chunkPosition;
		Block::Identification id;

		Message::decompileBlockMessage(client.connection->recieve(), worldPosition, chunkPosition, id);
		world.getChunk(worldPosition).setBlock(chunkPosition, Block(id));
	}

	void Engine::recieve() {
		while (!client.connection->empty()) {
			Message::Identification messageIdentification = static_cast<Message::Identification>(client.connection->recieve()[0]);

			switch (messageIdentification) {
			case Message::Identification::text:
				recieveText();
				break;

			case Message::Identification::sending_chunk:
				recieveChunks();
				break;

			case Message::Identification::sending_entity:
				recieveEntity();
				break;

			case Message::Identification::sending_entity_position:
				recieveEntityPosition();
				break;

			case Message::Identification::sending_block:
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