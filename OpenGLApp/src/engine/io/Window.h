#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>


class Window {
public:
	Window(const std::string& title, unsigned int width, unsigned int height);
	~Window();

	void clear(glm::vec3 color);
	void swap();
	bool open();

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
private:
	GLFWwindow* m_Id;
	unsigned int m_Width, m_Height;
};