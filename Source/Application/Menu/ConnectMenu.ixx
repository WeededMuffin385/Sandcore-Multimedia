module;
#include <thread>
#include <atomic>
#include <memory>
#include <filesystem>

#include <asio.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
export module Sandcore.ConnectMenu;

import Sandcore.Scene;
import Sandcore.Interface.Button;
import Sandcore.Shader.Program;
import Sandcore.Application.Memory;
import Sandcore.Engine;
import Sandcore.Event;

import Sandcore.Print;

export namespace Sandcore {
	class ConnectMenu : public Scene {
	public:
		ConnectMenu(Window& window, Event& event, Scenes& scenes) : Scene(window, event, scenes), shader(Memory::shaderInterfacePath), engine(new Engine(window, event, scenes)) {
			auto foo = [stop = stop, ready = ready, engine = engine] {
				while (!engine->connect("127.0.0.1", "16200", "1", "1", "1") && !*stop);
				*ready = true;
			};

			thread = std::thread(foo);
		}

		~ConnectMenu() {
			if (thread.joinable()) thread.detach();
		}

	protected:
		virtual void draw() {
			window.viewport(window.size().x, window.size().y);
			window.clear(1, 1, 0, 1);
			window.draw(back, shader);
			window.display();
		}

		virtual void input() {
		}

		virtual void events() {
			if (event.type == Event::Type::Mouse)
			if (event.mouse.action == GLFW_PRESS)
			if (event.mouse.button == GLFW_MOUSE_BUTTON_LEFT)
			if (back.collide(window)) {
				run = false;
				*stop = true;
			}
		}

		virtual void update() {
			back.position = glm::vec2(0.1, 0.1);
			back.size = glm::vec2(0.8, 0.2);

			if (*ready && run) {
				run = false;
				push(engine);
			}
		}

		std::shared_ptr<std::atomic<bool>> stop = std::make_shared<std::atomic<bool>>(false);
		std::shared_ptr<std::atomic<bool>> ready = std::make_shared<std::atomic<bool>>(false);
		std::shared_ptr<Engine> engine;

		std::thread thread;

		ShaderProgram shader;
		Interface::Button back;
	};
}