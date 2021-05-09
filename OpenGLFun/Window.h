#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
class Window
{
public:
	Window() = delete;
	Window(int h, int w, const char* name) :m_Height(h), m_Width(w), m_WindowName(name) {
		init();
		m_Window = glfwCreateWindow(m_Height, m_Width, m_WindowName, NULL, NULL);
		if (m_Window==nullptr)		
			glfwTerminate();
	};
	void Start() { glfwMakeContextCurrent(m_Window); }
	bool WindowShouldClose() {return glfwWindowShouldClose(m_Window); }
	void Render(){ glfwSwapBuffers(m_Window); }
private:
	GLFWwindow* m_Window = nullptr;
	int m_Height = 0;
	int m_Width = 0;
	const char* m_WindowName = nullptr;
	void init() {
		if (!glfwInit()) {
			std::cout << "GLFW initialization failed! \n";
		}
	};
};

