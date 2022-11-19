#include <asio.hpp>
#include <iostream>
#include <array>
#include <sstream>
#include <cstdint>

import Sandcore.Client;

import Sandcore.Byte;

namespace Sandcore {
	Client::Client() : resolver(ioContext) {
		connection = Connection::create(ioContext);
	}

	Client::~Client() {
		stop();
		connection.reset(); // два часа я думал, как пофиксить эту херь с exception'ом... это 3.14здец, оказалось, что необходимо вызывать деструкторы объектов asio до вызова деструктора ioContext
	}

	void Client::start() {
		
		connection->loop();

		try {
			thread = std::thread([this]() { ioContext.run(); });
		}
		catch (std::exception& e) {
			if (debug) {
				std::cerr << "[CLIENT] Exception: " << e.what() << "\n";
			}
		}
		if (debug) {
			std::cout << "[CLIENT] Started!\n";
		}
	}

	void Client::stop() {
		ioContext.stop();

		if (thread.joinable())
			thread.join();

		if (debug) {
			std::cout << "[CLIENT] Stopped!\n";
		}
	}

	bool Client::connect(std::string address, std::string port) {
		try {
			asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(address, port);

			if (debug) {
				std::cout << "[CLIENT] Endpoints:\n";
				for (auto a : endpoints) {
					std::cout << ">>>>>>>> " << a.endpoint() << "\n";
				}
			}

			asio::connect(connection->socket, endpoints);
		}
		catch (std::exception& e) {
			if (debug) {
				std::cout << "[CLIENT] Connection failed! " << e.what() << "\n";
			}

			return false;
		}

		if (debug) {
			std::cout << "[CLIENT] Connection succeeded!\n";
		}
		return true;
	}
}