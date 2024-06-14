#include "GFXObjectFactory.h"

//TODO:
//Fix to take in arr of GLfloat
//and create DoubleLL in the triangulate
//then fix and make amazing lolkekw
//also will need a function for wall/plane to
//fix up texture placement

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

    for (int i = 0; i < (length - 2) * 3; ++i)
    {
        std::cout << arr[i] << std::endl;
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
        arr[i * 8 + 6] = 0.0f;
        arr[i * 8 + 7] = 0.0f;
    }

    return arr;
}