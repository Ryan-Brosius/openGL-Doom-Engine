#pragma once
#ifndef GFX_OBJECT_FACTORY_H
#define GFX_OBJECT_FACTORY_H

#include "RenderObject.h"
#include <glad/glad.h>
#include <memory>
#include "DoubleLinkedList.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "LinearAlgebraUtils.h"

class GFXObjectFactory
{
	public:
		static RenderObject* createWall(GLfloat* vertices, Shader* shader, const char* texture, bool flatten_texture);
		static GLuint* triangulate(glm::vec3* vertices, int length);
		static GLfloat* createVertexArray(glm::vec3* vertices, int length);

	private:
};

#endif
