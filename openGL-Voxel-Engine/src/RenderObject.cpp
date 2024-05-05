#include "RenderObject.h"

extern State* state;

RenderObject::RenderObject(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize, Shader* shader, const char* texture)
	: shader(shader), texture(state->textureMap->get(texture)), _VBO(vertices, verticesSize), _EBO(indices, indicesSize), nVertices(indicesSize / sizeof(GLuint))
{
	_VAO.LinkAttrib(_VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	_VAO.LinkAttrib(_VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_VAO.LinkAttrib(_VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	_VAO.Unbind();
	_VBO.Unbind();
	_EBO.Unbind();
}

void RenderObject::Render()
{
	shader->Activate();
	texture->Bind();
	_VAO.Bind();
	glDrawElements(GL_TRIANGLES, nVertices, GL_UNSIGNED_INT, 0);
}