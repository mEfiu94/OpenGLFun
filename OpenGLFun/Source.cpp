#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <iostream>

int main(void)
{
	Window win(1024, 768, "OpenGL Testing");
	/* Make the window's context current */
	win.Start();
	GLenum err = glewInit();
	/* Loop until the user closes the window */
	if (GLEW_OK != err)
		std::cout << "ERROR!\n";
	std::cout << glGetString(GL_VERSION) << std::endl;


	unsigned int bufferId;
	constexpr float positions[8] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f,	
	};
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,2*sizeof(float),static_cast<const void*>(0));



	while (!win.WindowShouldClose())
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		win.Render();

		/* Poll for and process events */
		glfwPollEvents(); 
	}

	glfwTerminate();
	return 0;
}