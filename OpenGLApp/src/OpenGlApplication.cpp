

#include "glad/glad.h"
#include "GLFW/glfw3.h"

int main(int* argc, const char** argv) {

	GLFWwindow* glfwWindow;

	glfwInit();
	
	glfwDefaultWindowHints();
	glfwWindow = glfwCreateWindow(1920, 1080, "Example Window", NULL, NULL);

	glfwMakeContextCurrent(glfwWindow);
	glfwSwapInterval(1);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	float time = glfwGetTime();
	float r = time / 255.0f;

	while (!glfwWindowShouldClose(glfwWindow)) {
		glfwShowWindow(glfwWindow);
		r += time / 255.0f;

		if (r >= 1.0f) time = time * -1;
		
		glClearColor(r, 0, r, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(glfwWindow);
	}
}