module;
#include <filesystem>
#include <fstream>

#include <asio.hpp>
export module Sandcore.Engine;

import Sandcore.Render;
import Sandcore.TPS;
import Sandcore.World;
import Sandcore.World.Block;
import Sandcore.Client;
import Sandcore.Clock;
import Sandcore.World.Entity;
import Sandcore.Event;
import Sandcore.Window;
import Sandcore.Controls;
import Sandcore.Scene;

export namespace Sandcore {
	class Engine : public Scene {
	public:
		Engine(Window& window, Event& event, Scenes& scenes);
		~Engine();


	private:
		virtual void draw();
		virtual void input();
		virtual void update();
		virtual void events();

		bool connect(std::string address = "127.0.0.1", std::string port = "16200", std::string mail = "1", std::string username = "1", std::string password = "1");

		void requestChunks();
		void sendMove();

		void recieve();
		void recieveText();
		void recieveEntity();
		void recieveEntityPosition();
		void recieveChunks();
		void recieveBlock();

		void createEntity(int id);

		void breakBlock();
		void placeBlock();
		void captureBlock();

		Block::Identification currentBlockID = Block::Identification::Stone;

		int distance = 7;
		int precision = 10;
		int currentID = 0;

		TPS tps;

		Client client;
		World world;
		Controls ñontrols;

		Render render;
	};
}