#include "Application.h"
#include "engine/io/Input.h"
#include "Primitives.h"

Application::Application(const std::string& title, unsigned int width, unsigned int height)
{
    m_Window = std::make_unique<Window>(title, width, height);

    // Initialize the camera
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f); // Camera position
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);       // Camera up vector
    float yaw = -90.0f;                               // Yaw
    float pitch = 0.0f;                               // Pitch
    float fov = 45.0f;                                // Field of View
    float aspectRatio = 4.0f / 3.0f;                  // Aspect Ratio (for example)
    float nearClip = 0.1f;                            // Near clipping plane
    float farClip = 100.0f;                           // Far clipping plane

    m_Camera = std::make_unique<Camera>(position, up, yaw, pitch, fov, aspectRatio, nearClip, farClip);

    float lastFrame = static_cast<float>(glfwGetTime());

    start();

    while (m_Window->open()) {
        float currentFrameTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameTime - lastFrame;
        lastFrame = currentFrameTime;

        update(deltaTime);
    }
}

Application::~Application()
{
}

void Application::start()
{
    m_DefaultShader = std::make_unique<Shader>("res/shaders/vBasic.glsl", "res/shaders/fBasic.glsl");
    m_ContainerTexture = std::make_unique<Texture>("res/textures/container.jpg");
    m_WallTexture = std::make_unique<Texture>("res/textures/wall.jpg");
    m_Cube = std::make_unique<Mesh>(Primitives::Cube());
    m_Wall = std::make_unique<Mesh>(Primitives::Sphere(1, 20, 20));
    m_Wall->Translate({ 4.0f, 0.0f, 0.0f });
}

void Application::update(float deltaTime) {
    Input(deltaTime);

    // Update camera view matrix
    glm::mat4 viewMatrix = m_Camera->GetViewMatrix();
    glm::mat4 projectionMatrix = m_Camera->GetProjectionMatrix();

    // Clear the window with a specific color
    m_Window->clear({ 0.2f, 0.3f, 0.3f });

    // Draw the quad
    m_Cube->Draw(m_DefaultShader, m_ContainerTexture, m_Camera);
    m_Wall->Draw(m_DefaultShader, m_WallTexture, m_Camera);


    // Swap the buffers
    m_Window->swap();
}

void Application::Input(float deltaTime) {
    // Process input for camera movement
    if (Input::GetKey(GLFW_KEY_W))
        m_Camera->ProcessKeyboardMovement(m_Camera->GetFront(), deltaTime);
    if (Input::GetKey(GLFW_KEY_S))
        m_Camera->ProcessKeyboardMovement(-m_Camera->GetFront(), deltaTime);
    if (Input::GetKey(GLFW_KEY_A))
        m_Camera->ProcessKeyboardMovement(-m_Camera->GetRight(), deltaTime);
    if (Input::GetKey(GLFW_KEY_D))
        m_Camera->ProcessKeyboardMovement(m_Camera->GetRight(), deltaTime);
    if (Input::GetKey(GLFW_KEY_SPACE))
        m_Camera->ProcessKeyboardMovement(m_Camera->GetUp(), deltaTime);
    if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
        m_Camera->ProcessKeyboardMovement(-m_Camera->GetUp(), deltaTime);


    // Process input for camera rotation
    float rotationSpeed = 50.0f; // Adjust as necessary
    if (Input::GetKey(GLFW_KEY_UP))
        m_Camera->ProcessKeyboardRotation(0.0f, rotationSpeed * deltaTime);
    if (Input::GetKey(GLFW_KEY_DOWN))
        m_Camera->ProcessKeyboardRotation(0.0f, -rotationSpeed * deltaTime);
    if (Input::GetKey(GLFW_KEY_LEFT))
        m_Camera->ProcessKeyboardRotation(-rotationSpeed * deltaTime, 0.0f);
    if (Input::GetKey(GLFW_KEY_RIGHT))
        m_Camera->ProcessKeyboardRotation(rotationSpeed * deltaTime, 0.0f);
}
