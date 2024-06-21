#include "Renderer.h"

GLfloat vertices[] =
{
    //DRAWING TRIANGLE
    // POSITIONS            //COLORS
    //-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
    // 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
    // 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,

    //DRAWING THE SQUARE
    // POSITIONS            //COLORS
    -0.5f, -0.5f, 2.0f,     1.0f, 0.0f, 0.0f,	-1.0f, -1.0f, // Lower left corner
    -0.5f,  0.5f, 2.0f,     0.0f, 1.0f, 0.0f,	-1.0f, 0.0f, // Upper left corner
     0.5f,  0.5f, 2.0f,     0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // Upper right corner
     0.5f, -0.5f, 2.0f,     1.0f, 1.0f, 1.0f,	0.0f, -1.0f,  // Lower right corner
};

GLfloat vertices2[] =
{
     0.0f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
     0.0f,  1.0f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
     4.0f,  1.0f, 2.0f,     0.0f, 0.0f, 1.0f,	2.0f, 1.0f,
     4.0f,  0.0f, 2.0f,     1.0f, 1.0f, 1.0f,	2.0f, 0.0f
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
    //glm::vec3 test[] =
    //{
    //    glm::vec3(0, 5, -1),
    //    glm::vec3(1, -1, -1),
    //    glm::vec3(1, -1, -4),
    //    glm::vec3(0, 5, -4)
    //};

    //glm::vec3 test2[] =
    //{
    //    glm::vec3(-5, 0, -1),
    //    glm::vec3(5, 0, -1)
    //};

    GLfloat color[3] = { 1.0f, 1.0f, 0.0f };
    //RenderObject* testline = GFXObjectFactory::createLine(test2, .05, shader, color);
    //RenderObject* testcircle = GFXObjectFactory::createCircle(glm::vec3(0, 0, -4), 1, shader, color);

    //RenderObject* testbruh = GFXObjectFactory::createPlane(test, 4, shader, "bricks.png", true);

    //RenderObject* r1 = new RenderObject(floorvert, sizeof(floorvert), floorIndices, sizeof(floorIndices), shader, "bruh.png");
    //RenderObject* r2 = new RenderObject(vertices, sizeof(vertices), indices, sizeof(indices), shader, "pop_cat.png");
    //RenderObject* r3 = new RenderObject(vertices2, sizeof(vertices2), indices, sizeof(indices), shader, "pop_cat.png");

    //ObjectContainer.insert(r1);
    //ObjectContainer.insert(r2);
    //ObjectContainer.insert(r3);
    //ObjectContainer.insert(testbruh);
    //ObjectContainer.insert(testline);
    //ObjectContainer.insert(testcircle);

    ////// Will be used for the editor in the future //////
    // Area of the edit-area will be 100 x 100
    const int area = 50;
    for (int i = 0; i < area; ++i)
    {
        for (int j = 0; j < area; ++j)
        {
            RenderObject* circle = GFXObjectFactory::createCircle(glm::vec3(i, j, -4), .05, shader, color);
            ObjectContainer.insert(circle);
        }
    }
}