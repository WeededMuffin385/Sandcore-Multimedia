#include <asio.hpp>

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
		connection->start();

		try {
			thread = std::thread([this]() { ioContext.run(); });
		}
		catch (std::exception& e) {
			if (debug) {
			}
		}
		if (debug) {
		}
	}

	void Client::stop() {
		ioContext.stop();

		if (thread.joinable())
			thread.join();

		if (debug) {
		}
	}

	bool Client::connect(std::string address, std::string port) {
		try {
			asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(address, port);

			if (debug) {
				for (auto a : endpoints) {
				}
			}

			asio::connect(connection->socket, endpoints);
		}
		catch (std::exception& e) {
			if (debug) {
			}

			return false;
		}

		if (debug) {
		}
		return true;
	}
}