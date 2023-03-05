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
import Sandcore.Application.Memory;
import Sandcore.ConnectMenu;

export namespace Sandcore {
	class MainMenu : public Scene {
	public:
		MainMenu(Window& window, Event& event, Scenes& scenes) : Scene(window, event, scenes), shader(Memory::shaderInterfacePath) {
		}


	protected:
		virtual void draw() {
			window.viewport(window.size().x, window.size().y);
			window.clear(0.8828125, 0.82421875, 0.41796875);
			window.draw(affiche, shader);
			window.draw(connect, shader);
			window.draw(create, shader);
			window.draw(settings, shader);
			window.display();
		}

		virtual void input() {
			if (connect.click(window)) {
				push(new ConnectMenu(window, event, scenes));
				std::print("Clicked on \"Connect\" button\n");
			}
		}

		virtual void events() {

		}

		virtual void update() {
			float k, x, y;
			if (window.size().x < window.size().y) {
				k = (float)window.size().x / (float)window.size().y;
				x = 0.04f;
				y = x * k;
			} else {
				k = (float)window.size().y / (float)window.size().x;
				y = 0.04f;
				x = y * k;
			}

			glm::vec2 rect = glm::vec2((1 - 4 * x) / 3.f , (1.f - y * 3) / 4.f);

			affiche.position = glm::vec2(x, y * 2 + rect.y);
			affiche.size = glm::vec2(1 - 2 * x, 1 - rect.y - y * 3);

			connect.position = glm::vec2(x, y);
			connect.size = rect;

			create.position = glm::vec2(x * 2 + rect.x, y);
			create.size = rect;
			
			settings.position = glm::vec2(x * 3 + rect.x * 2, y);
			settings.size = rect;
		}

		ShaderProgram shader;

		Interface::Component affiche;

		Interface::Button connect;	//
		Interface::Button create;	// Buttons
		Interface::Button settings;	//
	};
}