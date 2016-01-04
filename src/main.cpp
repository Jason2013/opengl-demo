

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
using std::vector;
using std::unique_ptr;


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "globjs.h"
#include "conio.h"
#include "objloader.h"
#include "texture.h"

#include "demo.h"
#include "demo00.h"
#include "demo01.h"

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

		glfwSetKeyCallback(window, key_callback);

		unique_ptr<Demo> demo00(new Demo00);
		demo00->Prepare();

		unique_ptr<Demo> demo1(new Demo01);
		demo1->Prepare();

		glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			demo00->Draw();
			demo1->Draw();

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
