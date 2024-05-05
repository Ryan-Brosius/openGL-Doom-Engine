#include "Renderer.h"
#include "TextureMap.h"

GLfloat vertices[] =
{
    //DRAWING TRIANGLE
    // POSITIONS            //COLORS
    //-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
    // 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
    // 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,

    //DRAWING THE SQUARE
    // POSITIONS            //COLORS
    -0.5f, -0.5f, 2.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
    -0.5f,  0.5f, 2.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
     0.5f,  0.5f, 2.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
     0.5f, -0.5f, 2.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,  // Lower right corner
};

GLfloat vertices2[] =
{
     0.0f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
     0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
     4.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,	4.0f, 1.0f,
     4.0f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f,	4.0f, 0.0f
};

GLfloat floorvert[] =
{
    0.0f, -1.0f, -5.0f,     1.0f, 1.0f, 1.0f,   5.0f, 10.0f,
    5.0f, -1.0f, -2.0f,     1.0f, 1.0f, 1.0f,   10.0f, 7.0f,
    5.0f, -1.0f,  2.0f,     1.0f, 1.0f, 1.0f,   10.0f, 3.0f,
    0.0f, -1.0f,  5.0f,     1.0f, 1.0f, 1.0f,   5.0f, 0.0f,
   -5.0f, -1.0f,  2.0f,     1.0f, 1.0f, 1.0f,   0.0f, 2.0f,
   -5.0f, -1.0f, -2.0f,     1.0f, 1.0f, 1.0f,   0.0f, 7.0f
};

GLuint floorIndices[] = {
    0, 1, 5,
    5, 4, 1,
    4, 1, 2,
    4, 3, 2
};

GLuint indices[] = {
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
};

Renderer::Renderer(Camera* camera, Shader* shader)
	: camera(camera), shader(shader) {};

void Renderer::render()
{
    Node* temp = this->ObjectContainer.head;

	while (temp != NULL)
	{
		temp->data->Render();
	    temp = temp->next;
	}
}

void Renderer::addObjects()
{
    RenderObject* r1 = new RenderObject(floorvert, sizeof(floorvert), floorIndices, sizeof(floorIndices), shader, "bricks.png");
    RenderObject* r2 = new RenderObject(vertices, sizeof(vertices), indices, sizeof(indices), shader, "pop_cat.png");
    RenderObject* r3 = new RenderObject(vertices2, sizeof(vertices2), indices, sizeof(indices), shader, "bricks.png");

    ObjectContainer.insert(r1);
    ObjectContainer.insert(r2);
    ObjectContainer.insert(r3);
}