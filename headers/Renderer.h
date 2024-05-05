#pragma once
#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "Camera.h"
#include "Shader.h"
#include "RenderLinkedList.h"
#include "RenderObject.h"

class Renderer
{
	public:
		Camera* camera;
		Shader* shader;
		RenderLinkedList ObjectContainer = RenderLinkedList();

		Renderer(Camera* camera, Shader* shader);
		void render();
		void addObjects();

		RenderObject* floor_t = nullptr;
};

#endif

