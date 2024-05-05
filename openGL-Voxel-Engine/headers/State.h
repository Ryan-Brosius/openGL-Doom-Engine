#pragma once
#ifndef STATE_CLASS_H
#define STATE_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "TextureMap.h"
#include "Shader.h"

class State
{
	public:
		State();
		GLFWwindow* window;
		TextureMap* textureMap = nullptr;

		void generateTextureMap(Shader* shader);

};

#endif
