#include <iostream>

export module Sandcore.Engine;

import Sandcore.Render;
import Sandcore.World;
import Sandcore.Client;
import Sandcore.Clock;
import Sandcore.World.Entity;
import Sandcore.Event;
import Sandcore.Window;
import Sandcore.Controls;

export namespace Sandcore {
	class Engine {
	public:
		Engine(Window& window, Event& event);
		~Engine();

		void tick();

		virtual void draw();
		virtual void resize();

		virtual void input();
		virtual void events();

	private:
		void requestChunks();
		void recieveChunks();

		void recieveEntity();

		void sendMove();

		void recieveMessages();

		Client client;
		Clock clock;
		World world;
		Controls controls;

		Render render;

		Window& window;
		Event& event;
	};
}