module;
#include <thread>
#include <atomic>
#include <memory>
#include <asio.hpp>
#include <filesystem>
#include <glm/glm.hpp>
export module Sandcore.ConnectMenu;

import Sandcore.Scene;
import Sandcore.Interface.Button;
import Sandcore.Shader.Program;
import Sandcore.Application.Memory;
import Sandcore.Engine;
import Sandcore.Event;

export namespace Sandcore {
	class ConnectMenu : public Scene {
	public:
		ConnectMenu(Window& window, Event& event, Scenes& scenes) : Scene(window, event, scenes), shader(Memory::shaderInterfacePath), engine(new Engine(window, event, scenes)) {
			thread = std::thread(
				[this] {
					while (!engine->connect() && run);
					ready = true;
				}
			);
		}

		~ConnectMenu() {
			if (thread.joinable()) thread.join();

			Event trash;
			while (window.pollEvent(trash));
		}

	protected:
		virtual void draw() {
			window.viewport(window.size().x, window.size().y);
			window.clear(1, 1, 0, 1);
			window.draw(back, shader);
			window.display();
		}

		virtual void input() {
			if (back.click(window)) {
				run = false;
			}
		}

		virtual void events() {

		}

		virtual void update() {
			back.position = glm::vec2(0.1, 0.1);
			back.size = glm::vec2(0.8, 0.2);

			if (ready && thread.joinable()) {
				thread.join();
				scenes.push(std::move(engine));
				run = false;
			}
		}

		std::thread thread;
		ShaderProgram shader;
		Interface::Button back;
		std::atomic<bool> ready = false;
		std::unique_ptr<Engine> engine;
	};
}