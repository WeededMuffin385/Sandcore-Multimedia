module;
#include <asio.hpp>
#include <filesystem>
#include <glm/glm.hpp>
export module Sandcore.MainMenu;

import Sandcore.Scene;
import Sandcore.Interface.Component;
import Sandcore.Interface.Button;
import Sandcore.Shader.Program;
import Sandcore.Print;
import Sandcore.Engine;

export namespace Sandcore {
	class MainMenu : public Scene {
	public:
		MainMenu(Window& window, Event& event, Scenes& scenes) : Scene(window, event, scenes), shader("C:/Workbench/Sphere/Sphere/Userdata/Shaders/Shader/") {
		}


	protected:
		virtual void draw() {
			window.viewport(size.x, size.y);
			window.clear(0.8828125, 0.82421875, 0.41796875);
			window.draw(affiche, shader);
			window.draw(connect, shader);
			window.draw(create, shader);
			window.draw(settings, shader);
			window.display();
		}

		virtual void input() {
			if (connect.click(window)) {
				push(new Engine(window, event, scenes));
				std::printf("Clicked on \"Connect\" button\n");
			}
		}

		virtual void events() {

		}

		virtual void update() {
			size = window.size();
			
			float k, x, y;
			if (size.x < size.y) {
				k = (float)size.x / (float)size.y;
				x = 0.04f;
				y = x * k;
			} else {
				k = (float)size.y / (float)size.x;
				y = 0.04f;
				x = y * k;
			}

			glm::vec2 rect = glm::vec2((1 - 4 * x) / 3.f , (1.f - y * 3) / 3.f);

			affiche.position = glm::vec2(x, rect.y + y * 2);
			affiche.size = glm::vec2(1 - 2 * x, 1 - rect.y - y * 3);

			connect.position = glm::vec2(x, y);
			connect.size = rect;

			create.position = glm::vec2(x * 2 + rect.x, y);
			create.size = rect;
			
			settings.position = glm::vec2(x * 3 + rect.x * 2, y);
			settings.size = rect;
		}

		Window::Size size;

		ShaderProgram shader;

		Interface::Component affiche;

		Interface::Button connect;	//
		Interface::Button create;	// Buttons
		Interface::Button settings;	//
	};
}