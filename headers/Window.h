#pragma once
#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Texture.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Camera.h"
#include "RenderObject.h"
#include "Constants.h"
#include "Renderer.h"
#include "State.h"
#include "TextureMap.h"

#include <iostream>

class Window
{
	public:
		GLFWwindow* handle = nullptr;
		Window();
		void setup();
		void window_loop();
		void destroy();
		void update();
		void render();

	private:
		Camera gameCamera = Camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
		Shader* gameShader = nullptr;
		Renderer* gameRenderer = nullptr;

};

#endif

