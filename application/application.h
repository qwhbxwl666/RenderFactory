#pragma once

#include <iostream>
//#include <GLFW/glfw3.h>

#define app Application::getInstance()
// ?
class GLFWwindow;

// 单例类（全局唯一实例）
class Application {
public:
	~Application();

	// 用于访问实例的静态函数
	static Application* getInstance();

	bool init(const int& width = 800, const int& height = 600);

	bool update();

	void destroy();

	uint32_t getWidth() const { return mWidth; }
	uint32_t getHeight() const { return mHeight; }

private:
	// 全局唯一的静态变量实例
	static Application* mInstance;

	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	Application();
};