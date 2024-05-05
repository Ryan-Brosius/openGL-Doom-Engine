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
		TextureMap(Shader* shader);
		Texture* get(std::string texture);

	private:
		std::map<std::string, std::shared_ptr<Texture>> map;
		std::string path = "Resource/Textures/";
};

#endif // !TEXTURE_MAP_H
