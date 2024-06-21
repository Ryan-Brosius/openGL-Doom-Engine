#include "GFXObjectFactory.h"

//TODO:
//Fix to take in arr of GLfloat
//and create DoubleLL in the triangulate
//then fix and make amazing lolkekw
//also will need a function for wall/plane to
//fix up texture placement

RenderObject* GFXObjectFactory::createWall(glm::vec3* vertices, int length, Shader* shader, const char* texture, bool flatten_texture)
{
    GLfloat* proper_vertices = createVertexArray(vertices, length);
    GLuint* indices = triangulate(vertices, length);

    fitTexture(proper_vertices, length, 1, flatten_texture);

    RenderObject* wall = new RenderObject(proper_vertices, sizeof(GLfloat) * length * 8, indices, sizeof(GLuint) * (length - 2) * 3, shader, texture);
    return wall;
}

RenderObject* GFXObjectFactory::createPlane(glm::vec3* vertices, int length, Shader* shader, const char* texture, bool flatten_texture)
{
    GLfloat* proper_vertices = createVertexArray(vertices, length);
    GLuint* indices = triangulate(vertices, length);

    fitTexture(proper_vertices, length, 2, flatten_texture);

    RenderObject* plane = new RenderObject(proper_vertices, sizeof(GLfloat) * length * 8, indices, sizeof(GLuint) * (length - 2) * 3, shader, texture);
    return plane;
}

RenderObject* GFXObjectFactory::createLine(glm::vec3 vertices[2], float line_width, Shader* shader, GLfloat color[3])
{
    GLfloat proper_vertices[] =
    {
        vertices[0].x, vertices[0].y + line_width / 2, vertices[0].z,     color[0], color[1], color[2],     0.0, 0.0,
        vertices[0].x, vertices[0].y - line_width / 2, vertices[0].z,     color[0], color[1], color[2],     0.0, 0.0,
        vertices[1].x, vertices[1].y - line_width / 2, vertices[1].z,     color[0], color[1], color[2],     0.0, 0.0,
        vertices[1].x, vertices[1].y + line_width / 2, vertices[1].z,     color[0], color[1], color[2],     0.0, 0.0
    };
        
    glm::vec3 indices_check[] =
    {
        glm::vec3(vertices[0].x, vertices[0].y + line_width / 2, vertices[0].z),
        glm::vec3(vertices[0].x, vertices[0].y - line_width / 2, vertices[0].z),
        glm::vec3(vertices[1].x, vertices[1].y - line_width / 2, vertices[1].z),
        glm::vec3(vertices[1].x, vertices[1].y + line_width / 2, vertices[1].z)
    };

    GLuint* indices = triangulate(indices_check, 4);

    RenderObject* line = new RenderObject(proper_vertices, sizeof(GLfloat) * 4 * 8, indices, sizeof(GLuint) * 6, shader, "");
    return line;
}

RenderObject* GFXObjectFactory::createCircle(glm::vec3 position, float radius, Shader* shader, GLfloat color[3])
{
    const int CIRCLE_LINES = 20;
    glm::vec3 vertices[CIRCLE_LINES * 6];

    for (int i = 0; i < CIRCLE_LINES; ++i)
    {
        float angle = M_PI*2 / CIRCLE_LINES * i;
        vertices[i] = glm::vec3(cosf(angle) * radius + position.x, sinf(angle) * radius + position.y, position.z);
    }

    GLfloat* proper_vertices = createVertexArray(vertices, CIRCLE_LINES);
    GLuint* indices = triangulate(vertices, CIRCLE_LINES);

    RenderObject* circle = new RenderObject(proper_vertices, sizeof(GLfloat) * CIRCLE_LINES * 8, indices, sizeof(GLuint) * (CIRCLE_LINES - 2) * 3, shader, "");
    return circle;
}

