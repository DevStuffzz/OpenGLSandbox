#include "Window.h"

#include <iostream>
#include "Callbacks.h"
#include "Input.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);


    // glfw window creation
    // --------------------
    m_Id = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);
    if (m_Id == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_Id);
    Input::RegisterCallbacks(m_Id);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

}

Window::~Window()
{
    glfwDestroyWindow(m_Id);
    glfwTerminate();
}



void Window::clear(glm::vec3 color)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Window::swap()
{
    glfwSwapBuffers(m_Id);
    glfwPollEvents();
}

bool Window::open()
{
    return !glfwWindowShouldClose(m_Id);
}
