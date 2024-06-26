#pragma once


#include <string>
#include <memory>

#include "engine/io/Window.h"
#include "engine/renderer/Shader.h"
#include "engine/renderer/Renderer.h"
#include "Buffers/VertexArray.h"
#include <engine/renderer/Mesh.h>
#include <engine/io/Camera.h>

class Application {
public:
    Application(const std::string& title, unsigned int width, unsigned int height);
    ~Application();

    void start();
    void update(float deltaTime);

    void Input(float deltaTime);
public:
    std::unique_ptr<Window> m_Window;
private:
    std::unique_ptr<Shader> m_DefaultShader;
    std::unique_ptr<Mesh> m_Cube;
    std::unique_ptr<Mesh> m_Wall;
    std::unique_ptr<Texture> m_ContainerTexture;
    std::unique_ptr<Texture> m_WallTexture;
    std::unique_ptr<Camera> m_Camera;
};

