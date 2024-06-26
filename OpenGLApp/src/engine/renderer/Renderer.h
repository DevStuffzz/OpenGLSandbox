#pragma once
#include <glad/glad.h>
#include <iostream>

class Renderer {
public:
    static void checkGLError() {
        uint32_t error;
        while ((error = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL Error: " << error << std::endl;
        }
    }
public:
	Renderer();
	~Renderer();
};