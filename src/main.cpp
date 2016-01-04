

#include <iostream>
#include <vector>
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

		glewEnv glew;

		vector<shader_info> shader_infos = { {GL_VERTEX_SHADER, "shaders/SimpleVertexShader.vertexshader" },
			{ GL_FRAGMENT_SHADER, "shaders/SimpleFragmentShader.fragmentshader" } };

		GLuint programID = LoadShaders(shader_infos);
		glUseProgram(programID);

		glfwSetKeyCallback(window, key_callback);

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

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	catch (const FileNotFound& ex)
	{
		err_hander(string("Impossible to open ") + ex.filename + string(". Are you in the right directory?"));
	}
	catch (const ShaderCompileError& ex)
	{
		err_hander(string("Shader compilation error: ") + ex.err_msg);
	}
	catch (const ProgramCompileError& ex)
	{
		err_hander(string("Program compilation error: ") + ex.err_msg);
	}
	catch (const glfwEnvInitExcept& /*e*/)
	{
		err_hander("Failed to initialize GLFW!");
	}
	catch (const glewEnvInitExcept& /*e*/)
	{
		err_hander("Failed to initialize GLEW!");
	}
	catch (const glfwWinExcept& /*e*/)
	{
		err_hander("Failed to create window!");
	}

	return 0;
}
