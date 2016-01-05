
#define _CRTDBG_MAP_ALLOC 
#include<stdlib.h> 
#include<crtdbg.h>

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
#include "demo00/demo00.h"
#include "demo01/demo01.h"

vector<unique_ptr<Demo>> demos;
unsigned int curr_demo = 0xffff;

void choose_demo(int);

void prepare(GLFWwindow * win)
{
	demos.push_back(unique_ptr<Demo>(new Demo00));
	demos.push_back(unique_ptr<Demo>(new Demo01));

	for (auto & p : demos)
		p->Prepare(win);

	choose_demo(GLFW_KEY_0); //select demo 0
}

void choose_demo(int key)
{
	if (key < GLFW_KEY_0 || (key - GLFW_KEY_0) >= (int)demos.size())
		return;
	unsigned int new_demo = key - GLFW_KEY_0;
	if (new_demo != curr_demo)
	{
		curr_demo = new_demo;
		demos[curr_demo]->Active();
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else
		choose_demo(key);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	demos[curr_demo]->ResizeWindow(width, height);
}

extern const int nWinWidth = 1024;
extern const int nWinHeight = 768;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
		glfwSetWindowSizeCallback(window, window_size_callback);

		prepare(window);

		glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

		while (!glfwWindowShouldClose(window))
		{
			demos[curr_demo]->Time(glfwGetTime());
			demos[curr_demo]->Draw();

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
