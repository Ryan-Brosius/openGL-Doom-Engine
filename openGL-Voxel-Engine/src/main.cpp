#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"

GLfloat vertices[] =
{
    //DRAWING TRIANGLE
    // POSITIONS            //COLORS
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,

    //DRAWING THE SQUARE
    // POSITIONS            //COLORS
     0.0f,  0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
     1.0f,  0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f

};

GLuint indices[] = {
    0, 1, 2,
    3, 4, 5,
    4, 5, 6
};

int main(void)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "NAME", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    //Creates shaders
    Shader shader("default.vert", "default.frag");

    //Generates vertex array object
    VAO VAO1;
    VAO1.Bind();

    //Generates vertex buffer
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    //Links VBO to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Init();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 9);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}