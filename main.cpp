#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h> // ╤оят

#include "funcs/func.h"
#include "wrapper/checkError.h"
#include "application/application.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << "key:" << key << "\t\taction:" << action << "\tmods:" << mods << std::endl;;
}

int main() {
	if (!app->init(800, 600)) {
		return -1;
	}

	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetKeyCallback(window, keyCallBack);

	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	while (app->update())
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		// rendering

	}

	app->destroy();

	return 0;
}