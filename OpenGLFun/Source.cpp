#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include <iostream>
#include <string>

static unsigned int CompileShader(const std::string& source, unsigned int type)
{
	auto id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result==GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length*sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << message << std::endl;
		glDeleteShader(id);
	}

	return id;
}

static unsigned int CreateShader(const std::string & vertexShader, const std::string& fragmentShader) 
{
	auto program=glCreateProgram();
	auto vs = CompileShader(vertexShader,GL_VERTEX_SHADER);
	auto fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}



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
	constexpr float positions[] = {
		-0.1f, -0.1f,
		0.0f, 0.1f,
		0.1f, -0.1f,	
	};
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,false,2*sizeof(float),static_cast<const void*>(0));
	std::string vertexShader =
		R"(#version 330 core

			layout(location=0) in vec4 position;
			void main()
			{
				gl_Position=position;				
			}
)";
	std::string fragmentShader =
		R"(#version 330 core

			layout(location=0) out vec4 color;
			void main()
			{
				color=vec4(1.0,0.4,0.0,1.0);				
			}
)";
	unsigned int shader = CreateShader(vertexShader,fragmentShader);
	glUseProgram(shader);

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