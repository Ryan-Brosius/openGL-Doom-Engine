#pragma once
#ifndef OBJECT_RENDER_H
#define OBJECT_RENDER_H

#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "State.h"

class RenderObject
{
	public:
		RenderObject(GLfloat* vertices, GLsizeiptr verticiesSize, GLuint* indices, GLsizeiptr indicesSize, Shader* shader, const char* texture);
		void Render();

	private:
		Shader* shader;
		Texture* texture;
		VAO _VAO;
		VBO _VBO;
		EBO _EBO;

		int nVertices;
};
#endif
