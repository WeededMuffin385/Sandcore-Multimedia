#include <filesystem>

export module Sandcore.Application.Memory;

export namespace Sandcore {
	namespace Memory {
		std::filesystem::path shaderBlockPath = std::filesystem::current_path() / "Userdata/Shaders/ShaderBlock";
		std::filesystem::path shaderScreenPath = std::filesystem::current_path() / "Userdata/Shaders/ShaderScreen";
		std::filesystem::path texturesPath = std::filesystem::current_path() / "Userdata/TexturePackage";
	};
}