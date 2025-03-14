#include "application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ��ʼ��Application�ľ�̬����
Application* Application::mInstance = nullptr;

Application* Application::getInstance() {
	// ���mInstance�Ѿ�ʵ�����ˣ�new�����ˣ�����ֱ�ӷ���
	// ������Ҫ��new�������ٷ���
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}
	return mInstance;
}

Application::Application() {

}

Application::~Application() {

}

bool Application::init(const int& width, const int& height) {
	mWidth = width;
	mHeight = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, "RenderFactory", NULL, NULL);
	if (mWindow == NULL) return false;
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) return false;

	glfwPollEvents();

	glfwSwapBuffers(mWindow);

	return true;
}

void Application::destroy() {
	glfwTerminate();
}