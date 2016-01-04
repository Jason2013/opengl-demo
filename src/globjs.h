#ifndef __GLOBJS_H_
#define __GLOBJS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

void err_hander(const std::string&);

class MyExcept {};

class glfwEnvInitExcept : public MyExcept {};

class glfwWinExcept : public MyExcept {};

class glewEnvInitExcept : public MyExcept {};

class FileNotFound : public MyExcept
{
public:
	FileNotFound(const std::string& fname) : filename(fname) {}
	const std::string filename;
};

class ShaderCompileError : public MyExcept
{
public:
	ShaderCompileError(const std::string& msg) : err_msg(msg) {}
	const std::string err_msg;
};

class ProgramCompileError : public MyExcept
{
public:
	ProgramCompileError(const std::string& msg) : err_msg(msg) {}
	const std::string err_msg;
};

class glfwEnv
{
public:
	glfwEnv()
	{
		if (glfwInit() != GL_TRUE)
			throw glfwEnvInitExcept();
	}
	~glfwEnv() { glfwTerminate(); }
};

class glewEnv
{
public:
	glewEnv()
	{
		if (glewInit() != GLEW_OK)
			throw glewEnvInitExcept();
	}
};

class GlfwWinObj
{
public:
	GlfwWinObj(int width, int height, const char * title)
	{
		_win = glfwCreateWindow(width, height, title, 0, 0);
		if (!_win)
			throw glfwWinExcept();
	}
	~GlfwWinObj() { glfwDestroyWindow(_win); }
	operator GLFWwindow * () { return _win; }

private:
	GLFWwindow * _win;
};

class VertexArrayObj
{
public:
	VertexArrayObj(bool immediate = true)
	{
		glGenVertexArrays(1, &id);
		if (immediate)
			glBindVertexArray(id);
	}
	~VertexArrayObj() { glDeleteVertexArrays(1, &id); }
	operator GLuint() { return id; }
private:
	GLuint id;
};

class BufferObj
{
public:
	BufferObj() { glGenBuffers(1, &id); }
	~BufferObj() { glDeleteBuffers(1, &id); }
	operator GLuint() { return id; }
private:
	GLuint id;
};

#endif // __GLOBJS_H_
