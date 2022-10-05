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


namespace Sandcore {
	Engine::Engine(Window& window, Event& event) : window(window), event(event), render(window, event, world) {
		client.connect("127.0.0.1", "16200");
		client.start();

		client.connection->send(Sandcore::Message::generateRegistrationMessage("1", "1", "1"));
		client.connection->send(Sandcore::Message::generateAuthorisationMessage("1", "1"));
	}

	Engine::~Engine() {
	}

	void Engine::tick() {
		render.tick();

		draw();
		events();
		input();

		requestChunks();
		recieveMessages();
	}

	void Engine::resize() {
	}

	void Engine::input() {
		controls.input(window, render.camera);
		if (!render.spectator) sendMove();
	}

	void Engine::events() {
	}

	void Engine::draw() {
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

	void Engine::recieveEntity() {
		Vector3D<int> worldPosition;
		Vector3D<double> chunkPosition;
		bool isYou;
		int id;
		Message::decompileEntityMessage(client.connection->recieve(), worldPosition, chunkPosition, isYou, id);
		if (world.getEntities().find(id) == world.getEntities().end()) {
			world.getEntities()[id] = std::make_unique<Entity>(Entity());
		}
		world.getEntities()[id]->getWorldPosition() = worldPosition;
		world.getEntities()[id]->getChunkPosition() = chunkPosition;

		if (isYou && render.cameraFocus) {
			chunkPosition.z += world.getEntities()[id]->getSize().z - 0.05f;
			render.camera.setChunkPosition(chunkPosition);
			render.camera.setWorldPosition(worldPosition);
		}
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
			}

			client.connection->pop();
		}
	}
}