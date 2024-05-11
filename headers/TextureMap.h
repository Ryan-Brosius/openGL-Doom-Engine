#pragma once
#ifndef TEXTURE_MAP_H
#define TEXTURE_MAP_H

#include <iostream>
#include <filesystem>
#include <map>
#include "Texture.h"
namespace fs = std::filesystem;
#include "Shader.h"

class TextureMap
{
	public:
		static TextureMap& getSingleton(Shader* shader) {
			static TextureMap instance(shader);
			return instance;
		}

		TextureMap(const TextureMap&) = delete;
		TextureMap operator=(TextureMap const&) = delete;

		Texture* get(std::string texture);

	private:
		TextureMap(Shader* shader);

		std::map<std::string, std::shared_ptr<Texture>> map;
		std::string path = "Resource/Textures/";
};

#endif // !TEXTURE_MAP_H