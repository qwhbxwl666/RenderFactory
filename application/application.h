#pragma once

#include <iostream>
//#include <GLFW/glfw3.h>

#define app Application::getInstance()
// ?
class GLFWwindow;

// �����ࣨȫ��Ψһʵ����
class Application {
public:
	~Application();

	// ���ڷ���ʵ���ľ�̬����
	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destroy();

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }

private:
	// ȫ��Ψһ�ľ�̬����ʵ��
	static Application* mInstance;

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	Application();
};