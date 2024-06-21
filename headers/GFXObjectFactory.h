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
#include "Shader.h"

class GFXObjectFactory
{
	public:
		static RenderObject* createWall(glm::vec3* vertices, int length, Shader* shader, const char* texture, bool flatten_texture);
		static RenderObject* createPlane(glm::vec3* vertices, int length, Shader* shader, const char* texture, bool flatten_texture);
		static RenderObject* createLine(glm::vec3 vertices[2], float line_width, Shader* shader, GLfloat color[3]);
		static RenderObject* createCircle(glm::vec3 position, float radius, Shader* shader, GLfloat color[3]);

	private:
		static GLuint* triangulate(glm::vec3* vertices, int length);
		static GLfloat* createVertexArray(glm::vec3* vertices, int length);
		static void fitTexture(GLfloat* vertices, int length, int type, bool flatten_texture);
};

#endif
