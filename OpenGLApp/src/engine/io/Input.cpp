#include "Input.h"

std::unordered_map<int, bool> Input::keys;
std::unordered_map<int, bool> Input::mouseButtons;
double Input::mouseX = 0.0;
double Input::mouseY = 0.0;

bool Input::GetKey(int key)
{
    return keys[key];
}

bool Input::GetMouseButton(int button)
{
    return mouseButtons[button];
}

double Input::GetMouseX()
{
    return mouseX;
}

double Input::GetMouseY()
{
    return mouseY;
}

void Input::RegisterCallbacks(GLFWwindow* window)
{
    glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);
    glfwSetKeyCallback(window, Callbacks::key_callback);
    glfwSetCursorPosCallback(window, Callbacks::cursor_position_callback);
    glfwSetMouseButtonCallback(window, Callbacks::mouse_button_callback);
}

void Callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        Input::keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        Input::keys[key] = false;
    }
}

void Callbacks::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Input::mouseX = xpos;
    Input::mouseY = ypos;
}

void Callbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        Input::mouseButtons[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        Input::mouseButtons[button] = false;
    }
}
