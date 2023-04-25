module;
#include <asio.hpp>
#include <filesystem>
#include <fstream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
export module Sandcore.MainMenu;

import Sandcore.Scene;
import Sandcore.Interface.Component;
import Sandcore.Interface.Button;
import Sandcore.Graphics.Program;
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
			window.viewport(window.getSize().x, window.getSize().y);
			window.clear(0.8828125, 0.82421875, 0.41796875);
			window.draw(affiche, shader);
			window.draw(connect, shader);
			window.draw(create, shader);
			window.draw(settings, shader);
			window.display();
		}

		virtual void input() {
		}

		virtual void events() {
			if (event.type == Event::Type::Mouse)
			if (event.mouse.action == GLFW_PRESS)
			if (event.mouse.button == GLFW_MOUSE_BUTTON_LEFT) {
				if (connect.collide(window)) {
					push(new ConnectMenu(window, event, scenes));
					std::print("Clicked on \"Connect\" button\n");
				}

				if (create.collide(window)) {
					std::print("Clicked on \"Create\" button\n");
				}

				if (settings.collide(window)) {
					std::print("Clicked on \"Settings\" button\n");
				}
			}
		}

		virtual void update() {
			float k, x, y;
			if (window.getSize().x < window.getSize().y) {
				k = (float)window.getSize().x / (float)window.getSize().y;
				x = 0.04f;
				y = x * k;
			} else {
				k = (float)window.getSize().y / (float)window.getSize().x;
				y = 0.04f;
				x = y * k;
			}

			glm::vec2 rect = glm::vec2((1 - 4 * x) / 3.f , (1.f - y * 3) / 4.f);

			affiche.setPosition(glm::vec2(x, y * 2 + rect.y));
			affiche.setSize(glm::vec2(1 - 2 * x, 1 - rect.y - y * 3));

			connect.setPosition(glm::vec2(x, y));
			connect.setSize(rect);

			create.setPosition(glm::vec2(x * 2 + rect.x, y));
			create.setSize(rect);
			
			settings.setPosition(glm::vec2(x * 3 + rect.x * 2, y));
			settings.setSize(rect);
		}

		Program shader;

		Interface::Component affiche;

		Interface::Button connect;	//
		Interface::Button create;	// Buttons
		Interface::Button settings;	//
	};
}