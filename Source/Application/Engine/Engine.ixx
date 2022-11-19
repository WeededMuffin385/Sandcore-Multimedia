#include <iostream>

export module Sandcore.Engine;

import Sandcore.TPS;
import Sandcore.Render;
import Sandcore.World;
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
		Engine(Window& window, Event& event);
		~Engine();

		virtual void tick();

	private:
		void draw();
		void events();
		void input();

		bool connect(std::string address = "127.0.0.1", std::string port = "16200", std::string mail = "1", std::string username = "1", std::string password = "1");

		void requestChunks();
		void recieveChunks();

		void recieveEntity();
		void recieveEntityPosition();

		void sendMove();
		void recieveMessages();

		void createEntity(int id);

		int yourId = 0;

		TPS tps;

		Client client;
		World world;
		Controls controls;

		Render render;
	};
}