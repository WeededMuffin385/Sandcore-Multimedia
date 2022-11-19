#include <unordered_map>
#include <iostream>
#include <fstream>

import Sandcore.Engine;

import Sandcore.Message;
import Sandcore.World;
import Sandcore.Clock;
import Sandcore.Window;
import Sandcore.Event;
import Sandcore.Client;
import Sandcore.Render;
import Sandcore.Render.Camera;


namespace Sandcore {
	Engine::Engine(Window& window, Event& event) : Scene(window, event) , render(window, event, world) {
		while (!connect());
	}

	Engine::~Engine() {
	}

	void Engine::tick() {
		tps.tick();
		render.tick();

		draw();
		events();
		input();

		requestChunks();
		recieveMessages();
	}

	void Engine::events() {
	}

	void Engine::draw() {
	}

	void Engine::input() {
		controls.input(window, render.camera);
		if (!render.spectator) sendMove();
	}

	bool Engine::connect(std::string address, std::string port, std::string mail, std::string username, std::string password) {
		if (!client.connect(address, port)) {
			std::cout << "Connection failed, trying re-connect!\n";
			return false;
		}
		std::cout << "You succesfuly connected!\n";

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
			render.camera.setChunkPosition(chunkPosition + Vector3D<double>(0, 0, world.getEntities()[id]->getSize().z * 0.8));
			render.camera.setWorldPosition(worldPosition);
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
		if (controls.isChanged()) {
			client.connection->send(controls.generateMoveMessage());
		}
	}

	void Engine::recieveMessages() {
		while (!client.connection->empty()) {
			Message::Identification messageIdentification = static_cast<Message::Identification>(client.connection->recieve()[0]);


			switch (messageIdentification) {
				case Message::Identification::sending_chunk: {
					recieveChunks();
					break;
				}
				case Message::Identification::sending_entity: {
					recieveEntity();
					break;
				}

				case Message::Identification::sending_entity_position: {
					recieveEntityPosition();
					break;
				}
			}

			client.connection->pop();
		}
	}
}