void GFXObjectFactory::fitTexture(GLfloat* vertices, int length, int type, bool flatten_texture)
{
    int x_axis, y_axis, z_axis;

    switch (type)
    {
        case 1:
            x_axis = 0;
            y_axis = 1;
            z_axis = 2;
            break;
        case 2:
            x_axis = 0;
            y_axis = 2;
            z_axis = 1;
            break;
    }

    GLfloat texture_x = 0, texture_y = 0;
    vertices[6] = 0;
    vertices[7] = 0;
    GLfloat current_X = vertices[x_axis], current_Y = vertices[y_axis], current_Z = vertices[z_axis];

    for (int i = 1; i < length; ++i)
    {
        GLfloat new_X = vertices[i * 8 + x_axis], new_Y = vertices[i * 8 + y_axis], new_Z = vertices[i * 8 + z_axis];

        GLfloat dist = (((new_X - current_X) * (new_X - current_X)) + ((new_Z - current_Z) * (new_Z - current_Z)));
        if (dist != 0) dist = sqrtf(dist);

        ((new_X - current_X) < 0) ? texture_x -= dist : texture_x += dist;
        ((new_Y - current_Y) < 0) ? texture_y -= new_Y - current_Y : texture_y += new_Y - current_Y;
        
        current_X = new_X;
        current_Y = new_Y;
        current_Z = new_Z;

        vertices[i * 8 + 6] = texture_x;
        vertices[i * 8 + 7] = texture_y;
    }

    //GLfloat min_x = vertices[x_axis], max_x = vertices[x_axis];
    //GLfloat min_y = vertices[y_axis], max_y = vertices[y_axis];

    //for (int i = 0; i < length; ++i)
    //{
    //    if (vertices[i * 8 + x_axis] < min_x) min_x = vertices[i * 8 + x_axis];
    //    if (vertices[i * 8 + x_axis] > max_x) max_x = vertices[i * 8 + x_axis];
    //    if (vertices[i * 8 + y_axis] < min_y) min_y = vertices[i * 8 + y_axis];
    //    if (vertices[i * 8 + y_axis] > max_x) max_y = vertices[i * 8 + y_axis];
    //}

    //GLfloat width = max_x - min_x;
    //GLfloat height = max_y - min_y;

    //for (int i = 0; i < length; ++i)
    //{
    //    //texture x
    //    vertices[i * 8 + 6] = width - vertices[i * 8 + x_axis];
    //    //texture y
    //    vertices[i * 8 + 7] = height - vertices[i * 8 + y_axis];
    //}
}

GLuint* GFXObjectFactory::triangulate(glm::vec3* vertices, int length)
{
    //Generates the GLfloat verticies
    //Assumes that polygon is simple, is closed, and vertex order is CCW!!
    //E = V - 2 ?

    GLuint* arr = new GLuint[(length - 2) * 3];


    DoubleLinkedList<int> vertlist = DoubleLinkedList<int>();
    for (int i = 0; i < length; ++i)
    {
        vertlist.add(i);
    }
    int counter = 0;

    std::shared_ptr<DoubleNode<int>> node = vertlist.head;
    while (vertlist.length > 2)
    {

        int i = node->prev->data;
        int j = node->data;
        int k = node->next->data;

        bool valid = true;
        if (isConvex(vertices[i], vertices[j], vertices[k]))
        {
            std::shared_ptr<DoubleNode<int>> temp = node;
            temp = temp->next->next;
            for (int len = 0; len < vertlist.length - 3; ++len)
            {
                if (insideTriangle(vertices[i], vertices[j], vertices[k], vertices[temp->data]))
                {
                    valid = false;
                    break;
                }

                temp = temp->next;
            }
        }
        else
        {
            valid = false;
        }

        if (valid)
        {
            arr[counter * 3] = i;
            arr[counter * 3 + 1] = j;
            arr[counter * 3 + 2] = k;

            counter++;
            vertlist.remove(node->data);
        }

        node = node->next;
    }

    return arr;
}

//std::shared_ptr<DoubleLinkedList<glm::vec3>> vertices
GLfloat* GFXObjectFactory::createVertexArray(glm::vec3* vertices, int length)
{
    //GLfloat verticies that will be used for the
    //VBO VAO etc

    // x y z | r g b | (texture) x y
    //  3 3 2 -> 8 per vertex
    GLfloat* arr = new GLfloat[length * 8];

    for (int i = 0; i < length; ++i)
    {
        //Position (x, y, z)
        arr[i * 8] = vertices[i].x;
        arr[i * 8 + 1] = vertices[i].y;
        arr[i * 8 + 2] = vertices[i].z;

        //Color (r, g, b)
        arr[i * 8 + 3] = 1.0f;
        arr[i * 8 + 4] = 1.0f;
        arr[i * 8 + 5] = 1.0f;

        //Texture Pos (x, y)
        arr[i * 8 + 6] = 1.0f;
        arr[i * 8 + 7] = 1.0f;
    }

    return arr;
}