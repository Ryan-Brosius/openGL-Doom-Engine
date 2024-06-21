#include "Window.h"

State* state = new State;

Window::Window()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window::handle = glfwCreateWindow(WIDTH, HEIGHT, "NAME", NULL, NULL);
    if (Window::handle == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(Window::handle);

    gladLoadGL();

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
}

void Window::update()
{
    return;
}

void Window::render()
{
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gameRenderer->render();
    editorRenderer->render();

    glfwSwapBuffers(Window::handle);
}

void Window::setup()
{
    //Create game shader & renderer
    this->gameShader = new Shader("default.vert", "default.frag");
    this->primitiveShader = new Shader("2dObject.vert", "2dObject.frag");

    this->gameRenderer = new Renderer(&this->gameCamera, this->gameShader);
    this->editorRenderer = new Renderer(&this->editorCamera, this->primitiveShader);

    //add objects to state
    state->window = handle;
    
    //test function in renderer
    gameRenderer->addObjects();
    editorRenderer->addObjects();

    //Wireframe test :)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Window::window_loop()
{
    setup();


    while (!glfwWindowShouldClose(Window::handle))
    {
        //this->gameShader->Activate();
        //this->gameCamera.Inputs(Window::handle);
        //this->gameCamera.Matrix(45.0f, 0.1f, 100.0f, *this->gameShader, "camMatrix");

        this->primitiveShader->Activate();
        this->editorCamera.Inputs(Window::handle);
        this->editorCamera.Matrix(45.0f, 0.1f, 100.0f, *this->primitiveShader, "camMatrix");

        render();

        glfwPollEvents();
    }

    this->destroy();
    this->gameShader->Delete();
}

void Window::destroy()
{
    glfwDestroyWindow(this->handle);
    glfwTerminate();
}