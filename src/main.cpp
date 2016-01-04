

#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "globjs.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

extern const int nWinWidth = 1024;
extern const int nWinHeight = 768;

int main()
{

	try {

		glfwEnv glfw;
		 
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GlfwWinObj window(nWinWidth, nWinHeight, "OpenGL DEMO");

		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);

		glewEnv glew;

		glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

		static GLfloat vertexBuffer[] = {
			-0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f,
			 0.6f,  0.5f,
			-0.5f, -0.5f,
			 0.5f, -0.5f
		};

		VertexArrayObj vao;

		BufferObj buffer;

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		GLuint programID = LoadShaders("shaders/SimpleVertexShader.vertexshader", "shaders/SimpleFragmentShader.fragmentshader");
		glUseProgram(programID);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	catch (const glfwInitExcept& /*e*/)
	{
		cerr << "Failed to initialize GLFW!" << endl;
	}
	catch (const glewExcept& /*e*/)
	{
		cerr << "Failed to initialize GLEW!" << endl;
	}
	catch (const glfwWinExcept& /*e*/)
	{
		cerr << "Failed to create window!" << endl;
	}

	return 0;
}
