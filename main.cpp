#include <iostream>

import Sandcore.Application;

using namespace Sandcore;

int main() {
	std::cout << "Engine version: DATE[" __DATE__ "] TIME[" __TIME__ "]\n";

	Application application;
	application.loop();
}