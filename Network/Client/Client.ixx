#include <asio.hpp>
#include <memory>

export module Sandcore.Client;

import Sandcore.ThreadSafeQueue;

import Sandcore.Connection;

import Sandcore.World;

export namespace Sandcore {
	class Client {
	public:

		Client();
		~Client();

		bool connect(std::string address = "", std::string port = "16200");

		void start();
		void stop();

		std::shared_ptr<Connection> connection;

	private:

		bool debug = false;

		World world;

		asio::io_context ioContext;

		asio::ip::tcp::resolver resolver;

		std::thread thread;
	};
}